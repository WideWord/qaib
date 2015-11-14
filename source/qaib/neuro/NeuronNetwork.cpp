#include <qaib/neuro/NeuronNetwork.hpp>
#include <qaib/neuro/Neuron.hpp>

namespace qaib {
    
    NeuronNetwork::~NeuronNetwork() {
        for (auto neuron : neurons) {
            delete neuron;
        }
    }
    
    void NeuronNetwork::resetEvaluationState() {
        for (auto neuron: neurons) {
            neuron->evaluated = false;
        }
    }
    
    Neuron* NeuronNetwork::createNeuron(ActivationFunction activationFn) {
        auto neuron = new Neuron(activationFn);
        neurons.push_back(neuron);
        return neuron;
    }
    
}