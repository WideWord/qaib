#pragma once

#include <vector>
#include <functional>

namespace qaib {
    
    typedef std::function<float(float)> ActivationFunction;
    
    class Neuron;
    
    class NeuronNetwork {
    private:
        std::vector<Neuron*> neurons;
    public:
        Neuron* createNeuron(ActivationFunction activationFn);
        void resetEvaluatedNetwork();
        virtual ~NeuronNetwork();
    };
    
}