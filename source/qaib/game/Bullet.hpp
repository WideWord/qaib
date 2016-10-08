#pragma once

#include <qaib/game/Movable.hpp>
#include <qaib/game/GameWorld.hpp>

namespace qaib {

    class Bullet : public Movable {
    private:
        b2Body* physicsBody;
    protected:
        friend class GameWorld;
        explicit Bullet(b2Body* body);
        bool isActive;
        Ref<Pawn> shootBy;
    public:

        virtual glm::vec2 getPosition() const override;
        virtual void setPosition(const glm::vec2& pos) override;

        virtual float getRotation() const override;
        virtual void setRotation(float rot) override;

        inline b2Body* getPhysicsBody() {
            return physicsBody;
        }

        inline bool getIsActive() {
            return isActive;
        }
    };

}