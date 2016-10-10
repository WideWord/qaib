#include <qaib/nn/Genome.hpp>
#include <qaib/util/Random.hpp>
#include <qaib/nn/NeuralNetwork.hpp>
#include <deque>
#include <sstream>

namespace qaib {


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

        inputs = a.inputs;
        outputs = a.outputs;

        recollectNeurons();
    }

    Genome::Gene* Genome::getRandomEnabledGene() {
        if (genes.empty()) return nullptr;
        int maxQueries = 10;
        for (int i = 0; i < maxQueries; ++i) {
            int geneId = Random::getInt(0, (int)(genes.size() - 1));
            Gene& gene = genes[geneId];
            if (gene.enabled) {
                return &gene;
            }
        }
        return nullptr;
    }

    Neuron Genome::getRandomNeuron() {
        int id = Random::getInt(0, (int)neurons.size() - 1);
        auto it = neurons.begin();
        std::advance(it, id);
        return *it;
    }

    void Genome::addConnection(InnovationGenerator& g, Neuron from, Neuron to, float weight) {
        genes.push_back(Gene(g, from, to, weight));
    }

    void Genome::insertRandomConnection(InnovationGenerator& g) {
        Neuron n1;
        while (true) {
            n1 = getRandomNeuron();
            bool isOutput = false;
            for (auto output: outputs) {
                if (output == n1) {
                    isOutput = true;
                }
            }
            if (!isOutput) {
                break;
            }
        }
        Neuron n2;
        while (true) {
            n2 = getRandomNeuron();
            bool isInput = false;
            for (auto input: inputs) {
                if (input == n2) {
                    isInput = true;
                }
            }
            bool connectionExists = false;
            for (auto& gene : genes) {
                if (!gene.enabled) continue;
                if ((gene.from == n1 && gene.to == n2) || (gene.from == n2 && gene.to == n1)) {
                    connectionExists = true;
                    break;
                }
            }
            if (n1 != n2 && !connectionExists && !isInput) break;
        }
        addConnection(g, n1, n2, Random::getFloat(-2, 2));
    }

    void Genome::insertRandomNode(InnovationGenerator& g) {
        Gene* maybeGene = getRandomEnabledGene();
        if (!maybeGene) return;
        Gene& gene = *maybeGene;
        gene.enabled = false;

        float newWeight = sqrtf(fabsf(gene.weight));

        Neuron newNeuron = g.generate();
        genes.push_back(Gene(g, gene.from, newNeuron, newWeight));
        genes.push_back(Gene(g, newNeuron, gene.to, (gene.weight < 0) ? -newWeight : newWeight));
        neurons.insert(newNeuron);
    }

    void Genome::removeRandomConnection() {
        Gene* gene = getRandomEnabledGene();
        if (!gene) return;
        gene->enabled = false;
        recollectNeurons();
    }

    Genome::Genome(InnovationGenerator& g, int inputsCount, int outputsCount) {
        for (int i = 0; i < inputsCount; ++i) {
            Neuron n = g.generate();
            inputs.push_back(n);
        }

        for (int i = 0; i < outputsCount; ++i) {
            Neuron n = g.generate();
            outputs.push_back(n);
        }

        recollectNeurons();
    }

    void Genome::mutateRandomWeight() {
        Gene* maybeGene = getRandomEnabledGene();
        if (!maybeGene) return;
        Gene& gene = *maybeGene;
        gene.weight = gene.weight + Random::getFloat(-0.2, 0.2);
        if (gene.weight < -2) {
            gene.weight = -2;
        } else if (gene.weight > 2) {
            gene.weight = 2;
        }
    }

    void Genome::mutate(InnovationGenerator& g) {
        int r = Random::getInt(0, 100);
        if (r < 15) {
            insertRandomNode(g);
        } else if (r < 30) {
            insertRandomConnection(g);
        } else if (r < 35) {
            removeRandomConnection();
        } else {
            mutateRandomWeight();
        }
    }

    Ref<NeuralNetwork> Genome::buildNeuralNetwork() const {

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

        std::deque<Neuron> queue;
        for (auto output : outputs) {
            queue.push_back(output);
        }

        auto nn = Ref<NeuralNetwork>(new NeuralNetwork());

        std::vector<NeuralNetwork::NeuronData> exec;

        while (!queue.empty()) {
            auto neuron = queue.front();
            queue.pop_front();
            if (net[neuron].flag) {
                continue;
            }
            auto data = net[neuron];
            exec.push_back(data);
            net[neuron].flag = true;
            for (auto& link : net[neuron].inputs) {
                queue.push_back(link.from);
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

    Genome::Genome(sf::Packet& packet) {
        uint64_t size;
        packet >> (sf::Uint64&)size;
        for (uint64_t i = 0; i < size; ++i) {
            genes.push_back(Gene(packet));
        }

        uint64_t inputsCount;
        uint64_t outputsCount;

        packet >> (sf::Uint64&)inputsCount;
        for (uint64_t i = 0; i < inputsCount; ++i) {
            Neuron input;
            packet >> (sf::Uint64&)input;
            inputs.push_back(input);
        }

        packet >> (sf::Uint64&)outputsCount;
        for (uint64_t i = 0; i < outputsCount; ++i) {
            Neuron output;
            packet >> (sf::Uint64&)output;
            outputs.push_back(output);
        }
    }

    void Genome::writeTo(sf::Packet& packet) const {
        uint64_t size = genes.size();
        packet << (sf::Uint64)size;

        for (auto& gene : genes) {
            gene.writeTo(packet);
        }

        packet << (sf::Uint64)inputs.size();

        for (auto i : inputs) {
            packet << (sf::Uint64)i;
        }

        packet << (sf::Uint64)outputs.size();

        for (auto i : outputs) {
            packet << (sf::Uint64)i;
        }
    }

    void Genome::recollectNeurons() {
        neurons.clear();
        for (auto& gene : genes) {
            if (!gene.enabled) continue;
            neurons.insert(gene.from);
            neurons.insert(gene.to);
        }
        for (auto& neuron : inputs) {
            neurons.insert(neuron);
        }
        for (auto& neuron : outputs) {
            neurons.insert(neuron);
        }
    }

    std::string Genome::renderGraph() const {
        std::stringstream ss;
        ss << "\ndigraph G {\nnode [shape=circle,color=green1];\n";

        ss << "subgraph inputs {\n node [style=solid,color=blue4, shape=circle];\n";
        for (auto& input : inputs) {
            ss << input << ";\n";
        }
        ss << "}\n";

        ss << "subgraph outputs {\n  node [style=solid,color=red2, shape=circle];\n";
        for (auto& output : outputs) {
            ss << output << ";\n";
        }
        ss << "}\n";


        for (auto& gene : genes) {
            if (!gene.enabled) continue;
            ss << gene.from << " -> " << gene.to << " [label=\"" << gene.weight << "\"];\n";
        }

        ss << "}\n";

        return ss.str();
    }

}
