#include <qaib/app/PlayingGameApplication.hpp>
#include <qaib/app/TrainingApplication.hpp>
#include <qaib/app/MultithreadedTrainer.hpp>
#include <iostream>
#include <sstream>

using namespace qaib;

int parseIntArg(const char* arg) {
	std::stringstream s(arg);
	int res;
	s >> res;
	return res;
}

int main(int argc, char** argv) {
	if (argc < 2) {
        std::cout << "Usage: qaib [train, train-gui, play, graph]\n";
		return -1;
	}

	if (strcmp(argv[1], "train-gui") == 0) {
		if (argc < 3) {
			return TrainingApplication().exec();
		} else {
			std::stringstream ss(argv[2]);
			int generation;
			ss >> generation;
			return TrainingApplication(generation).exec();
		}
	} else if (strcmp(argv[1], "play") == 0) {
		if (argc < 7) {
			std::cout << "Usage: qaib play [world size] [obstructions] [seed] [use jit] [ai population]\n";
			return -1;
		}
		PlayingGameApplication::Config cfg;
		cfg.world.size = parseIntArg(argv[2]);
		cfg.world.obstructionCount = parseIntArg(argv[3]);
		cfg.world.seed = (unsigned)parseIntArg(argv[4]);
		cfg.useJIT = parseIntArg(argv[5]) > 0;
		cfg.aiFilename = std::string(argv[6]);
		return PlayingGameApplication(cfg).exec();
	} else if (strcmp(argv[1], "graph") == 0) {
        if (argc < 3) {
            std::cout << "Usage: qaib graph [population file]\n";
            return -1;
        } else {
            std::string aiFilename(argv[2]);
            auto population = Population::load(aiFilename);
			std::cout << population->getGenomes().front().renderGraph();
			return 0;
        }
    } else if (strcmp(argv[1], "train") == 0) {
		if (argc < 10) {
			std::cout << "Usage qaib train [world size] [obstructions] [seed] [threads] [use jit (0 or 1)] [population size] [rounds] [start from generation]\n";
			return -1;
		}
		MultithreadedTrainer::Config cfg;
		cfg.world.size = parseIntArg(argv[2]);
		cfg.world.obstructionCount = parseIntArg(argv[3]);
		cfg.world.seed = (unsigned)parseIntArg(argv[4]);
		cfg.threads = parseIntArg(argv[5]);
        cfg.useJIT = parseIntArg(argv[6]) > 0;
		cfg.populationSize = parseIntArg(argv[7]);
		cfg.bigRoundsNum = parseIntArg(argv[8]);
		cfg.startFromGeneration = parseIntArg(argv[9]);
		MultithreadedTrainer trainer;
		trainer.run(cfg);
		return 0;
	} else {
		std::cout << "Usage: qaib [train, train-gui, play, graph]\n";
		return -1;
	}
}