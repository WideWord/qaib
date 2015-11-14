//
//  ActivationFunction.cpp
//  qaib
//
//  Created by Kirill Vilkov on 14.11.15.
//
//

#include "ActivationFunction.hpp"
#include <cmath>

namespace qaib {
    
    ActivationFunction ActivationFunction::sigmoid(
    [](float x) {
        return 1.0f / (1.0f + exp(x));
    },
    [](float x) {
        return (1.0f / (1.0f + exp(x))) * (1.0f - 1.0f / (1.0f + exp(x)));
    });
    
}