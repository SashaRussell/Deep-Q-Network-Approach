#include "NeuralNetwork.h"
#include "iostream"

NeuralNetwork::NeuralNetwork()
{
	numLayers = 0;
}

void NeuralNetwork::AddLinearLayer(int size)
{

	// Implimentation Required (FOR WEIGHTS)
}

void NeuralNetwork::AddLeakyReLULayer()
{
	// Implimentation Required
}

void NeuralNetwork::AddReLULayer()
{
	// Implimentation Required
}

void NeuralNetwork::AddSigmoidLayer()
{
	// Implimentation Required
}



NeuralNetwork::~NeuralNetwork()
{
	numLayers = 0; // Number of Hiiden Layers
	delete layers;// = nullptr; // State batch
	delete weights;// = nullptr; // Hidden Layer Values
	delete bias;// = nullptr; // Bias Values
};