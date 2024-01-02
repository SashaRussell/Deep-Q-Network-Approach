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
	return true;
}

bool NeuralNetwork::TransactionFF()
{
	if (nnSize > 1)
	{
		for (int i = 1; i < nnSize; i++) // goes through layers
		{
			for (int j = 0; j < layers[i]->getNodesNumber(); j++) // goes through nodes of layers
			{
				float value = layers[i]->getNodeAt(j)->getNodeValue(); // getting value from node j

				for (int m = 0; m < layers[i]->getNodeAt(j)->getTotalWeightNumber(); m++) // goes through weights of nodes
				{
					value = value + ((float)layers[i-1]->getNodeAt(m)->getNodeValue() * layers[i]->getNodeAt(j)->getWeightValueAt(m)); // multiply prev layer node with weights and summ them up
				}

				value = value + layers[i]->getBiasValue(); // add the bias
				layers[i]->getNodeAt(j)->setNodeValue(value); // input the new value into the node
			}
		}
		return true;
	}
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