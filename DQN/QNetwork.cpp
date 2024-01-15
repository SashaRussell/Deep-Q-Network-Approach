#include "QNetwork.h"

float QNetwork::MSELossForBackPropogation(Layer* currValue, Layer* targValue)
{
	float errorValue = 0.0f;

	for (int i = 0; i < currValue->getNodesNumber(); i++)
	{
		float temp = (float)currValue->getNodeAt(i)->getNodeValue() - targValue->getNodeAt(i)->getNodeValue();
		localErrors[i] = temp;
		errorValue = (float)temp + errorValue;
	}
	errorValue = (float)errorValue / currValue->getNodesNumber();
	return errorValue;
}

void QNetwork::EvaluateGradient()
{
	// Weights Gradient Evaluation

	for (int i = 0; i < hiddenLayerSize * outputLayerSize; i++) //  for last weights its different story - they have to be diveded by E_i
	{

	}

	for (int i = hiddenLayerNumber + 2; i > 1; i--)
	{
		
	}

	// Bias Gradient Evaluation



}

QNetwork::QNetwork(int inputLayerSize, int hiddenLayerNumber, int hiddenLayerSize, int outputLayerSize, float learningRate)
{
	if ((inputLayerSize > 0) and (hiddenLayerNumber > 0) and (hiddenLayerSize > 0) and (outputLayerSize > 0) and (learningRate >= 0 and learningRate <= 1))
	{
		// save values
		this->inputLayerSize = inputLayerSize;
		this->hiddenLayerNumber = hiddenLayerNumber;
		this->hiddenLayerSize = hiddenLayerSize;
		this->outputLayerSize = outputLayerSize;
		this->learningRate = learningRate;

		// init my Neural Network
		myNeuralNetwork = new NeuralNetwork();

		myNeuralNetwork->AddLinearLayer(0, inputLayerSize);
		myNeuralNetwork->AddReLULayer(inputLayerSize, hiddenLayerSize);

		for (int i = 0; i < hiddenLayerNumber - 2; i++)
		{
			if (i % 2 == 0)
			{
				myNeuralNetwork->AddLinearLayer(hiddenLayerSize, hiddenLayerSize);
			}
			else
			{
				myNeuralNetwork->AddReLULayer(hiddenLayerSize, hiddenLayerSize);
			}
		}

		myNeuralNetwork->AddLinearLayer(hiddenLayerSize, hiddenLayerSize);
		myNeuralNetwork->AddLinearLayer(hiddenLayerSize, outputLayerSize);

		// For storing Error list

		localErrors = new float[outputLayerSize];

		// Make a list for storing evaluated gradient values  //  P.S. LATER Why not combinde two below if they are connected? I mean in a vector<vector<float>, vecotor<Optimizer>>???
		// this only applies to ReLU connections

		biasGradient = new float[hiddenLayerNumber + 1];

		weightGradient = new float* [hiddenLayerNumber + 1];

		weightGradient[0] = new float[inputLayerSize * hiddenLayerSize];
		for (int i = 1; i < hiddenLayerNumber; i++)
		{
			weightGradient[i] = new float[hiddenLayerSize * hiddenLayerSize]; // [(hiddenLayerSize+1)] respresents the previous layer size and the bias AND [hiddenLayerSize] represents the current layer size MAKING the summ of CONNECTIONS (weights and bias) needed for optimizing
		}
		weightGradient[hiddenLayerNumber] = new float[hiddenLayerSize * outputLayerSize];


		// For bias



		// Make a list of Optimizers (Currently its just ADAM)

		OptimizerList = new Optimizer * [hiddenLayerNumber + 1];

		OptimizerList[0] = new Adam[(inputLayerSize + 1) * hiddenLayerSize];
		for (int i = 1; i < hiddenLayerNumber; i++)
		{
			OptimizerList[i] = new Adam[(hiddenLayerSize + 1) * hiddenLayerSize]; // [(hiddenLayerSize+1)] respresents the previous layer size and the bias AND [hiddenLayerSize] represents the current layer size MAKING the summ of CONNECTIONS (weights and bias) needed for optimizing
		}
		OptimizerList[hiddenLayerNumber] = new Adam[(hiddenLayerSize + 1) * outputLayerSize];
	}
}

QNetwork::~QNetwork()
{
	delete myNeuralNetwork;
}


void QNetwork::Update(Layer* inputValue, Layer* targOutValue)
{

	myNeuralNetwork->setInputLayer(inputValue);
	myNeuralNetwork->TransactionFF();
	lossTotal = MSELossForBackPropogation(myNeuralNetwork->getLayerAt(hiddenLayerNumber + 1), targOutValue);
	// Weight back propogation evaluation (find VALUE and DVALUE through MSELoss for each weight and bias) OR we are finding the gradient value for the weight and biases
	//
	EvaluateGradient();
	//
	// Weight Adjustment based on Adam Alg. optimization with input data of VALUE and DVALUE
}
