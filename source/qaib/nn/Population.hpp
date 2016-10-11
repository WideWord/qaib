#pragma once

#include <vector>
#include <qaib/nn/Genome.hpp>
#include <SFML/Network/Packet.hpp>
#include <qaib/util/Typedef.hpp>
#include <qaib/game/GameWorld.hpp>

namespace qaib {

    class Population {
    private:
        InnovationGenerator innovationGenerator;
        std::vector<Genome> genomes;

        void deleteOldGenes();

        GameWorld::Config worldConfig;
    public:
        Population(int size, int inputsCount, int outputsCount, const GameWorld::Config& worldConfig);

        inline GameWorld::Config getWorldConfig() {
            return worldConfig;
        }

        inline const std::vector<Genome>& getGenomes() const {
            return genomes;
        }

        inline int getSize() const {
            return genomes.size();
        }

        void makeSelection(int newSize, std::vector<float> fitness);

        void writeTo(sf::Packet &packet) const;

        Population(sf::Packet &packet);

        static Ref<Population> load(const std::string &filename);
    };
}