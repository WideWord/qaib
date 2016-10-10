#include <qaib/app/PlayingGameApplication.hpp>
#include <qaib/app/TrainingApplication.hpp>
#include <iostream>
#include <sstream>

using namespace qaib;

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "Usage:\n\tqaib train [continue from generation]\n\tqaib play [population file]";
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
	} else if (strcmp(argv[1], "train") == 0) {
		if (argc < 3) {
			return TrainingApplication(-1, false).exec();
		} else {
			std::stringstream ss(argv[2]);
			int generation;
			ss >> generation;
			return TrainingApplication(generation, false).exec();
		}
	} else if (strcmp(argv[1], "play") == 0) {
		if (argc < 3) {
			return PlayingGameApplication("data/default_ai.pop").exec();
		} else {
			std::string aiFilename(argv[2]);
			return PlayingGameApplication(aiFilename).exec();
		}
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
    } else {
		std::cout << "Usage:\n\tqaib train [continue from generation]\n\tqaib play [population file]\n";
        std::cout << "\tqaib graph [population file]\n";
		return -1;
	}
}