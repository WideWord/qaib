#include <qaib/game/Bullet.hpp>
#include <qaib/util/VectorConversion.hpp>

namespace qaib {

    Bullet::Bullet(b2Body* body) {
        physicsBody = body;

        b2CircleShape shape;
        shape.m_radius = 0.05f;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1;
        body->CreateFixture(&fixtureDef);
        body->SetUserData(this);

        active = true;
    }

    glm::vec2 Bullet::getPosition() const {
        return convert<glm::vec2>(physicsBody->GetPosition());
    }

    void Bullet::setPosition(const glm::vec2& pos) {
        physicsBody->SetTransform(convert<b2Vec2>(pos), physicsBody->GetAngle());
    }

    float Bullet::getRotation() const {
        return physicsBody->GetAngle();
    }

    void Bullet::setRotation(float rot) {
        physicsBody->SetTransform(physicsBody->GetPosition(), rot);
    }

}