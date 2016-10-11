#include <qaib/app/PlayingGameApplication.hpp>
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
        std::cout << "Usage: qaib [train-new, train-continue, play, world, graph]\n";
		return -1;
	}

	if (strcmp(argv[1], "play") == 0) {
		if (argc < 3) {
			std::cout << "Usage: qaib play [use jit] [ai population]\n";
			return -1;
		}
		PlayingGameApplication::Config cfg;
		cfg.useAI = true;
		cfg.useJIT = parseIntArg(argv[1]) > 0;
		cfg.aiFilename = std::string(argv[2]);
		return PlayingGameApplication(cfg).exec();
	} else if (strcmp(argv[1], "world") == 0) {
		if (argc < 5) {
			std::cout << "Usage: qaib world [size] [obstructions] [seed]\n";
			return -1;
		}
		PlayingGameApplication::Config cfg;
		cfg.useAI = false;
		cfg.world.size = parseIntArg(argv[2]);
		cfg.world.obstructionCount = parseIntArg(argv[3]);
		cfg.world.seed = (unsigned)parseIntArg(argv[4]);
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
    } else if (strcmp(argv[1], "train-new") == 0) {
		if (argc < 9) {
			std::cout << "Usage qaib train-new [threads] [use jit (0 or 1)] [population size] [rounds] [world size] [obstructions] [seed]\n";
			return -1;
		}
		MultithreadedTrainer::Config cfg;
		cfg.threads = parseIntArg(argv[2]);
        cfg.useJIT = parseIntArg(argv[3]) > 0;
		cfg.populationSize = parseIntArg(argv[4]);
		cfg.bigRoundsNum = parseIntArg(argv[5]);
		cfg.world.size = parseIntArg(argv[6]);
		cfg.world.obstructionCount = parseIntArg(argv[7]);
		cfg.world.seed = (unsigned)parseIntArg(argv[8]);
		cfg.startFromGeneration = 0;
		MultithreadedTrainer trainer;
		trainer.run(cfg);
		return 0;
	} else if (strcmp(argv[1], "train-continue") == 0) {
		if (argc < 7) {
			std::cout << "Usage qaib train-continue [threads] [use jit (0 or 1)] [population size] [rounds] [population number]\n";
			return -1;
		}
		MultithreadedTrainer::Config cfg;
		cfg.threads = parseIntArg(argv[2]);
		cfg.useJIT = parseIntArg(argv[3]) > 0;
		cfg.populationSize = parseIntArg(argv[4]);
		cfg.bigRoundsNum = parseIntArg(argv[5]);
		cfg.startFromGeneration = parseIntArg(argv[6]);
		MultithreadedTrainer trainer;
		trainer.run(cfg);
		return 0;
	} else {
		std::cout << "Usage: qaib [train-new, train-continue, play, world, graph]\n";
		return -1;
	}
}