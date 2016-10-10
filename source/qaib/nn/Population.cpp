#include <SFML/System.hpp>
#include <qaib/nn/Population.hpp>
#include <qaib/util/Random.hpp>

namespace qaib {

    Population::Population(int size, int inputsCount, int outputsCount) {
        Genome initialGenome(innovationGenerator, inputsCount, outputsCount);
        for (int i = 0; i < 10; ++i) {
            initialGenome.insertRandomConnection(innovationGenerator);
        }
        for (int i = 0; i < size; ++i) {
            auto genome = initialGenome;
            for (int j = 0; j < 20; ++j) {
                genome.mutate(innovationGenerator);
            }
            genomes.push_back(genome);
        }
    }

    std::vector<Ref<NeuralNetwork>> Population::getNeuralNetworks() const {
        std::vector<Ref<NeuralNetwork>> res;

        for (auto& genome : genomes) {
            res.push_back(genome.buildNeuralNetwork());
        }

        return res;
    }

    void Population::makeSelection(int newSize, std::vector<float> fitness) {

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
            if (Random::getInt(0, 100) > 80) {
                result.mutate(innovationGenerator);
            }
            newGenomes.push_back(result);
        }

        genomes = newGenomes;

        deleteOldGenes();
    }

    Population::Population(sf::Packet& packet) : innovationGenerator(packet) {
        uint64_t size;
        packet >> size;

        for (uint64_t i = 0; i < size; ++i) {
            genomes.push_back(Genome(packet));
        }
    }

    void Population::writeTo(sf::Packet& packet) const {
        innovationGenerator.writeTo(packet);

        packet << (uint64_t)genomes.size();

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
        while (true) {
            if (genomes.front().genes.empty()) break;
            Genome::Gene& original = genomes.front().genes.front();
            bool removeGene = true;
            for (auto& genome : genomes) {
                if (genome.genes.empty()) {
                    removeGene = false;
                    break;
                }
                Genome::Gene& gene = genome.genes.front();
                if (
                        gene.enabled ||
                        gene.innovation != original.innovation ||
                        gene.from != original.from ||
                        gene.to != original.to) {
                    removeGene = false;
                    break;
                }
            }
            if (removeGene) {
                for (auto& genome : genomes) {
                    genome.genes.erase(genome.genes.begin());
                }
            } else {
                break;
            }
        }
    }


}