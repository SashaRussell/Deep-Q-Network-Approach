#pragma once

#include "NeuralNetwork.h"
#include "Adam.h"

class QNetwork
{
private:
	NeuralNetwork* myNeuralNetwork = nullptr;

	Optimizer**** weightOptimizer;
	Optimizer** biasOptimizer;

	float*** weightGradient;
	float* biasGradient;

	int inputLayerSize = 0;
	int hiddenLayerNumber = 0;
	int hiddenLayerSize = 0;
	int outputLayerSize = 0;
	int nnLayerSize = 0;

	float lossTotal = 0.0f;
	float difLossTotal = 0.0f;
	float* localDifErrors = nullptr;

	float learningRate = 0.001f;

	float MSELoss(Layer* targValue);
	float MSEDifLoss(Layer* targValue);

	void EvaluateWeightGradient();
	void EvaluateBiasGradient();


public:

	float GradientRecursionMethod(int layer, int node);
	void DisplayNeuralNetwork();

	void Update(Layer* inputValue, Layer* targOutValue);
	float GetLossTotal();

	QNetwork(int inputLayerSize, int hiddenLayerNumber, int hiddenLayerSize, int outputLayerSize, float learningRate = 0.001f);
	~QNetwork();

	

	/*float CheckError(Layer* targValue);*/

	//void Update(Layer* inputValue, Layer* targOutValue); // need to give some value as input
	/*void UpdateBeta(Layer* inputValue, Layer* targOutValue);*/
};