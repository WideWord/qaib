#include <qaib/neuro/Perceptron.hpp>
#include <qaib/neuro/Neuron.hpp>

#define PERCEPTRON_DEFAULT_WEIGHT 1.0f

namespace qaib {
    
    Perceptron::Perceptron(std::vector<int> config, ActivationFunction activationFn) {
        for (int i = 0, iend = config.front(); i < iend; ++i) {
            inputNeurons.push_back(createNeuron(activationFn));
        }
        
        std::vector<Neuron*> lastLayer = inputNeurons;
        std::vector<Neuron*> currentLayer;
        
        for (int i = 1, iend = config.size(); i < iend; ++i) {
            for (int j = 0, jend = config[i]; j < jend; ++j)
            {
                Neuron* neuron = createNeuron(activationFn);
                currentLayer.push_back(neuron);
                for (auto neuronFromLastLayer : lastLayer) {
                    neuron->connectTo(neuronFromLastLayer, PERCEPTRON_DEFAULT_WEIGHT);
                }
            }
            lastLayer = currentLayer;
            currentLayer.clear();
        }
        
        outputNeuron = createNeuron(activationFn);
        
        for (auto neuronFromLastLayer : lastLayer) {
            outputNeuron->connectTo(neuronFromLastLayer, PERCEPTRON_DEFAULT_WEIGHT);
        }
    }
    
    Perceptron::~Perceptron() {}
    
    float Perceptron::evaluate(std::vector<float> input) {
        resetEvaluationState();
        
        for (int i = 0, iend = inputNeurons.size(); i < iend; ++i) {
            inputNeurons[i]->setValue(input[i]);
        }
        
        return outputNeuron->evaluate();
    }
}