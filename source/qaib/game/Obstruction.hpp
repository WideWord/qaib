#pragma once

#include <qaib/game/Movable.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>


namespace qaib {

    class GameWorld;

    class Obstruction: public Movable {
    private:
        b2Body* physicsBody;
        sf::Vertex points[3];
    protected:
        friend class ObstructionGenerator;
        explicit Obstruction(b2Body* body);
    public:
        inline b2Body* getPhysicsBody() {
            return physicsBody;
        }

        virtual glm::vec2 getPosition() const override;
        virtual void setPosition(const glm::vec2& pos) override;

        virtual float getRotation() const override;
        virtual void setRotation(float rot) override;

        inline const sf::Vertex* getPoints() const {
            return points;
        }
    };

}