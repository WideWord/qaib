#include <qaib/nn/NeuralNetwork.hpp>
#include <cmath>
#include <sstream>

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

    std::string PlainNeuralNetwork::renderGraph() const {
        std::stringstream ss;
        ss << "\ndigraph G {\nrankdir=LR;\nnode [shape=circle,color=green1];\n";


        std::list<std::string> inputNames = {
                "Dist to enemy",
                "Angle to enemy",
                "Dist to bullet",
                "Agnle to bullet",
                "Bullet angle to me",
                "My health",
                "Enemy health",
                "Pos X",
                "Pos Y"
        };

        std::list<std::string> outputNames = {
                "Move forward/backward",
                "Move left/right",
                "Turn",
                "Shoot"
        };


        ss << "subgraph inputs {\n node [style=solid,color=blue4, shape=box];\n";
        for (auto& input : inputs) {
            ss << input << " [label=\"" << inputNames.front() << "\"];\n";
            inputNames.pop_front();
        }
        ss << "}\n";

        ss << "subgraph outputs {\n  node [style=solid,color=red2, shape=box];\n";
        for (auto& output : outputs) {
            ss << output << " [label=\"" << outputNames.front() << "\"];\n";
            outputNames.pop_front();
        }
        ss << "}\n";

        int ctr = 1;

        for (auto& rule : executionRules) {
            ctr++;
            for (auto& link : rule.inputs) {
                ss << "edge [color=\"" << (link.weight * 0.12f + (1.0f - 0.25f)) << " 1.000 1.000\", label=\"" << ctr << "\"];\n";
                ss << link.from << " -> " << rule.neuron << ";\n";
            }
        }

        ss << "}\n";

        return ss.str();
    }


}