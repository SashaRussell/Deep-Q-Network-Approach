#pragma once
class AgentDQN
{
private:
public:
	AgentDQN( /*environment, */int inputLayerSize, int hiddenLayerNumber, int hiddenLayerSize = 64, int outputLayerSize = 64, float gamma = 0.99f , float learningRate = 0.001, float epsilon = 0.01, int replaySize = 1000000, int minibatchSize = 32, int targetUpdateThreshold = 20);
};

