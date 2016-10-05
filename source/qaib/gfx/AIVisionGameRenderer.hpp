#pragma once

#include <SFML/Graphics.hpp>
#include <glm/vec2.hpp>

namespace qaib {

    class GameWorld;
    class Pawn;

    class AIVisionGameRenderer {
    private:
        sf::RenderTexture target;
        sf::RenderTexture bigTarget;
        sf::Image result;
        sf::Texture redTexture;
        float fovSize;
        int samples;
        float pixelSize;
    public:
        AIVisionGameRenderer(float fovSize, int resolution, int samples);
        const sf::Texture& drawFrame(GameWorld& gameWorld, const Pawn& pawn);

    };

}