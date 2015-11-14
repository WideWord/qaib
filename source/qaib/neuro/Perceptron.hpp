#pragma once

#include <vector>

#include <qaib/neuro/NeuronNetwork.hpp>
#include <qaib/neuro/ActivationFunction.hpp>

namespace qaib {
    
    class Perceptron : private NeuronNetwork {
    private:
        std::vector<Neuron*> inputNeurons;
        Neuron* outputNeuron;
    public:
        Perceptron(std::vector<int> config, ActivationFunction activationFn = ActivationFunctions::sigmoid);
        virtual ~Perceptron();
        
        float evaluate(std::vector<float> input);
    };
    
}