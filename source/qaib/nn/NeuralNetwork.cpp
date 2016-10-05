#include <qaib/nn/NeuralNetwork.hpp>

namespace qaib {

    std::vector<float> NeuralNetwork::execute(std::vector<float> inputData) {

        std::map<Neuron, float> powers;

        for (int i = 0, iend = (int)inputData.size(); i < iend; ++i) {
            powers[inputs[i]] = inputData[i];
        }

        for (auto& n : executionRules) {
            float power = 0;
            for (auto& link : n.inputs) {
                power += powers[link.from] * link.weight;
            }
            powers[n.neuron] = power > 0 ? 1 : -1;
        }

        std::vector<float> res;

        for (auto output : outputs) {
            res.push_back(powers[output]);
        }

        return std::move(res);
    }


}