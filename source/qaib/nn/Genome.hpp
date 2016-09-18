#pragma once

#include <qaib/nn/Innovation.hpp>
#include <vector>
#include <set>

namespace qaib {

    using Neuron = Innovation;

    class Genome {
    private:
        struct Gene {
            Innovation innovation;
            Neuron from;
            Neuron to;
            bool enabled;
            float weight;

            inline Gene(InnovationGenerator& g, Neuron from, Neuron to, float weight) {
                innovation = g.generate();
                this->from = from;
                this->to = to;
                this->weight = weight;
            }
        };
        std::vector<Gene> genes;
        std::vector<Neuron> inputs;
        std::vector<Neuron> outputs;
        std::set<Neuron> neurons;

        Gene& getRandomEnabledGene();
        Neuron getRandomNeuron();
    public:
        Genome(InnovationGenerator& g, int inputsCount, int outputsCout);
        Genome(const Genome& a, const Genome& b);
        Genome(Genome&& other);

        void addConnection(InnovationGenerator& g, Neuron from, Neuron to, float weight);
        void insertRandomConnection(InnovationGenerator& g);
        void insertRandomNode(InnovationGenerator& g);
        void mutateRandomWeight();
        void mutate(InnovationGenerator& g);
    };

}