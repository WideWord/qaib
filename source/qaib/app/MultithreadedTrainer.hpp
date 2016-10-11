#pragma once
#include <mutex>
#include <vector>
#include <map>
#include <qaib/util/Typedef.hpp>
#include <condition_variable>
#include <qaib/game/GameWorld.hpp>

namespace qaib {

    class Population;
    class NeuralNetwork;

    class MultithreadedTrainer {
    public:
        struct Config {
            GameWorld::Config world;
            int threads;
            int bigRoundsNum;
            int populationSize;
            int startFromGeneration;
            bool useJIT;
        };

        void run(const Config& config);
    private:
        int aCtr;
        int bCtr;
        int bigRoundCtr;
        std::mutex roundCtrsMutex;

        Config config;

        Ref<Population> population;
        int generation;

        std::vector<bool> generationDone;
        std::mutex generationDoneMutex;
        std::condition_variable generationDoneCond;

        std::vector<float> fitness;
        std::mutex fitnessMutex;
        std::vector<std::vector<Ref<NeuralNetwork>>> nets;
        std::vector<int> netLinksCount;
        std::vector<int> netNeuronsCount;

        void worker(int thread);
        float calcFitness(float score, float health, int linksCount, int neuronsCount);
    };

}