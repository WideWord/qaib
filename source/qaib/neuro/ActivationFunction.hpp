#pragma once

#include <functional>

namespace qaib {
    
    class ActivationFunction {
    public:
        const std::function<float(float)> activationFn;
        const std::function<float(float)> derivativeActivationFn;
        
        inline ActivationFunction(std::function<float(float)> _activationFn, std::function<float(float)> _derivativeActivationFn)
        : activationFn(_activationFn), derivativeActivationFn(_derivativeActivationFn) {}
        
        inline ActivationFunction(const ActivationFunction& other)
        : activationFn(other.activationFn), derivativeActivationFn(other.derivativeActivationFn) {}
        
        static ActivationFunction sigmoid;
    };
    
}