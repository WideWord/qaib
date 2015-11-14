#pragma once

#include <vector>
#include <functional>
#include <qaib/neuro/ActivationFunction.hpp>

namespace qaib {
        
    class Neuron;
    
    class NeuronNetwork {
    private:
        std::vector<Neuron*> neurons;
    public:
        Neuron* createNeuron(ActivationFunction activationFn);
        void resetEvaluationState();
        
        virtual ~NeuronNetwork();
    };
    
}