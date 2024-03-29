#include <SFML/System.hpp>
#include <qaib/nn/Population.hpp>
#include <qaib/util/Random.hpp>
#include <unordered_map>
#include <unordered_set>

namespace qaib {

    Population::Population(int size, int inputsCount, int outputsCount, const GameWorld::Config& worldConfig) {
        Genome initialGenome(innovationGenerator, inputsCount, outputsCount);
        for (int i = 0; i < size; ++i) {
            auto genome = initialGenome;
            genomes.push_back(genome);
        }
        this->worldConfig = worldConfig;
    }

    void Population::makeSelection(int newSize, std::vector<float> fitness, int mutationRate) {

        float fitnessSum = 0;
        for (auto s : fitness) {
            if (s < 0.00001f) s = 0.00001f;
            fitnessSum += s;
        }
        for (auto& s : fitness) {
            s /= fitnessSum;
        }

        std::vector<Genome> newGenomes;

        for (int i = 0; i < newSize; ++i) {

            Genome* a = nullptr;
            Genome* b = nullptr;

            float ar = Random::getFloat(0, 1);
            float br = Random::getFloat(0, 1);

            for (int i = 0, iend = genomes.size(); i < iend; ++i) {
                ar -= fitness[i];
                br -= fitness[i];

                if (!a && ar < 0) {
                    a = &genomes[i];
                }
                if (!b && br < 0) {
                    b = &genomes[i];
                }

                if (a && b) {
                    break;
                }
            }

            if (!a) {
                a = &genomes.back();
            }

            if (!b) {
                b = &genomes.back();
            }

            Genome result(*a, *b);
            if (Random::getInt(0, 100) < mutationRate) {
                result.mutate(innovationGenerator);
            }
            newGenomes.push_back(result);
        }

        genomes = newGenomes;

        deleteOldGenes();
    }

    Population::Population(sf::Packet& packet) : innovationGenerator(packet) {
        packet >> worldConfig.size;
        packet >> (sf::Int32&)worldConfig.obstructionCount;
        packet >> (sf::Uint32&)worldConfig.seed;

        uint64_t size;
        packet >> (sf::Uint64&)size;

        for (uint64_t i = 0; i < size; ++i) {
            genomes.push_back(Genome(packet));
        }
    }

    void Population::writeTo(sf::Packet& packet) const {
        innovationGenerator.writeTo(packet);

        packet << worldConfig.size << (sf::Int32&)worldConfig.obstructionCount << (sf::Uint32&)worldConfig.seed;

        packet << (sf::Uint64)genomes.size();

        for (auto& genome : genomes) {
            genome.writeTo(packet);
        }
    }

    Ref<Population> Population::load(const std::string& filename) {
        sf::FileInputStream in;
        in.open(filename);
        size_t aiDataSize = (size_t)in.getSize();
        void* aiData = malloc(aiDataSize);
        in.read(aiData, aiDataSize);

        sf::Packet packet;
        packet.append(aiData, aiDataSize);

        auto res = Ref<Population>(new Population(packet));

        free(aiData);

        return res;
    }

    void Population::deleteOldGenes() {
        std::unordered_map<Innovation, int> disabledGenesCount;


        for (auto& genome : genomes) {
            for (auto& gene : genome.genes) {
                if (!gene.enabled) {
                    auto it = disabledGenesCount.find(gene.innovation);
                    if (it == disabledGenesCount.end()) {
                        disabledGenesCount[gene.innovation] = 1;
                    } else {
                        it->second += 1;
                    }
                }

            }
        }

        for (auto it = disabledGenesCount.begin(); it != disabledGenesCount.end(); ++it) {
            if (it->second < getSize()) {
                continue;
            }
            for (auto& genome : genomes) {
                for (auto geneIt = genome.genes.begin(); geneIt != genome.genes.end(); ++geneIt) {
                    if (geneIt->innovation == it->first) {
                        genome.genes.erase(geneIt);
                        break;
                    }
                }
            }
        }
    }


}
