#include <qaib/game/Obstruction.hpp>
#include <qaib/util/VectorConversion.hpp>
#include <random>

namespace qaib {

    Obstruction::Obstruction(b2Body *body) {
        physicsBody = body;


        b2Vec2 points[3];

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(-2.0, 2.0);

        for (int i = 0; i < 3; ++i) {
            points[i] = b2Vec2(dist(mt), dist(mt));
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