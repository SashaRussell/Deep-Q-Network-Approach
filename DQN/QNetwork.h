#pragma once
#include "NeuralNetwork.h"
class QNetwork
{
private:

	NeuralNetwork* myNeuralNetwork = nullptr;

	int inputLayerSize = 0;
	int hiddenLayerNumber = 0;
	int hiddenLayerSize = 0;
	int outputLayerSize = 0;

	float learningRate = 0.5f;

	float MSELoss(Layer* currValue, Layer* targValue);
	float Adam(float learningRate = 0.5f);

public:
	QNetwork(int inputLayerSize, int hiddenLayerNumber, int hiddenLayerSize, int outputLayerSize, float learningRate = 0.001f);
	~QNetwork();

	void UpdateWeights(Layer* currValue, Layer* targValue); // need to give some value as input
};