#pragma once

#include <vector>
#include <functional>

namespace qaib {
    
    class Neuron;
    
    class NeuronNetwork {
    private:
        std::vector<Neuron*> neurons;
    public:
        Neuron* createNeuron(std::function<float(float)> activationFn);
        
        void setNotEvaluated();
        
        virtual ~NeuronNetwork();
    };
    
    class Perceptron : private NeuronNetwork {
    public:
        Perceptron(std::vector<int> config);
        float evaluate(std::vector<float> input);
    };
    
}