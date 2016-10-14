#include <qaib/app/MultithreadedTrainer.hpp>
#include <qaib/util/Typedef.hpp>
#include <qaib/nn/Population.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/GameWorld.hpp>
#include <qaib/nn/JITNeuralNetwork.hpp>
#include <qaib/game/NeuralNetworkPawnController.hpp>
#include <mutex>
#include <functional>
#include <thread>
#include <qaib/util/Random.hpp>
#include <glm/glm.hpp>
#include <qaib/util/MakeString.hpp>
#include <fstream>
#include <string>
#include <iostream>

namespace qaib {

    void MultithreadedTrainer::run(const Config& _config) {

        this->config = _config;
        generation = config.startFromGeneration;

        if (generation <= 0) {
            generation = 1;

            population = Ref<Population>(new Population(config.populationSize,
                                                        NeuralNetworkPawnController::inputsCount,
                                                        NeuralNetworkPawnController::outputsCount,
                                                        config.world));

            sf::Packet packet;
            population->writeTo(packet);

            std::ofstream out(MakeString() << "pop/" << generation << ".pop");
            out.write((const char*)packet.getData(), packet.getDataSize());

        } else {
            population = Population::load(MakeString() << "pop/" << generation << ".pop");
            this->config.world = population->getWorldConfig();
        }

        if (config.matchWith.length() > 0) {
            matchWithPopulation = Population::load(config.matchWith);
        }

        generationDone.resize(config.threads);
        nets.resize(config.threads);
        randoms.reserve(config.threads);

        if (matchWithPopulation != nullptr) {
            matchWithNets.resize(config.threads);
            for (auto& v : matchWithNets) {
                for (auto& genome : matchWithPopulation->getGenomes()) {
                    if (config.useJIT) {
                        auto jitnet = Ref<JITNeuralNetwork>(new JITNeuralNetwork(genome.buildNeuralNetwork()));
                        for (int th = 0; th < config.threads; ++th) {
                            v.push_back(Ref<JITNeuralNetworkWithField>(new JITNeuralNetworkWithField(jitnet)));
                        }
                    } else {
                        for (int th = 0; th < config.threads; ++th) {
                            v.push_back(genome.buildNeuralNetwork());
                        }
                    }
                }
            }
        }

        for (int i = 1; i < config.threads; ++i) {
            generationDone[i] = true;
            std::thread([i, this](){
                worker(i);
            }).detach();
        }
        worker(0);
    }

    void MultithreadedTrainer::worker(int thread) {

        while (true) {

            if (thread == 0) {

                for (int th = 0; th < config.threads; ++th) {
                    nets[th].clear();
                }

                for (auto& genome : population->getGenomes()) {
                    if (config.useJIT) {
                        auto jitnet = Ref<JITNeuralNetwork>(new JITNeuralNetwork(genome.buildNeuralNetwork()));
                        for (int th = 0; th < config.threads; ++th) {
                            nets[th].push_back(Ref<JITNeuralNetworkWithField>(new JITNeuralNetworkWithField(jitnet)));
                        }
                    } else {
                        for (int th = 0; th < config.threads; ++th) {
                            nets[th].push_back(genome.buildNeuralNetwork());
                        }
                    }
                }

                netLinksCount.clear();
                netNeuronsCount.clear();
                fitness.clear();
                roundsCtr.clear();

                for (auto& g : population->getGenomes()) {
                    fitness.push_back(0);
                    netLinksCount.push_back(g.getEnabledGenesCount());
                    netNeuronsCount.push_back(g.getNeuronsCount());
                    roundsCtr.push_back(0);
                }
            }

            if (thread == 0) {
                for (int i = 1; i < config.threads; ++i) {
                    {
                        std::unique_lock<std::mutex> lock(generationDoneMutex);
                        generationDone[i] = false;
                    }
                    generationDoneCond.notify_all();
                }
            } else {
                std::unique_lock<std::mutex> lock(generationDoneMutex);
                while (generationDone[thread]) {
                    generationDoneCond.wait(lock);
                }
            }

            // paralel

            while (true) {
                int aGenome = -1, bGenome = -1;
                bool addFitnessToB = false;

                {
                    std::unique_lock<std::mutex> lock(fitnessMutex);
                    for (int i = 0, iend = population->getSize(); i < iend; ++i) {
                        if (roundsCtr[i] < config.roundsNum) {
                            roundsCtr[i] += 1;
                            aGenome = i;
                            break;
                        }
                    }

                    if (aGenome == -1) break;

                    bGenome = randoms[thread].getInt(0, population->getSize());

                    if (roundsCtr[bGenome] < config.roundsNum) {
                        roundsCtr[bGenome] += 1;
                        addFitnessToB = true;
                    }
                }


                auto gw = Ref<GameWorld>(new GameWorld());

                auto aPawn = gw->createPawn();
                auto bPawn = gw->createPawn();

                aPawn->useController<NeuralNetworkPawnController>(nets[thread][aGenome], bPawn);
                bPawn->useController<NeuralNetworkPawnController>(nets[thread][bGenome], aPawn);

                for (int i = 0; i < 30 * 8; ++i) {
                    gw->doTick(1 / 30.0f);
                }

                {
                    std::unique_lock<std::mutex> lock(fitnessMutex);
                    fitness[aGenome] += calcFitness(aPawn->getScore(),
                                                    aPawn->getHealth() / aPawn->getInitialHealth(),
                                                    netLinksCount[aGenome],
                                                    netNeuronsCount[aGenome]);
                    if (addFitnessToB) {
                        fitness[bGenome] += calcFitness(bPawn->getScore(),
                                                        bPawn->getHealth() / bPawn->getInitialHealth(),
                                                        netLinksCount[bGenome],
                                                        netNeuronsCount[bGenome]);
                    }

                }
            }

            // ===

            if (thread == 0) {
                for (int i = 1; i < config.threads; ++i) {
                    std::unique_lock<std::mutex> lock(generationDoneMutex);
                    while (!generationDone[i]) {
                        generationDoneCond.wait(lock);
                    }
                }
            } else {
                std::unique_lock<std::mutex> lock(generationDoneMutex);
                generationDone[thread] = true;
                generationDoneCond.notify_all();
            }

            if (thread == 0) {
                population->makeSelection(config.populationSize, fitness, config.mutationRate);
                generation += 1;

                sf::Packet packet;
                population->writeTo(packet);

                std::ofstream out(MakeString() << "pop/" << generation << ".pop");
                out.write((const char*)packet.getData(), packet.getDataSize());
            }

        }

    }

    float MultithreadedTrainer::calcFitness(float score, float health, int linksCount, int neuronsCount) {
        if (score < 0) {
            score = 0;
        }
        score += 1;
        float fitness = score * score + 0.1f;
        return fitness;
    }


}