#include "NeuralNetwork.h"
#include "iostream"

NeuralNetwork::NeuralNetwork(int inputLayerSize, int hiddenLayerNumber, int hiddenLayerSize, int outputLayerSize, float learningRate)
{
	nnSize = hiddenLayerNumber + 2;
	{ /// Node Init
		myNeuralNetworkNodes = new float* [nnSize];
		// Input Layer
		myNeuralNetworkNodes[0] = new float[inputLayerSize];
		for (int j = 0; j < inputLayerSize; j++)
		{
			myNeuralNetworkNodes[0][j] = 0.0f;
		}
		// Inner Layers
		for (int i = 1; i < nnSize - 1; i++)
		{
			myNeuralNetworkNodes[i] = new float[hiddenLayerSize];
			for (int j = 0; j < hiddenLayerSize; j++)
			{
				myNeuralNetworkNodes[i][j] = 0.0f;
			}
		}
		// Output Layer
		myNeuralNetworkNodes[nnSize - 1] = new float[outputLayerSize];
		for (int j = 0; j < outputLayerSize; j++)
		{
			myNeuralNetworkNodes[nnSize - 1][j] = 0.0f;
		}
	}
	{ /// Weight Init
		std::random_device rd; // for Init-ing random HeNormal Weights
		std::mt19937 gen(rd());

		myNeuralNetworkWeights = new float* [nnSize - 1];
		myNeuralNetworkWeights[0] = HeNormal_Init(inputLayerSize, hiddenLayerSize, gen);
		for (int i = 1; i < nnSize - 2; i++)
		{
			myNeuralNetworkWeights[i] = HeNormal_Init(hiddenLayerSize, hiddenLayerSize, gen);
		}
		myNeuralNetworkWeights[nnSize - 2] = HeNormal_Init(hiddenLayerSize, outputLayerSize, gen);
	}
	{ /// Layer Type Init (Concept is -> Input, Layer=Input+1 , Output and Layer=Output-1 are always Linear, Inner layers - if their order %2==0 then they are ReLU, otherwise Linear)
		myLayerType = new char[nnSize];
		for (int i = 0; i < nnSize; i++)
		{
			if ((i < 2) or (i >= nnSize - 2))
			{
				myLayerType[i] = 'L';
			}
			else
			{
				if (i % 2 == 0)
				{
					myLayerType[i] = 'R';
				}
				else
				{
					myLayerType[i] = 'L';
				}
			}
		}
	}
	{ /// Bias Init
		myNeuralNetworkBias = new float[nnSize];
		for (int i = 0; i < nnSize; i++)
		{
			myNeuralNetworkBias[i] = 0.0f;
		}
	}
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
					value = value + ((float)layers[i - 1]->getNodeAt(m)->getNodeValue() * layers[i]->getNodeAt(j)->getWeightValueAt(m)); // multiply prev layer node with weights and summ them up
				}

				value = value + layers[i]->getBiasValue(); // add the bias
				layers[i]->getNodeAt(j)->setNodeValue(value); // input the new value into the node
			}
		}
		return true;
	}
	return false;
}

void NeuralNetwork::setInputLayer(Layer* initLayer)
{
	//layers[0] = initLayer;
}

Layer* NeuralNetwork::getLayerAt(int index)
{
	if (index >= 0 and index < nnSize)
	{
		return 0;//layers[index];
	}
	return nullptr;
}

float* HeNormal_Init(int prevNodeNumber, int currNodesNumber, std::mt19937& generator)
{
	int WeightNumber = prevNodeNumber * currNodesNumber;
	float* array = new float[WeightNumber];
	for (int i = 0; i < WeightNumber; i++)
	{
		std::uniform_real_distribution<float> distribution(0.0, 1.0);
		array[i] = static_cast<float>(distribution(generator) * sqrt(2.0 / prevNodeNumber));
	}
	return array;
}



NeuralNetwork::~NeuralNetwork()
{

};