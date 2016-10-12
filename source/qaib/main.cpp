#include <qaib/app/PlayingGameApplication.hpp>
#include <qaib/app/MultithreadedTrainer.hpp>
#include <iostream>
#include <sstream>
#include <third-party/cmdline.hpp>

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
        cmdline::parser a;
        a.add<bool>("nojit", 0, "disable jit", false, false);
        a.add<std::string>("pop", 'p', "population file", false, "data/default_ai.pop");

        a.parse_check(argc, argv);

		PlayingGameApplication::Config cfg;
		cfg.useAI = true;
		cfg.useJIT = !a.get<bool>("nojit");;
		cfg.aiFilename = a.get<std::string>("pop");
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
    } else if (strcmp(argv[1], "train") == 0) {
		cmdline::parser a;
        a.add<int>("threads", 't', "num of threads", false, 1, cmdline::range(1, 128));
        a.add<bool>("nojit", 0, "disable jit", false, false);
        a.add<int>("pop-size", 'p', "population size", true, 0, cmdline::range(1, 10000000));
        a.add<int>("rounds", 'r', "num of rounds", true, 0, cmdline::range(1, 10000000));
        a.add<int>("world-size", 0, "world size", false, 20);
        a.add<int>("world-obstructions", 0, "number of obstructions", false, 15);
        a.add<unsigned>("world-seed", 's', "world seed", false, 0);
        a.add<int>("continue", 'c', "continue from population", false, 0);
        a.add<std::string>("match-with", 0, "matches with other poplation", false);

        a.parse_check(argc, argv);

		MultithreadedTrainer::Config cfg;
		cfg.threads = a.get<int>("threads");
        cfg.useJIT = !a.get<bool>("nojit");
		cfg.populationSize = a.get<int>("pop-size");
		cfg.bigRoundsNum = a.get<int>("rounds");
		cfg.world.size = a.get<int>("world-size");
		cfg.world.obstructionCount = a.get<int>("world-obstructions");
		cfg.world.seed = a.get<unsigned>("world-seed");
		cfg.startFromGeneration = a.get<int>("continue");
        cfg.matchWith = a.get<std::string>("match-with");
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