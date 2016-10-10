#include <qaib/nn/JITNeuralNetwork.hpp>
#include <qaib/util/JIT.hpp>
#include <unordered_map>

namespace qaib {

    JITNeuralNetwork::JITNeuralNetwork(const Ref<PlainNeuralNetwork>& plainNetwork) {
        using namespace asmjit;
        using x86::ptr;

        std::unordered_map<Neuron, int> neuronsMapping;
        int ctr = 0;

        for (auto& input : plainNetwork->inputs) {
            inputs.push_back(ctr);
            neuronsMapping[input] = ctr;
            ctr += 1;
        }

        for (auto& output : plainNetwork->outputs) {
            outputs.push_back(ctr);
            neuronsMapping[output] = ctr;
            ctr += 1;
        }

        CodeHolder codeHolder;

        codeHolder.init(jitRuntime.getCodeInfo());

        X86Compiler c(&codeHolder);

        auto func = c.addFunc(FuncSignature1<void, float*>(CallConv::kIdHost));

        auto aField = c.newGpz("field");
        auto aCurrentPower = c.newXmmSs();
        auto aTmpFloat1 = c.newXmmSs();
        auto aTmpFloat2 = c.newXmmSs();
        auto aTmpGP = c.newGpq();
        c.setArg(0, aField);

        for (auto& rule : plainNetwork->executionRules) {
            if (neuronsMapping.find(rule.neuron) == neuronsMapping.end()) {
                neuronsMapping[rule.neuron] = ctr++;
            }

            int outputNeuron = neuronsMapping[rule.neuron];

            c.subss(aCurrentPower, aCurrentPower); // currentPower = 0

            for (auto& input : rule.inputs) {
                if (neuronsMapping.find(input.from) == neuronsMapping.end()) {
                    neuronsMapping[input.from] = ctr++;
                }

                int inputNeuron = neuronsMapping[input.from];

                c.movss(aTmpFloat1, ptr(aField, sizeof(float) * inputNeuron, sizeof(float)));

                uint64_t weight;
                *(float*)(&weight) = input.weight;

                c.mov(aTmpGP, Imm(weight));
                c.movq(aTmpFloat2, aTmpGP);

                c.mulss(aTmpFloat1, aTmpFloat2);

                c.addss(aCurrentPower, aTmpFloat1);

            }
            {
                auto call = c.call(imm_ptr(activationFunc), FuncSignature1<float, float>(CallConv::kIdHost));
                call->setArg(0, aCurrentPower);
                call->setRet(0, aCurrentPower);
            }

            c.movss(ptr(aField, sizeof(float) * outputNeuron, sizeof(float)), aCurrentPower);

        }

        c.ret();

        c.endFunc();

        c.finalize();

        jitRuntime.add(&executeFunc, &codeHolder);

        neuronsCount = ctr;
    }

    float JITNeuralNetwork::activationFunc(float power) {
        return 1.0f / (1.0f +  expf(-power)) * 2.0f - 1.0f;
    }

    std::vector<float> JITNeuralNetwork::execute(std::vector<float> inputs) {
        float* field = new float[neuronsCount];
        return std::move(execute(inputs, field));
        delete[] field;
    }

    std::vector<float> JITNeuralNetwork::execute(const std::vector<float>& inputs, float* field) {
        for (int i = 0; i < neuronsCount; ++i) {
            field[i] = 0;
        }
        for (int i = 0, iend = inputs.size(); i < iend; ++i) {
            field[this->inputs[i]] = inputs[i];
        }
        executeFunc(field);
        std::vector<float> results;
        for (auto output : outputs) {
            results.push_back(field[output]);
        }
        return std::move(results);
    }

    JITNeuralNetwork::~JITNeuralNetwork() {
        jitRuntime.release(executeFunc);
    }

    JITNeuralNetworkWithField::JITNeuralNetworkWithField(const Ref<JITNeuralNetwork>& origin) {
        this->origin = origin;
        field = new float[origin->getNeuronsCount()];
    }

    JITNeuralNetworkWithField::~JITNeuralNetworkWithField() {
        delete field;
    }

    std::vector<float> JITNeuralNetworkWithField::execute(std::vector<float> inputs) {
        return std::move(origin->execute(inputs, field));
    }

}
