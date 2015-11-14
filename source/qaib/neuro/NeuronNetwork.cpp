#include <qaib/neuro/NeuronNetwork.hpp>
#include <qaib/neuro/Neuron.hpp>

namespace qaib {
    
    NeuronNetwork::~NeuronNetwork() {
        for (auto neuron : neurons) {
            delete neuron;
        }
    }
    
    void NeuronNetwork::resetEvaluatedNetwork() {
        for (auto neuron: neurons) {
            neuron->evaluated = false;
        }
    }
    
    Neuron* NeuronNetwork::createNeuron(std::function<float(float)> activationFn) {
        auto neuron = new Neuron(activationFn);
        neurons.push_back(neuron);
        return neuron;
    }
    
}