#pragma once
#include "NeuralNetwork.h"
//#include "Optimizer.h"
#include "Adam.h"
class QNetwork
{
private:

	

	Optimizer**** weightOptimizer;
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
	void EvaluateGradientCopy();
	float BackPropogationRecursionMethod(int layerCounter);
	void AdamPass();

public:
	NeuralNetwork* myNeuralNetwork = nullptr;

	QNetwork(int inputLayerSize, int hiddenLayerNumber, int hiddenLayerSize, int outputLayerSize, float learningRate = 0.1f);
	~QNetwork();

	float CheckError(Layer* targValue);

	void Update(Layer* inputValue, Layer* targOutValue); // need to give some value as input
	void UpdateBeta(Layer* inputValue, Layer* targOutValue);
};