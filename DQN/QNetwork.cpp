#include "QNetwork.h"

QNetwork::QNetwork(int inputLayerSize, int hiddenLayerNumber, int hiddenLayerSize, int outputLayerSize, float learningRate)
{
	if ((inputLayerSize > 0) and (hiddenLayerNumber > 0) and (hiddenLayerSize > 0) and (outputLayerSize > 0) and (learningRate >= 0 and learningRate <= 1))
	{
		this->inputLayerSize = inputLayerSize;
		this->hiddenLayerNumber = hiddenLayerNumber;
		this->hiddenLayerSize = hiddenLayerSize;
		this->outputLayerSize = outputLayerSize;
		this->learningRate = learningRate;

		myNeuralNetwork = new NeuralNetwork();

		myNeuralNetwork->AddLinearLayer(0, inputLayerSize);
		myNeuralNetwork->AddReLULayer(inputLayerSize, hiddenLayerSize);

		for (int i = 0; i < hiddenLayerNumber - 1; i++)
		{
			myNeuralNetwork->AddLinearLayer(hiddenLayerSize, hiddenLayerSize);
			myNeuralNetwork->AddReLULayer(hiddenLayerSize, hiddenLayerSize);
		}

		myNeuralNetwork->AddLinearLayer(hiddenLayerSize, outputLayerSize);

	}
}

QNetwork::~QNetwork()
{
	delete myNeuralNetwork;
}

void QNetwork::Update()
{

}
