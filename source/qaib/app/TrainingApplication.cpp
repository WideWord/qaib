#include <qaib/app/TrainingApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/NeuralNetworkPawnController.hpp>
#include <qaib/util/Random.hpp>
#include <fstream>
#include <sstream>
#include <qaib/util/MakeString.hpp>

namespace qaib {



    TrainingApplication::TrainingApplication(int startFromGeneration, bool gui) : Application(gui), gui(gui) {
        gameWorld = nullptr;
        aPawn = nullptr;
        bPawn = nullptr;
        if (startFromGeneration <= 0) {
            generationCount = 1;
            population = Ref<Population>(new Population(populationSize, NeuralNetworkPawnController::inputsCount, NeuralNetworkPawnController::outputsCount));
        } else {
            generationCount = startFromGeneration;
            population = Population::load(MakeString() << "populations/" << startFromGeneration << ".pop");
        }

        if (gui) {
            gameRenderer = Ref<GameRenderer>(new GameRenderer);
        }
    }

    void TrainingApplication::init() {
        aID = populationSize;
        bID = populationSize;
        nextTest();
    }

    void TrainingApplication::newGeneration() {

        generationCount += 1;

        if (fitness.size() > 0) {
            population->makeSelection(populationSize, fitness);
        } else {
            fitness.resize(populationSize);
        }

        for (int i = 0; i < populationSize; ++i) {
            fitness[i] = 0;
        }

        sf::Packet packet;
        population->writeTo(packet);

        std::stringstream ss;
        ss << "populations/" << generationCount << ".pop";

        std::ofstream out(MakeString() << "populations/" << generationCount << ".pop");
        out.write((const char*)packet.getData(), packet.getDataSize());

        aID = 0;
        bID = 0;

    }

    void TrainingApplication::nextTest() {
        roundFrames = 0;

        if (aPawn && bPawn) {

            auto fitnessFunc = [](float score, float health, int neuronsCount) {
                if (score < 0.1f) {
                    score = 0.1f;
                }
                return score + health / 10.0f - powf(neuronsCount, 2) / 10000.0f;
            };

            fitness[aID] += (fitnessFunc(aPawn->getScore(), aPawn->getHealth(), population->getGenomes()[aID].getNeuronsCount()));
            fitness[bID] += (fitnessFunc(bPawn->getScore(), bPawn->getHealth(), population->getGenomes()[bID].getNeuronsCount()));

            aPawn = nullptr;
            bPawn = nullptr;
            gameWorld = nullptr;
        }

        aID += 1;

        if (aID >= populationSize) {
            aID = 0;
            bID += 1;
            if (bID >= populationSize) {
                bID = 0;
                newGeneration();
            }
        }

        auto& aGenome = population->getGenomes()[aID];
        auto& bGenome = population->getGenomes()[bID];

        auto aNet = aGenome.buildNeuralNetwork();
        auto bNet = bGenome.buildNeuralNetwork();

        gameWorld = Ref<GameWorld>(new GameWorld(1000, 0));

        if (gui) {
            gameRenderer->setGameWorld(gameWorld.get());
        }

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

        if (gui) {
            gameRenderer->drawFrame(getMainTarget());
        }
    }

}