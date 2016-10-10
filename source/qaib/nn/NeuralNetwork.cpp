#include <qaib/nn/NeuralNetwork.hpp>
#include <cmath>

namespace qaib {

    NeuralNetwork::~NeuralNetwork() {}

    std::vector<float> PlainNeuralNetwork::execute(std::vector<float> inputData) {

        std::map<Neuron, float> powers;

        for (int i = 0, iend = (int)inputData.size(); i < iend; ++i) {
            powers[inputs[i]] = inputData[i];
        }

        for (auto& n : executionRules) {
            float power = 0;
            for (auto& link : n.inputs) {
                power += powers[link.from] * link.weight;
            }
            powers[n.neuron] = 1.0f / (1.0f +  expf(-power)) * 2.0f - 1.0f;
        }

        std::vector<float> res;

        for (auto output : outputs) {
            res.push_back(powers[output]);
        }

        return std::move(res);
    }


}