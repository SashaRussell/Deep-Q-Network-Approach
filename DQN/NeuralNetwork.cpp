#include "NeuralNetwork.h"
#include "iostream"

NeuralNetwork::NeuralNetwork()
{

}

bool NeuralNetwork::AddLinearLayer(int prevLayerSize, int currLayerSize, char* weightInitType)
{
	if (nnSize == 0 and prevLayerSize > 0) // first layer can't have weights
	{
		return false;
	}
	nnSize++;
	layers.push_back(new Linear(prevLayerSize, currLayerSize, weightInitType));
	return true;
}

bool NeuralNetwork::AddLeakyReLULayer(int prevLayerSize, int currLayerSize, char* weightInitType, float koef)
{
	if (nnSize == 0 and prevLayerSize > 0) // first layer can't have weights
	{
		return false;
	}
	nnSize++;
	layers.push_back(new LeakyReLU(prevLayerSize, currLayerSize, weightInitType, koef));
	return true;
}

bool NeuralNetwork::AddReLULayer(int prevLayerSize, int currLayerSize, char* weightInitType)
{
	if (nnSize == 0 and prevLayerSize > 0) // first layer can't have weights
	{
		return false;
	}
	nnSize++;
	layers.push_back(new ReLU(prevLayerSize, currLayerSize, weightInitType));
	return false;
}

Layer* NeuralNetwork::getLayerAt(int index)
{
	if (index >= 0 and index < nnSize)
	{
		return layers[index];
	}
	return nullptr;
}

NeuralNetwork::~NeuralNetwork()
{

};