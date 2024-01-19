#pragma once
#include "NeuralNetwork.h"
//#include "Optimizer.h"
#include "Adam.h"
class QNetwork
{
private:

	NeuralNetwork* myNeuralNetwork = nullptr;

	Optimizer*** weightOptimizer;
	Optimizer* biasOptimizer;


	float*** weightGradient;
	float* biasGradient;

	float* localErrors;

	int inputLayerSize = 0;
	int hiddenLayerNumber = 0;
	int hiddenLayerSize = 0;
	int outputLayerSize = 0;

	float lossTotal = 0.0f;

	float learningRate = 0.001f;

	float MSELossForBackPropogation(Layer* currValue, Layer* targValue);
	void EvaluateGradient();

public:
	QNetwork(int inputLayerSize, int hiddenLayerNumber, int hiddenLayerSize, int outputLayerSize, float learningRate = 0.001f);
	~QNetwork();



	void Update(Layer* inputValue, Layer* targOutValue); // need to give some value as input
};