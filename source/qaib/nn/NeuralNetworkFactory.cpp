#include <qaib/nn/NeuralNetworkFactory.hpp>
#include <qaib/nn/NeuralNetwork.hpp>

namespace qaib {

    Ref<NeuralNetwork> NeuralNetworkFactory::buildPerceptron(const std::vector<int>& layers) {

        auto nn = std::make_shared<NeuralNetwork>();

        int lastStart = 0;
        int lastEnd = 0;

        for (int i = 0, layerCount = layers.size(); i < layerCount; ++i) {


            int newLastStart = nn->neurons.size();

            for (int j = 0, neuronCount = layers[i]; j < neuronCount; ++j) {
                nn->neurons.push_back(NeuralNetwork::Neuron());

                if (i != 0) {
                    for (int k = lastStart; k < lastEnd; ++k) {
                        auto current = lastEnd + j;
                        NeuralNetwork::Link link;
                        link.inputNeuron = k;
                        link.outputNeuron = current;
                        link.weight = 0;
                        nn->links.push_back(link);
                    }
                }
            }

            lastStart = newLastStart;
            lastEnd = lastStart + layers[i];

        }

        nn->inputsCount = layers[0];
        nn->outputsCount = layers[layers.size() - 1];

        return nn;
    }

}