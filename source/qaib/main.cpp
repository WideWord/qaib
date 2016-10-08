#include <qaib/app/PlayingGameApplication.hpp>


#include <qaib/nn/NeuralNetwork.hpp>
#include <qaib/app/TrainingApplication.hpp>

using namespace qaib;

int main() {
	return TrainingApplication().exec();
}