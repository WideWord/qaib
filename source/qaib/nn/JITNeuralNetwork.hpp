#pragma once

#include <qaib/nn/NeuralNetwork.hpp>
#include <qaib/util/Typedef.hpp>
#include <qaib/util/JIT.hpp>

namespace qaib {

    class PlainNeuralNetwork;

    class JITNeuralNetwork : public NeuralNetwork {
    private:
        std::vector<int> inputs;
        std::vector<int> outputs;


        typedef void (*executeFuncPtr)(float*);
        executeFuncPtr executeFunc;

        asmjit::JitRuntime jitRuntime;

        static float activationFunc(float);
        size_t neuronsCount;

    public:
        JITNeuralNetwork(const Ref<PlainNeuralNetwork>& plainNetwork);
        virtual ~JITNeuralNetwork();
        virtual std::vector<float> execute(std::vector<float> inputs) override;
        std::vector<float> execute(const std::vector<float>& inputs, float* field);

        inline size_t getNeuronsCount() {
            return neuronsCount;
        }
    };

    class JITNeuralNetworkWithField : public NeuralNetwork {
    private:
        Ref<JITNeuralNetwork> origin;
        float* field;
    public:
        JITNeuralNetworkWithField(const Ref<JITNeuralNetwork>& origin);
        virtual ~JITNeuralNetworkWithField();
        virtual std::vector<float> execute(std::vector<float> inputs) override;
    };

}