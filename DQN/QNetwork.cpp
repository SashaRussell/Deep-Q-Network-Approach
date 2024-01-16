#include "QNetwork.h"
#include <iostream>

float QNetwork::MSELossForBackPropogation(Layer* currValue, Layer* targValue)
{
	float errorValue = 0.0f;

	for (int i = 0; i < currValue->getNodesNumber(); i++)
	{
		float temp = (float)currValue->getNodeAt(i)->getNodeValue() - targValue->getNodeAt(i)->getNodeValue();
		localErrors[i] = (float)temp / currValue->getNodesNumber();
		errorValue = (float)temp + errorValue;
	}
	errorValue = (float)errorValue / currValue->getNodesNumber();
	return errorValue;
}

void QNetwork::EvaluateGradient()
{
	// Weights Gradient Evaluation

	for (int i = 0; i < myNeuralNetwork->getLayerAt(hiddenLayerNumber + 1)->getNodesNumber(); i++) //  for last weights its different story - they have to be diveded for E_i, not Etotal.
	{
		for (int j = 0; j < myNeuralNetwork->getLayerAt(hiddenLayerNumber + 1)->getNodeAt(i)->getTotalWeightNumber(); j++)
		{
			weightGradient[hiddenLayerNumber][i][j] = (float)localErrors[i] * myNeuralNetwork->getLayerAt(hiddenLayerNumber)->getNodeAt(j)->getNodeValue();
		}
	}

	for (int i = hiddenLayerNumber; i > 0; i--) // we start at layer i and go by declining   
	{
		for (int j = 0; j < myNeuralNetwork->getLayerAt(i)->getNodesNumber(); j++) // we go through nodes of layer i
		{
			//int k = myNeuralNetwork->getLayerAt(i)->getNodesNumber(); //
			for (int m = 0; m < myNeuralNetwork->getLayerAt(i)->getNodeAt(j)->getTotalWeightNumber(); m++) // in nodes we ho through weights of layer i to calculate the gradient
			{
				float temp1 = (float)myNeuralNetwork->getLayerAt(i - 1)->getNodeAt(m)->getNodeValue() * myNeuralNetwork->getLayerAt(i)->getNodeAt(j)->getNodeValue() * lossTotal; // gradient value
				bool flagIsPrevLayerReLU = false; // for NULL-ing the negative values as the NN has ReLU connections // 

				if ((*myNeuralNetwork->getLayerAt(i - 1)->getLayerType() == 'R') and temp1 < 0)
				{
					temp1 = 0.0f;
				}
				if (i != hiddenLayerNumber) // we dont take into account the last row of hidden layer as there is nothing to summ up //
				{

					for (int n = i; n <= hiddenLayerNumber; n++) // adds all the other layers infront
					{
						float temp2 = 0.0f;
						if (*myNeuralNetwork->getLayerAt(n - 1)->getLayerType() == 'R')
						{
							// char* Mychar = myNeuralNetwork->getLayerAt(n - 1)->getLayerType(); //
							flagIsPrevLayerReLU = true;
						}
						else
						{
							// char* Mychar = myNeuralNetwork->getLayerAt(n - 1)->getLayerType(); //
							flagIsPrevLayerReLU = false;
						}
						for (int k = 0; k < myNeuralNetwork->getLayerAt(n)->getNodesNumber(); k++)
						{
							if (((flagIsPrevLayerReLU) and (myNeuralNetwork->getLayerAt(n)->getNodeAt(k)->getNodeValue() > 0)) or (!flagIsPrevLayerReLU))
							{
								temp2 = (float)temp2 + myNeuralNetwork->getLayerAt(n)->getNodeAt(k)->getNodeValue();
							}
						}
						temp1 = (float)temp1 * temp2;
					}
				}

				weightGradient[i - 1][j][m] = temp1;
			}
		}
	}

	//for (int i = 0; i < hiddenLayerSize; i++) // to display the gradients from from Layer (2) till the end [values intputted manually]
	//{
	//	for (int j = 0; j < hiddenLayerSize; j++)
	//	{
	//		for (int k = 1; k < hiddenLayerNumber; k++)
	//		{
	//			std::cout << weightGradient[k][i][j] << " ";
	//		}
	//		std::cout << "\n";
	//	}
	//	std::cout << "\n";
	//}



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

		biasGradient = new float[hiddenLayerNumber + 1]; // bias

		weightGradient = new float** [hiddenLayerNumber + 1];

		for (int i = 0; i < hiddenLayerNumber + 1; i++)
		{
			int temp1 = myNeuralNetwork->getLayerAt(i + 1)->getNodesNumber();
			weightGradient[i] = new float* [temp1];
			for (int j = 0; j < temp1; j++)
			{
				int temp2 = myNeuralNetwork->getLayerAt(i + 1)->getNodeAt(j)->getTotalWeightNumber();
				weightGradient[i][j] = new float[temp2];
			}
		}

		//weightGradient[0] = new float[inputLayerSize * hiddenLayerSize];
		//for (int i = 1; i < hiddenLayerNumber; i++)
		//{
		//	weightGradient[i] = new float[hiddenLayerSize * hiddenLayerSize]; // [(hiddenLayerSize+1)] respresents the previous layer size and the bias AND [hiddenLayerSize] represents the current layer size MAKING the summ of CONNECTIONS (weights and bias) needed for optimizing
		//}
		//weightGradient[hiddenLayerNumber] = new float[hiddenLayerSize * outputLayerSize];




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
