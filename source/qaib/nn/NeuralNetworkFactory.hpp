#pragma once

#include <qaib/util/Typedef.hpp>
#include <vector>

namespace qaib {

    class NeuralNetwork;

    class NeuralNetworkFactory {
    public:
        static Ref<NeuralNetwork> buildPerceptron(const std::vector<int>& layers);
    };

}