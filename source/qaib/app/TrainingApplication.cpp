#include <qaib/app/TrainingApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/NeuralNetworkPawnController.hpp>
#include <qaib/util/Random.hpp>
#include <fstream>
#include <sstream>
#include <qaib/util/VectorConversion.hpp>

namespace qaib {

    TrainingApplication::TrainingApplication() : population(30, 4 + 12, 4), aiVision(4, 3, 4) {
        generationCount = 0;
        gameWorld = nullptr;
        aPawn = nullptr;
        bPawn = nullptr;
    }

    void TrainingApplication::init() {
        nextTest();
    }

    void TrainingApplication::newGeneration(){

        generationCount += 1;

        if (fitness.size() > 0) {
            population.makeSelection(30, fitness);
            fitness.clear();
        }

        for (auto& net : population.getNeuralNetworks()) {
            testQueue.push(net);
        }

        sf::Packet packet;
        population.writeTo(packet);

        std::stringstream ss;
        ss << "populations/" << generationCount << ".pop";

        std::ofstream out(ss.str());
        out.write((const char*)packet.getData(), packet.getDataSize());

    }

    void TrainingApplication::nextTest() {
        roundFrames = 0;

        if (aPawn && bPawn) {

            auto score = aPawn->getScore();
            if (score < 0.1f) {
                score = 0.1f;
            }
            fitness.push_back(score / (aPawn->getHealth() / 10.0f + 0.1f));

            score = bPawn->getScore();
            if (score < 0.1f) {
                score = 0.1f;
            }
            fitness.push_back(score / (bPawn->getHealth() / 10.0f + 0.1f));

            aPawn = nullptr;
            bPawn = nullptr;
            gameWorld = nullptr;
        }

        if (testQueue.empty()) {
            newGeneration();
        }

        auto aNet = testQueue.front();
        testQueue.pop();
        auto bNet = testQueue.front();
        testQueue.pop();

        gameWorld = Ref<GameWorld>(new GameWorld(20, 10));
        gameRenderer.setGameWorld(gameWorld.get());

        aPawn = gameWorld->createPawn();
        bPawn = gameWorld->createPawn();

        aPawn->useController<NeuralNetworkPawnController>(aNet, bPawn, aiVision);
        bPawn->useController<NeuralNetworkPawnController>(bNet, aPawn, aiVision);

        aPawn->setPosition(glm::vec2(Random::getFloat(-2, 2), Random::getFloat(-2, 2)));
        aPawn->setRotation(Random::getFloat(-M_PI, M_PI));
        bPawn->setPosition(glm::vec2(Random::getFloat(-2, 2), Random::getFloat(-2, 2)));
        bPawn->setRotation(Random::getFloat(-M_PI, M_PI));


    }

    void TrainingApplication::doFrame(float deltaTime) {
        gameWorld->doTick(1.0f / 30.0f);
        roundFrames += 1;

        if (roundFrames > 30 * 8) {
            nextTest();
        }

        gameRenderer.drawFrame(getMainTarget());

        auto& texture = aiVision.drawFrame(*(gameWorld.get()), *(aPawn.get()));

        sf::Sprite sprite(texture);
        sprite.setScale(0.3f, 0.3f);
        sprite.setPosition(convert<sf::Vector2f>(aPawn->getPosition() + glm::vec2(0, 1)));
        getMainTarget().draw(sprite);
    }

}