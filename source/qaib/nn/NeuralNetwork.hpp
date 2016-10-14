#pragma once

#include <qaib/util/Typedef.hpp>
#include <qaib/nn/Genome.hpp>
#include <vector>
#include <list>
#include <map>

namespace qaib {

    class JITNeuralNetwork;

    class NeuralNetwork {
    public:
        virtual std::vector<float> execute(std::vector<float> inputs) = 0;
        virtual ~NeuralNetwork();
    };

    class PlainNeuralNetwork: public NeuralNetwork {
    protected:

        friend class Genome;
        friend class JITNeuralNetwork;

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
        virtual std::vector<float> execute(std::vector<float> inputs) override;
        std::string renderGraph() const;
    };

}