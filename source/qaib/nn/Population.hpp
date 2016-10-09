#pragma once

#include <vector>
#include <qaib/nn/Genome.hpp>
#include <SFML/Network/Packet.hpp>
#include <qaib/util/Typedef.hpp>

namespace qaib {

    class Population {
    private:
        InnovationGenerator innovationGenerator;
        std::vector<Genome> genomes;

        void deleteOldGenes();
    public:
        Population(int size, int inputsCount, int outputsCount);

        std::vector<Ref<NeuralNetwork>> getNeuralNetworks() const;
        inline const std::vector<Genome>& getGenomes() const {
            return genomes;
        }

        void makeSelection(int newSize, std::vector<float> fitness);

        void writeTo(sf::Packet &packet) const;

        Population(sf::Packet &packet);

        static Ref<Population> load(const std::string &filename);
    };
}