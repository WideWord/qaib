#pragma once
#include <mutex>
#include <vector>
#include <map>
#include <string>
#include <qaib/util/Typedef.hpp>
#include <condition_variable>
#include <qaib/game/GameWorld.hpp>
#include <qaib/util/Random.hpp>

namespace qaib {

    class Population;
    class NeuralNetwork;

    class MultithreadedTrainer {
    public:
        struct Config {
            GameWorld::Config world;
            int threads;
            int roundsNum;
            int populationSize;
            int startFromGeneration;
            bool useJIT;
            std::string matchWith;
            int mutationRate;
        };

        void run(const Config& config);
    private:
        Config config;

        Ref<Population> population;
        Ref<Population> matchWithPopulation;
        int generation;

        std::vector<bool> generationDone;
        std::mutex generationDoneMutex;
        std::condition_variable generationDoneCond;

        std::vector<int> roundsCtr;
        std::vector<float> fitness;
        std::mutex fitnessMutex;

        std::vector<RandomEngine> randoms;

        std::vector<std::vector<Ref<NeuralNetwork>>> nets;
        std::vector<std::vector<Ref<NeuralNetwork>>> matchWithNets;
        std::vector<int> netLinksCount;
        std::vector<int> netNeuronsCount;

        void worker(int thread);
        float calcFitness(float score, float health, int linksCount, int neuronsCount);
    };

}