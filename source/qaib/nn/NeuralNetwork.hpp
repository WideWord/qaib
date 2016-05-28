#pragma once

#include <qaib/util/Typedef.hpp>
#include <vector>

namespace qaib {

    class NeuralNetworkFactory;

    class NeuralNetwork {
    protected:
        friend class NeuralNetworkFactory;

        struct Neuron {
            float power;
            bool isCompleted;
        };

        struct Link {
            int inputNeuron;
            int outputNeuron;
            float weight;
        };

        std::vector<Neuron> neurons;
        std::vector<Link> links;

        int inputsCount;
        int outputsCount;
    public:

        std::vector<float> exec(const std::vector<float>& inputs);

        void crossover(NeuralNetwork& other);
        void mutate();
    };

}