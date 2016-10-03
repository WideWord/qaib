#pragma once

#include <vector>
#include <qaib/nn/Genome.hpp>
#include <SFML/Network/Packet.hpp>

namespace qaib {

    class Population {
    private:
        InnovationGenerator innovationGenerator;
        std::vector<Genome> genomes;
    public:
        Population(int size, int inputsCount, int outputsCount);
        std::vector<Ref<NeuralNetwork>> getNeuralNetworks() const;
        void makeSelection(int newSize, std::vector<float> succsess);

        void writeTo(sf::Packet& packet) const;
        Population(sf::Packet& packet);
    };


}