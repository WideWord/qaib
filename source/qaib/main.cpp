#include <qaib/app/PlayingGameApplication.hpp>

#include <qaib/nn/NeuralNetwork.hpp>
#include <qaib/nn/NeuralNetworkFactory.hpp>

using namespace qaib;

int main() {
	//return PlayingGameApplication().exec();

    auto nn = NeuralNetworkFactory::buildPerceptron({2, 3, 1});

    nn->mutate();

    return 0;
}