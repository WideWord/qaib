#pragma once

#include <vector>
#include <functional>

namespace qaib {
    
    class Neuron {
    public:
        struct Connection {
            Neuron * neuron;
            float weight;
            inline Connection(Neuron * _neuron, float _weight) {
                neuron = _neuron;
                weight = _weight;
            }
        };
    private:
        std::vector<Connection> connections;
        std::function<float(float)> activationFn;
    protected:
        friend class NeuronNetwork;
        bool evaluated;
        float value;
        
        inline Neuron(std::function<float(float)> _activationFn) {
            activationFn = _activationFn;
        }
    public:
        inline void connectTo(Neuron * neuron, float weight) {
            connections.push_back(Connection(neuron, weight));
        }
        float evaluate();
        inline void setValue(float _value) {
            evaluated = true;
            value = _value;
        }
    };
    
}
