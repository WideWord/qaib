#include <qaib/neuro/Neuron.hpp>

namespace qaib {
    
    float Neuron::evaluate() {
        if (evaluated)
            return value;
        
        value = 0;
        
        for (auto& connection : connections) {
            value = connection.weight * connection.neuron->evaluate();
        }
        
        value = activationFn(value);
        
        evaluated = true;
        return value;
    }
    
}