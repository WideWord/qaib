#include <qaib/nn/Genome.hpp>
#include <qaib/util/Random.hpp>
#include <qaib/nn/NeuralNetwork.hpp>
#include <queue>

namespace qaib {



    Genome::Genome(Genome&& other) {
        genes = std::move(other.genes);
    }

    Genome::Genome(const Genome& a, const Genome& b) {
        auto it1 = a.genes.begin();
        auto it2 = b.genes.begin();

        while (it1 != a.genes.end() && it2 != b.genes.end()) {
            if (it1->innovation == it2->innovation) {
                Gene gene = *it1;
                gene.enabled = it1->enabled && it2->enabled;
                gene.weight = Random::getBool() ? it1->weight : it2->weight;
                genes.push_back(gene);
                ++it1;
                ++it2;
            } else if (it1->innovation < it2->innovation) {
                genes.push_back(*it1);
                ++it1;
            } else {
                genes.push_back(*it2);
                ++it2;
            }
        }

        while (it1 != a.genes.end()) {
            genes.push_back(*it1++);
        }

        while (it2 != b.genes.end()) {
            genes.push_back(*it2++);
        }
    }

    Genome::Gene& Genome::getRandomEnabledGene() {
        while (true) {
            int geneId = Random::getInt(0, (int)(genes.size() - 1));
            Gene& gene = genes[geneId];
            if (gene.enabled) {
                return gene;
            }
        }
    }

    Neuron Genome::getRandomNeuron() {
        Gene& gene = getRandomEnabledGene();
        return Random::getBool() ? gene.from : gene.to;
    }

    void Genome::addConnection(InnovationGenerator& g, Neuron from, Neuron to, float weight) {
        genes.push_back(Gene(g, from, to, weight));
    }

    void Genome::insertRandomConnection(InnovationGenerator& g) {
        Neuron n1 = getRandomNeuron();
        Neuron n2;
        do {
            n2 = getRandomNeuron();
        } while (n1 == n2);
        addConnection(g, n1, n2, Random::getFloat(-2, 2));
    }

    void Genome::insertRandomNode(InnovationGenerator& g) {
        Gene& gene = getRandomEnabledGene();
        gene.enabled = false;

        float newWeight = sqrtf(fabsf(gene.weight));

        Neuron newNeuron = g.generate();
        genes.push_back(Gene(g, gene.from, newNeuron, newWeight));
        genes.push_back(Gene(g, newNeuron, gene.to, (gene.weight < 0) ? -newWeight : newWeight));
    }

    Genome::Genome(InnovationGenerator& g, int inputsCount, int outputsCount) {
        for (int i = 0; i < inputsCount; ++i) {
            Neuron n = g.generate();
            inputs.push_back(n);
            neurons.insert(n);
        }

        for (int i = 0; i < outputsCount; ++i) {
            Neuron n = g.generate();
            outputs.push_back(n);
            neurons.insert(n);

            for (int j = 0; j < inputsCount; ++j) {
                addConnection(g, inputs[j], outputs[i], Random::getFloat(-2, 2));
            }
        }


    }

    void Genome::mutateRandomWeight() {
        Gene& gene = getRandomEnabledGene();
        gene.weight = gene.weight + Random::getFloat(-0.2, 0.2);
        if (gene.weight < -2) {
            gene.weight = -2;
        } else if (gene.weight > 2) {
            gene.weight = 2;
        }
    }

    void Genome::mutate(InnovationGenerator& g) {
        int r = Random::getInt(0, 100);
        if (r < 5) {
            insertRandomNode(g);
        } else if (r < 15) {
            insertRandomConnection(g);
        } else {
            mutateRandomWeight();
        }
    }

    Ref<NeuralNetwork> Genome::buildNeuralNetwork() {

        std::map<Neuron, NeuralNetwork::NeuronData> net;

        for (auto input : inputs) {
            NeuralNetwork::NeuronData data;
            data.neuron = input;
            data.flag = true;
            net[input] = data;
        }

        for (auto& gene : genes) {
            if (!gene.enabled) continue;

            if (net.find(gene.to) == net.end()) {
                NeuralNetwork::NeuronData data;
                data.neuron = gene.to;
                data.flag = false;
                net[gene.to] = data;
            }

            auto& toNeuronData = net[gene.to];

            NeuralNetwork::NeuronData::Link link;
            link.from = gene.from;
            link.weight = gene.weight;
            toNeuronData.inputs.push_back(link);
        }

        std::queue<Neuron> queue;
        for (auto output : outputs) {
            queue.push(output);
        }

        auto nn = Ref<NeuralNetwork>(new NeuralNetwork());

        std::vector<NeuralNetwork::NeuronData> exec;

        while (!queue.empty()) {
            auto neuron = queue.front();
            queue.pop();
            if (net[neuron].flag) {
                continue;
            }
            auto data = net[neuron];
            exec.push_back(data);
            net[neuron].flag = true;
            for (auto& link : net[neuron].inputs) {
                queue.push(link.from);
            }
        }

        nn->inputs = inputs;
        nn->outputs = outputs;

        nn->executionRules.reserve(exec.size());

        for (auto it = exec.rbegin(); it != exec.rend(); ++it) {
            nn->executionRules.push_back(*it);
        }

        return nn;
    }


}