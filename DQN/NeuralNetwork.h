#pragma once
#include "Linear.h"
#include "ReLU.h"
#include "LeakyReLU.h"

#include <random>
#include <vector>
class NeuralNetwork
{
private:
	int nnSize = 0;
	int inputLayerSize;
	int hiddenLayerNumber;
	int hiddenLayerSize;
	int outputLayerSize;
	float learningRate = 0.01;
	

	//std::vector <Layer*> layers;
	float** myNeuralNetworkNodes = nullptr;
	float** myNeuralNetworkWeights = nullptr;
	float* myNeuralNetworkBias = nullptr;

	char* myLayerType = nullptr; // "L" - Linear, "R" - ReLU

	std::random_device rd;

	float* localError = nullptr;

	float* HeNormal_Init(int prevNodeNumber, int currNodesNumber, std::mt19937& generator);


public:

	void NullNodesAt();


	NeuralNetwork(int inputLayerSize, int hiddenLayerNumber, int hiddenLayerSize, int outputLayerSize, float learningRate = 0.01);
	void print();
	~NeuralNetwork();

	void SetInputLayer(float* InputLayer);


	float* LocalErrorMSE(float* targetOutput = nullptr); // need to be private

	
	bool AddLinearLayer(int prevLayerSize, int currLayerSize, char* weightInitType = new char[9] {'H', 'e', 'N', 'o', 'r', 'm', 'a', 'l', '\0'}); // returns 1 on success, 0 - fail, He Normal Weight Init by default
	bool AddLeakyReLULayer(int prevLayerSize, int currLayerSize, char* weightInitType = new char[9] {'H', 'e', 'N', 'o', 'r', 'm', 'a', 'l', '\0'}, float koef = 0.01); // same as above
	bool AddReLULayer(int prevLayerSize, int currLayerSize, char* weightInitType = new char[9] {'H', 'e', 'N', 'o', 'r', 'm', 'a', 'l', '\0'}); // same as above

	bool TransactionFF(); // Feed Forward 

	bool TransactionBP(float* targetOutput);

	float evaluateWeightSum();


	void setInputLayer(Layer* initLayer);
	Layer* getLayerAt(int index);


	//bool AddSigmoidLayer(); // Not implimented yet
};

