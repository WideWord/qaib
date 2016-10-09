#pragma once

#include <SFML/Network/Packet.hpp>

namespace qaib {

    using Innovation = uint64_t;

    class InnovationGenerator {
    private:
        Innovation nextInnovation;
    public:
        inline InnovationGenerator() {
            nextInnovation = 0;
        }
        inline InnovationGenerator(sf::Packet& packet) {
            packet >> (sf::Uint64&)nextInnovation;
        }
        inline void writeTo(sf::Packet& packet)const {
            packet << (sf::Uint64&)nextInnovation;
        }
        inline Innovation generate() {
            return nextInnovation++;
        }
    };

}