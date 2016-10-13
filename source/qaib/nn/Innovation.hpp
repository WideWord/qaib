#pragma once

#include <SFML/Network/Packet.hpp>
#include <unordered_map>

namespace qaib {

    using Innovation = uint64_t;

    class InnovationGenerator {
    private:
        Innovation nextInnovation;
        std::unordered_map<uint64_t, Innovation> cache;
    public:
        inline InnovationGenerator() {
            nextInnovation = 1;
        }
        inline Innovation cachedLinkBetween(Innovation a, Innovation b) {
            auto it = cache.find(a + b >> 32);
            if (it == cache.end()) return 0;
            else return it->second;
        }
        inline void addCachedLink(Innovation a, Innovation b, Innovation link) {
            cache[a + b >> 32] = link;
        }
        inline InnovationGenerator(sf::Packet& packet) {
            using namespace sf;
            packet >> (Uint64&)nextInnovation;
            Uint64 size;
            packet >> size;
            for (Uint64 i = 0; i < size; ++i) {
                Uint64 key = 0, link = 0;
                packet >> key >> link;
                cache[key] = link;
            }

        }
        inline void writeTo(sf::Packet& packet) const {
            using namespace sf;
            packet << (Uint64)nextInnovation;
            packet << (Uint64)cache.size();
            for (auto link : cache) {
                packet << (Uint64)link.first << (Uint64) link.second;
            }
        }
        inline Innovation generate() {
            return nextInnovation++;
        }
    };

}