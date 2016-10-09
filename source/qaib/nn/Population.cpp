#include <qaib/nn/Population.hpp>
#include <qaib/util/Random.hpp>

namespace qaib {

    Population::Population(int size, int inputsCount, int outputsCount) {
        Genome initialGenome(innovationGenerator, inputsCount, outputsCount);
        for (int i = 0; i < 5; ++i) {
            initialGenome.mutate(innovationGenerator);
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

    void Population::makeSelection(int newSize, std::vector<float> success) {

        float successSum = 0;
        for (auto s : success) {
            successSum += s;
        }
        for (auto& s : success) {
            s /= successSum;
        }

        std::vector<Genome> newGenomes;

        for (int i = 0; i < newSize; ++i) {

            Genome* a = nullptr;
            Genome* b = nullptr;

            float ar = Random::getFloat(0, 1);
            float br = Random::getFloat(0, 1);

            for (int i = 0, iend = genomes.size(); i < iend; ++i) {
                ar -= success[i];
                br -= success[i];

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
            if (Random::getInt(0, 100) > 50) {
                result.mutate(innovationGenerator);
            }
            newGenomes.push_back(result);
        }

        genomes = newGenomes;
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

}