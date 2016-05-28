#include <qaib/nn/NeuralNetwork.hpp>
#include <math.h>

namespace qaib {

    std::vector<float> NeuralNetwork::exec(const std::vector<float>& inputs) {
        for (auto& neuron : neurons) {
            neuron.power = 0;
            neuron.isCompleted = false;
        }
        {
            int i = 0;
            for (auto input : inputs) {
                neurons[i].power = input;
                neurons[i].isCompleted = true;
                i += 1;
            }
        }
        for (auto& link : links) {
            auto& inputNeuron = neurons[link.inputNeuron];
            auto& outputNeuron = neurons[link.outputNeuron];

            if (!inputNeuron.isCompleted) {
                inputNeuron.power = 1.0f / (1.0f + expf(-inputNeuron.power));
                inputNeuron.isCompleted = true;
            }

            outputNeuron.power += inputNeuron.power * link.weight;
        }

        auto outputNeuronsStart = neurons.size() - outputsCount;
        auto outputNeuronsEnd = neurons.size();

        std::vector<float> res(outputsCount);

        for (auto i = outputNeuronsStart; i < outputNeuronsEnd; ++i) {
            auto& neuron = neurons[i];

            if (!neuron.isCompleted) {
                neuron.power = 1.0f / (1.0f + expf(-neuron.power));
                neuron.isCompleted = true;
            }

            res.push_back(neuron.power);
        }

        return std::move(res);
    }


    void NeuralNetwork::crossover(NeuralNetwork &other) {

    }

    void NeuralNetwork::mutate() {

    }

}