#include <qaib/app/TrainingApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/NeuralNetworkPawnController.hpp>
#include <qaib/util/Random.hpp>
#include <fstream>
#include <sstream>
#include <qaib/util/MakeString.hpp>

namespace qaib {

    TrainingApplication::TrainingApplication() {
        generationCount = 0;
        gameWorld = nullptr;
        aPawn = nullptr;
        bPawn = nullptr;
        population = Ref<Population>(new Population(30, 7, 4));
    }

    TrainingApplication::TrainingApplication(int startFromGeneration) {
        generationCount = startFromGeneration;
        gameWorld = nullptr;
        aPawn = nullptr;
        bPawn = nullptr;
        population = Population::load(MakeString() << "populations/" << startFromGeneration << ".pop");
    }

    void TrainingApplication::init() {
        nextTest();
    }

    void TrainingApplication::newGeneration(){

        generationCount += 1;

        if (fitness.size() > 0) {
            population->makeSelection(30, fitness);
            fitness.clear();
        }

        for (auto& genome : population->getGenomes()) {
            auto ptr = &genome;
            testQueue.push(ptr);
        }

        sf::Packet packet;
        population->writeTo(packet);

        std::stringstream ss;
        ss << "populations/" << generationCount << ".pop";

        std::ofstream out(MakeString() << "populations/" << generationCount << ".pop");
        out.write((const char*)packet.getData(), packet.getDataSize());

    }

    void TrainingApplication::nextTest() {
        roundFrames = 0;

        if (aPawn && bPawn) {

            auto fitnessFunc = [](float score, float health, int neuronsCount) {
                if (score < 0.1f) {
                    score = 0.1f;
                }
                return score * 0.1f + health / 100.0f - powf(aNeuronsCount, 2) / 10000.0f;
            };

            fitness.push_back(fitnessFunc(aPawn->getScore(), aPawn->getHealth(), aNeuronsCount));
            fitness.push_back(fitnessFunc(bPawn->getScore(), bPawn->getHealth(), bNeuronsCount));

            aPawn = nullptr;
            bPawn = nullptr;
            gameWorld = nullptr;
        }

        if (testQueue.empty()) {
            newGeneration();
        }

        auto& aGenome = *(testQueue.front());
        testQueue.pop();
        auto& bGenome = *(testQueue.front());
        testQueue.pop();

        auto aNet = aGenome.buildNeuralNetwork();
        auto bNet = bGenome.buildNeuralNetwork();

        aNeuronsCount = aGenome.getNeuronsCount();
        bNeuronsCount = bGenome.getNeuronsCount();

        gameWorld = Ref<GameWorld>(new GameWorld(20, 0));
        gameRenderer.setGameWorld(gameWorld.get());

        aPawn = gameWorld->createPawn();
        bPawn = gameWorld->createPawn();

        aPawn->useController<NeuralNetworkPawnController>(aNet, bPawn);
        bPawn->useController<NeuralNetworkPawnController>(bNet, aPawn);

        aPawn->setPosition(glm::vec2(-8, 0));
        aPawn->setRotation(Random::getFloat(-M_PI, M_PI));
        bPawn->setPosition(glm::vec2(8, 0));
        bPawn->setRotation(Random::getFloat(-M_PI, M_PI));


    }

    void TrainingApplication::doFrame(float deltaTime) {
        gameWorld->doTick(1.0f / 30.0f);
        roundFrames += 1;

        if (roundFrames > 30 * 8) {
            nextTest();
        }

        gameRenderer.drawFrame(getMainTarget());
    }

}