#include <qaib/game/Obstruction.hpp>
#include <qaib/util/VectorConversion.hpp>
#include <random>
#include <glm/gtx/rotate_vector.hpp>

namespace qaib {

    Obstruction::Obstruction(std::mt19937& mt, b2Body *body) {
        physicsBody = body;

        std::uniform_real_distribution<float> dist(-2.0, 2.0);
        std::uniform_real_distribution<float> rdist(M_PI_4, M_PI_2);


        glm::vec2 generatedPoints[3];

        do {
            for (int i = 0; i < 2; ++i) {
                generatedPoints[i] = glm::vec2(dist(mt), dist(mt));
            }
            generatedPoints[2] =
                    glm::rotate(generatedPoints[0] - generatedPoints[1], rdist(mt)) * rdist(mt) + generatedPoints[1];
        } while (glm::length(generatedPoints[0] - generatedPoints[1]) < 0.5 ||
                glm::length(generatedPoints[1] - generatedPoints[2]) < 0.5 ||
                glm::length(generatedPoints[0] - generatedPoints[2]) < 0.5);
        b2Vec2 points[3];



        for (int i = 0; i < 3; ++i) {
            points[i] = convert<b2Vec2>(generatedPoints[i]);
            this->points[i].position = convert<sf::Vector2f>(points[i]);
            this->points[i].texCoords = this->points[i].position * 75.0f;
        }

        b2PolygonShape shape;
        shape.Set(points, 3);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1;
        body->CreateFixture(&fixtureDef);
    }

    glm::vec2 Obstruction::getPosition() const {
        return convert<glm::vec2>(physicsBody->GetPosition());
    }

    void Obstruction::setPosition(const glm::vec2& pos) {
        physicsBody->SetTransform(convert<b2Vec2>(pos), physicsBody->GetAngle());
    }

    float Obstruction::getRotation() const {
        return physicsBody->GetAngle();
    }

    void Obstruction::setRotation(float rot) {
        physicsBody->SetTransform(physicsBody->GetPosition(), rot);
    }

}