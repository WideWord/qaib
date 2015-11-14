#include <qaib/neuro/Perceptron.hpp>
#include <qaib/neuro/Neuron.hpp>

namespace qaib {
    
    Perceptron::Perceptron(std::vector<int> config, ActivationFunction activationFn) {
        for (int i = 0, iend = config.front(); i < iend; ++i) {
            inputNeurons.push_back(createNeuron(activationFn));
        }
    }
    
    Perceptron::~Perceptron() {}
    
    float Perceptron::evaluate(std::vector<float> input) {
        resetEvaluatedNetwork();
        
        for (int i = 0, iend = inputNeurons.size(); i < iend; ++i) {
            inputNeurons[i]->setValue(input[i]);
        }
        
        return outputNeuron->evaluate();
    }
}