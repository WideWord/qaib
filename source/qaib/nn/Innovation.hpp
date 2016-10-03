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
            packet >> nextInnovation;
        }
        inline void writeTo(sf::Packet& packet)const {
            packet << nextInnovation;
        }
        inline Innovation generate() {
            return nextInnovation++;
        }
    };

}