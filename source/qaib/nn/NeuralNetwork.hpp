#pragma once

#include <qaib/util/Typedef.hpp>
#include <qaib/nn/Genome.hpp>
#include <vector>
#include <list>
#include <map>

namespace qaib {

    class NeuralNetwork {
    protected:

        friend class Genome;

        struct NeuronData {
            struct Link {
                Neuron from;
                float weight;
            };
            std::vector<Link> inputs;
            Neuron neuron;
            bool flag;
        };

        std::vector<NeuronData> executionRules;

        std::vector<Neuron> inputs;
        std::vector<Neuron> outputs;
    public:
        std::vector<float> execute(std::vector<float> inputs);
    };

}