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

	if (strcmp(argv[1], "train") == 0) {
		if (argc < 3) {
			return TrainingApplication().exec();
		} else {
			std::stringstream ss(argv[2]);
			int generation;
			return TrainingApplication(generation).exec();
		}
	} else if (strcmp(argv[1], "play") == 0) {
		if (argc < 3) {
			return PlayingGameApplication("data/default_ai.pop").exec();
		} else {
			std::string aiFilename(argv[2]);
			return PlayingGameApplication(aiFilename).exec();
		}
	} else {
		std::cout << "Usage:\n\tqaib train [continue from generation]\n\tqaib play [population file]";
		return -1;
	}
}