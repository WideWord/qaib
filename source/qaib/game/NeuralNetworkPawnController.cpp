#include <qaib/game/NeuralNetworkPawnController.hpp>
#include <qaib/gfx/AIVisionGameRenderer.hpp>
#include <vector>
#include <qaib/nn/NeuralNetwork.hpp>
#include <qaib/game/Pawn.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <qaib/game/GameWorld.hpp>
#include <qaib/game/Bullet.hpp>

namespace qaib {

    void NeuralNetworkPawnController::prepareTick(GameWorld& gameWorld, float deltaTime) {
        using namespace glm;

        this->deltaTime = deltaTime;

        std::vector<float> inputs;

        auto me = getPawn();
        if (enemy && !enemy->isDead()) {
            vec2 dir = enemy->getPosition() - me->getPosition();
            vec2 forward = me->getForward();

            float dist = sqrtf((dir.x * dir.x + dir.y * dir.y)) / 50.0f;
            if (dist > 1.0f) dist = 1.0f;

            inputs.push_back(dist);

            dir = normalize(dir);
            auto angle = ((forward.x * dir.x + forward.y * dir.y) * 0.5f + 1);
            if (orientedAngle(forward, dir) < 0) angle = -angle;
            inputs.push_back(angle);


            auto speed = rotate(enemy->getSpeed(), me->getRotation());
            inputs.push_back(speed.x);
            inputs.push_back(speed.y);
        } else {
            inputs.push_back(0);
            inputs.push_back(0);
            inputs.push_back(1.0f);
            inputs.push_back(0);
        }

        float distToBullet = INFINITY;
        Ref<Bullet> nearestBullet;
        for (auto& bullet : gameWorld.getBullets()) {
            if (bullet->getShootBy().get() == me) continue;
            float dist = distance(bullet->getPosition(), me->getPosition());
            if (dist < distToBullet) {
                nearestBullet = bullet;
                distToBullet = dist;
            }
        }

        if (nearestBullet) {
            vec2 dir = nearestBullet->getPosition() - me->getPosition();
            vec2 forward = me->getForward();

            float dist = sqrtf((dir.x * dir.x + dir.y * dir.y)) / 50.0f;
            if (dist > 1.0f) dist = 1.0f;

            inputs.push_back(dist);

            dir = normalize(dir);
            auto angle = ((forward.x * dir.x + forward.y * dir.y) * 0.5f + 1);
            if (orientedAngle(forward, dir) < 0) angle = -angle;
            inputs.push_back(angle);

            float hit = dot(nearestBullet->getForward(), -dir);
            inputs.push_back(hit);
        } else {
            inputs.push_back(1.0f);
            inputs.push_back(0);
            inputs.push_back(-1);
        }

        inputs.push_back(me->getHealth() / me->getInitialHealth());
        inputs.push_back(enemy->getHealth() / enemy->getInitialHealth());

        inputs.push_back(me->getPosition().x / 10.0f);
        inputs.push_back(me->getPosition().y / 10.0f);

//        for (int i = 0; i < 12; ++i) {
//            float angle = (float)M_PI / 6.0f * ((float)i) + me->getRotation();
//            vec2 dir = rotate(vec2(1, 0), angle);
//            inputs.push_back(gameWorld.rayCast(me->getPosition(), dir) / 100.0f);
//        }

        outputs = net->execute(inputs);
    }

    glm::vec2 NeuralNetworkPawnController::movementDirection() {
        return glm::rotate(glm::vec2(outputs[0], outputs[1]), -(getPawn()->getRotation()));
    }

    glm::vec2 NeuralNetworkPawnController::turningTo() {
        return glm::rotate(glm::vec2(1, 0), getPawn()->getRotation() + outputs[2] * deltaTime * 4);

    }

    bool NeuralNetworkPawnController::shouldAttack() {
        return outputs[3] > 0;
    }


}