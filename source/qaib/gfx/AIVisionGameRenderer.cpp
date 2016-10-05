#include <qaib/gfx/AIVisionGameRenderer.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/GameWorld.hpp>
#include <qaib/game/Obstruction.hpp>
#include <qaib/game/Bullet.hpp>

namespace qaib {

    AIVisionGameRenderer::AIVisionGameRenderer(float fovSize, int resolution, int samples) {
        this->fovSize = fovSize;
        this->samples = samples;
        pixelSize = fovSize / (float)resolution;
        target.create(resolution, resolution, false);
        bigTarget.create(resolution * samples, resolution * samples, false);
        bigTarget.setSmooth(false);

        redTexture.create(1, 1);

        uint32_t pixels = 0xFF0000FF;
        redTexture.update((uint8_t*)&pixels);
    }

    const sf::Texture& AIVisionGameRenderer::drawFrame(GameWorld& gameWorld, const Pawn& aiPawn) {
        bigTarget.clear(sf::Color::Red);

        sf::View view;
        view.setSize(fovSize, fovSize);

        auto pawnPos = aiPawn.getPosition();
        view.setCenter(pawnPos.x, pawnPos.y);
        view.setRotation(aiPawn.getRotation() / M_PI * 180.0f);

        bigTarget.setView(view);


        {
            auto radius = gameWorld.getWorldSize() * 0.5f;

            sf::CircleShape sand(radius, 80);
            sand.setPosition(-radius, -radius);
            sand.setFillColor(sf::Color::Black);
            bigTarget.draw(sand);
        }

        {
            auto& obstructions = gameWorld.getObstructions();

            for (auto obstruction : obstructions) {

                sf::RenderStates states;
                states.transform = obstruction->getSFTransform();
                //states.transform = states.transform.scale(1.0f / 200.0f, 1.0f / 200.0f);
                states.texture = &redTexture;
                auto points = obstruction->getPoints();
                bigTarget.draw(obstruction->getPoints(), 3, sf::Triangles, states);
                sf::Vertex line[2];
                line[0] = points[0];
                line[1] = points[1];
                bigTarget.draw(line, 2, sf::Lines, states);
                line[0] = points[1];
                line[1] = points[2];
                bigTarget.draw(line, 2, sf::Lines, states);
                line[0] = points[2];
                line[1] = points[0];
                bigTarget.draw(line, 2, sf::Lines, states);
            }
        }

        {
            sf::CircleShape circleShape(pixelSize * 0.65f, 8);
            circleShape.setFillColor(sf::Color::Green);
            circleShape.setPosition(-0.2f, -0.2f);

            auto &pawns = gameWorld.getPawns();
            for (auto pawn : pawns) {
                if (pawn.get() == &aiPawn) { continue; }
                sf::RenderStates states;
                states.transform = pawn->getSFTransform();
                states.blendMode = sf::BlendAdd;
                bigTarget.draw(circleShape, states);
            }
        }

        {
            sf::Vertex line[2];
            line[0] = sf::Vertex(sf::Vector2f(-0.25f, 0), sf::Color::Blue);
            line[1] = sf::Vertex(sf::Vector2f(0.25f, 0), sf::Color::Blue);

            auto &bullets = gameWorld.getBullets();
            for (auto bullet : bullets) {
                if (!bullet->getIsActive()) {
                    continue;
                }
                sf::RenderStates states;
                states.transform = bullet->getSFTransform();
                states.blendMode = sf::BlendAdd;
                bigTarget.draw(line, 2, sf::Lines, states);
            }
        }
        bigTarget.display();


        sf::Sprite sprite(bigTarget.getTexture());
        sprite.setScale(1.0f / samples, 1.0f / samples);

        target.draw(sprite);

        target.display();

        return target.getTexture();
    }

}