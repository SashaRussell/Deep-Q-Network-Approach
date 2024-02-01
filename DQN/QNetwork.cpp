#include "QNetwork.h"
#include <iostream>

QNetwork::QNetwork(int inputLayerSize, int hiddenLayerNumber, int hiddenLayerSize, int outputLayerSize, float learningRate)
{

}

QNetwork::~QNetwork()
{

}




//
//float QNetwork::MSELossForBackPropogation(Layer* currValue, Layer* targValue)
//{
//	float errorValue = 0.0f;
//
//	for (int i = 0; i < currValue->getNodesNumber(); i++)
//	{
//		float temp = (float)currValue->getNodeAt(i)->getNodeValue() - targValue->getNodeAt(i)->getNodeValue();
//		localErrors[i] = (float)temp / currValue->getNodesNumber();
//		temp = (float)temp * temp;
//		errorValue = (float)temp + errorValue;
//	}
//	//errorValue = (float)errorValue / currValue->getNodesNumber();
//	return errorValue;
//}
//
//void QNetwork::EvaluateGradient()
//{
//	// Weights Gradient Evaluation
//
//	for (int i = 0; i < myNeuralNetwork->getLayerAt(hiddenLayerNumber + 1)->getNodesNumber(); i++) //  for last weights its different - they have to be diveded for E_i, not Etotal.
//	{
//		for (int j = 0; j < myNeuralNetwork->getLayerAt(hiddenLayerNumber + 1)->getNodeAt(i)->getTotalWeightNumber(); j++)
//		{
//			weightGradient[hiddenLayerNumber][i][j] = (float)localErrors[i] * myNeuralNetwork->getLayerAt(hiddenLayerNumber)->getNodeAt(j)->getNodeValue();
//		}
//	}
//
//	for (int i = hiddenLayerNumber; i > 0; i--) // we start at layer i (the last layer) and go by declining   
//	{
//		for (int j = 0; j < myNeuralNetwork->getLayerAt(i)->getNodesNumber(); j++) // we go through nodes of layer i
//		{
//			//int k = myNeuralNetwork->getLayerAt(i)->getNodesNumber(); //
//			for (int m = 0; m < myNeuralNetwork->getLayerAt(i)->getNodeAt(j)->getTotalWeightNumber(); m++) // in nodes we ho through weights of layer i to calculate the gradient
//			{
//				float temp1 = (float)myNeuralNetwork->getLayerAt(i - 1)->getNodeAt(m)->getNodeValue() * myNeuralNetwork->getLayerAt(i)->getNodeAt(j)->getNodeValue() * lossTotal; // gradient value
//				bool flagIsPrevLayerReLU = false; // for NULL-ing the negative values as the NN has ReLU connections // 
//
//				if ((*myNeuralNetwork->getLayerAt(i - 1)->getLayerType() == 'R') and temp1 < 0)
//				{
//					temp1 = 0.0f;
//				}
//				if (i != hiddenLayerNumber) // we dont take into account the last row of hidden layer as there is nothing to summ up //
//				{
//
//					for (int n = i; n <= hiddenLayerNumber; n++) // adds all the other layers infront
//					{
//						float temp2 = 0.0f;
//						if (*myNeuralNetwork->getLayerAt(n - 1/* - 1*/)->getLayerType() == 'R') // Prev layer was ReLU
//						{
//							// char* Mychar = myNeuralNetwork->getLayerAt(n - 1)->getLayerType(); //
//							flagIsPrevLayerReLU = true;
//						}
//						else
//						{
//							// char* Mychar = myNeuralNetwork->getLayerAt(n - 1)->getLayerType(); // We are at a non ReLU layer
//							flagIsPrevLayerReLU = false;
//						}
//						for (int k = 0; k < myNeuralNetwork->getLayerAt(n)->getNodesNumber(); k++)
//						{
//							if (((flagIsPrevLayerReLU) and (myNeuralNetwork->getLayerAt(n)->getNodeAt(k)->getNodeValue() > 0)) or (!flagIsPrevLayerReLU))
//							{
//								temp2 = (float)temp2 + myNeuralNetwork->getLayerAt(n)->getNodeAt(k)->getNodeValue();
//							}
//						}
//						temp1 = (float)temp1 * temp2;
//					}
//				}
//
//				weightGradient[i - 1][j][m] = temp1;
//			}
//		}
//	}
//
//	biasGradient[hiddenLayerNumber] = lossTotal;
//
//	for (int i = hiddenLayerNumber - 1; i > -1; i--)
//	{
//		float temp1 = lossTotal;
//		bool flagIsPrevLayerReLU = false;
//		for (int j = i; j < hiddenLayerNumber; j++)
//		{
//			float temp2 = 0.0f;
//
//			if (*myNeuralNetwork->getLayerAt(j)->getLayerType() == 'R')
//			{
//				flagIsPrevLayerReLU = true;
//			}
//			else
//			{
//				flagIsPrevLayerReLU = false;
//			}
//
//			for (int m = 0; m < myNeuralNetwork->getLayerAt(j + 1)->getNodesNumber(); m++)
//			{
//				if (((flagIsPrevLayerReLU) and (myNeuralNetwork->getLayerAt(j)->getNodeAt(m)->getNodeValue() > 0)) or (!flagIsPrevLayerReLU))
//				{
//					temp2 = (float)temp2 + myNeuralNetwork->getLayerAt(j + 1)->getNodeAt(m)->getNodeValue();
//				}
//			}
//			temp1 = (float)temp1 * temp2;
//		}
//		biasGradient[i] = temp1;
//	}
//
//	/*for (int i = 0; i < 11; i++)
//	{
//		std::cout << (float)biasGradient[i] << " ";
//	}*/
//
//	// Bias Gradient Evaluation
//
//
//}
//
//void QNetwork::EvaluateGradientCopy()
//{
//	for (int i = 0; i < myNeuralNetwork->getLayerAt(hiddenLayerNumber + 1)->getNodesNumber(); i++) //  for last weights its different - they have to be diveded for E_i, not Etotal.
//	{
//		for (int j = 0; j < myNeuralNetwork->getLayerAt(hiddenLayerNumber + 1)->getNodeAt(i)->getTotalWeightNumber(); j++)
//		{
//			weightGradient[hiddenLayerNumber][i][j] = (float)localErrors[i] * myNeuralNetwork->getLayerAt(hiddenLayerNumber)->getNodeAt(j)->getNodeValue();
//		}
//	}
//
//	for (int i = 0; i < hiddenLayerNumber; i++)
//	{
//		for (int j = 0; j < myNeuralNetwork->getLayerAt(i + 1)->getNodesNumber(); j++)
//		{
//			for (int k = 0; k < myNeuralNetwork->getLayerAt(i + 1)->getNodeAt(j)->getTotalWeightNumber(); k++)
//			{
//				weightGradient[i][j][k] = (float)myNeuralNetwork->getLayerAt(i)->getNodeAt(k)->getNodeValue() * myNeuralNetwork->getLayerAt(i + 1)->getNodeAt(j)->getNodeValue() * BackPropogationRecursionMethod(i + 2);
//			}
//		}
//	}
//
//	biasGradient[hiddenLayerNumber] = lossTotal;
//
//
//	for (int i = 0; i < hiddenLayerNumber; i++)
//	{
//		biasGradient[i] = BackPropogationRecursionMethod(i + 1);
//	}
//	//int layerCounter = 0, nodeCounter = 0, weightCounter = 0;
//	//BackPropogationRecursionMethod(layerCounter, nodeCounter, weightCounter);
//}
//
//
//float QNetwork::BackPropogationRecursionMethod(int layerCounter)
//{
//	float sum = 0.0f;
//	if (layerCounter < hiddenLayerNumber + 1)
//	{
//		for (int i = 0; i < myNeuralNetwork->getLayerAt(layerCounter)->getNodesNumber(); i++)
//		{
//			if ((*myNeuralNetwork->getLayerAt(layerCounter - 1)->getLayerType() == 'R') and (myNeuralNetwork->getLayerAt(layerCounter)->getNodeAt(i)->getNodeValue() < 0))
//			{
//				return 0;
//			}
//			else
//			{
//				sum = sum + myNeuralNetwork->getLayerAt(layerCounter)->getNodeAt(i)->getNodeValue();
//			}
//		}
//		sum = sum * BackPropogationRecursionMethod(layerCounter + 1);
//	}
//	else
//	{
//		return lossTotal;
//	}
//	return sum;
//}
//
//void QNetwork::AdamPass()
//{
//	for (int i = 0; i < hiddenLayerNumber; i++)
//	{
//		float temp = biasOptimizer->Update(myNeuralNetwork->getLayerAt(i + 1)->getBiasValue(), biasGradient[i]);
//		myNeuralNetwork->getLayerAt(i + 1)->setBiasValue(temp);
//	}
//
//	for (int i = 0; i < hiddenLayerNumber + 1; i++)
//	{
//		for (int j = 0; j < myNeuralNetwork->getLayerAt(i + 1)->getNodesNumber(); j++)
//		{
//			for (int m = 0; m < myNeuralNetwork->getLayerAt(i + 1)->getNodeAt(j)->getTotalWeightNumber(); m++)
//			{
//				float temp = weightOptimizer[i][j][m]->Update(myNeuralNetwork->getLayerAt(i + 1)->getNodeAt(j)->getWeightValueAt(m), weightGradient[i][j][m]);
//				myNeuralNetwork->getLayerAt(i + 1)->getNodeAt(j)->setNodeValue(temp);
//			}
//		}
//	}
//}
//
//QNetwork::QNetwork(int inputLayerSize, int hiddenLayerNumber, int hiddenLayerSize, int outputLayerSize, float learningRate)
//{
//	if ((inputLayerSize > 0) and (hiddenLayerNumber > 0) and (hiddenLayerSize > 0) and (outputLayerSize > 0) and (learningRate >= 0 and learningRate <= 1))
//	{
//		// save values
//		this->inputLayerSize = inputLayerSize;
//		this->hiddenLayerNumber = hiddenLayerNumber;
//		this->hiddenLayerSize = hiddenLayerSize;
//		this->outputLayerSize = outputLayerSize;
//		this->learningRate = learningRate;
//
//		// init my Neural Network
//		myNeuralNetwork = new NeuralNetwork();
//
//		myNeuralNetwork->AddLinearLayer(0, inputLayerSize);
//		myNeuralNetwork->AddReLULayer(inputLayerSize, hiddenLayerSize);
//
//		for (int i = 0; i < hiddenLayerNumber - 2; i++)
//		{
//			if (i % 2 == 0)
//			{
//				myNeuralNetwork->AddLinearLayer(hiddenLayerSize, hiddenLayerSize);
//			}
//			else
//			{
//				myNeuralNetwork->AddReLULayer(hiddenLayerSize, hiddenLayerSize);
//			}
//		}
//
//		myNeuralNetwork->AddLinearLayer(hiddenLayerSize, hiddenLayerSize);
//		myNeuralNetwork->AddLinearLayer(hiddenLayerSize, outputLayerSize);
//
//		// For storing Error list
//
//		localErrors = new float[outputLayerSize];
//
//		// Make a list for storing evaluated gradient values  // 
//		// this only applies to ReLU connections
//
//		biasGradient = new float[hiddenLayerNumber + 1]; // bias
//
//		weightGradient = new float** [hiddenLayerNumber + 1];
//
//		for (int i = 0; i < hiddenLayerNumber + 1; i++)
//		{
//			int temp1 = myNeuralNetwork->getLayerAt(i + 1)->getNodesNumber();
//			weightGradient[i] = new float* [temp1];
//			for (int j = 0; j < temp1; j++)
//			{
//				int temp2 = myNeuralNetwork->getLayerAt(i + 1)->getNodeAt(j)->getTotalWeightNumber();
//				weightGradient[i][j] = new float[temp2];
//			}
//		}
//
//		//weightGradient[0] = new float[inputLayerSize * hiddenLayerSize];
//		//for (int i = 1; i < hiddenLayerNumber; i++)
//		//{
//		//	weightGradient[i] = new float[hiddenLayerSize * hiddenLayerSize]; // [(hiddenLayerSize+1)] respresents the previous layer size and the bias AND [hiddenLayerSize] represents the current layer size MAKING the summ of CONNECTIONS (weights and bias) needed for optimizing
//		//}
//		//weightGradient[hiddenLayerNumber] = new float[hiddenLayerSize * outputLayerSize];
//
//
//
//
//		// Make a list of Optimizers (Currently its just ADAM)
//
//		biasOptimizer = new Adam[hiddenLayerNumber + 1]; // bias
//
//		weightOptimizer = new Optimizer*** [hiddenLayerNumber + 1];
//
//		for (int i = 0; i < hiddenLayerNumber + 1; i++)
//		{
//			int temp1 = myNeuralNetwork->getLayerAt(i + 1)->getNodesNumber();
//			weightOptimizer[i] = new Optimizer** [temp1];
//			for (int j = 0; j < temp1; j++)
//			{
//				int temp2 = myNeuralNetwork->getLayerAt(i + 1)->getNodeAt(j)->getTotalWeightNumber();
//				weightOptimizer[i][j] = new Optimizer*[temp2];
//				for (int m = 0; m < temp2; m++)
//				{
//					weightOptimizer[i][j][m] = new Adam();
//				}
//			}
//		}
//	}
//}
//
//QNetwork::~QNetwork()
//{
//	delete myNeuralNetwork;
//}
//
//float QNetwork::CheckError(Layer* targValue)
//{
//	/*float errorValue = 0.0f;
//
//	for (int i = 0; i < myNeuralNetwork->getLayerAt(hiddenLayerNumber+1)->getNodesNumber(); i++)
//	{
//		float temp = (float) targValue->getNodeAt(i)->getNodeValue() - myNeuralNetwork->getLayerAt(hiddenLayerNumber + 1)->getNodeAt(i)->getNodeValue();
//		temp = (float)temp * temp;
//		localErrors[i] = (float)temp / myNeuralNetwork->getLayerAt(hiddenLayerNumber + 1)->getNodesNumber();
//		errorValue = (float)temp + errorValue;
//	}
//	errorValue = (float)errorValue / myNeuralNetwork->getLayerAt(hiddenLayerNumber + 1)->getNodesNumber();
//	return errorValue;*/
//	return lossTotal;
//}
//
//
//void QNetwork::Update(Layer* inputValue, Layer* targOutValue)
//{
//
//	myNeuralNetwork->setInputLayer(inputValue);
//	myNeuralNetwork->TransactionFF();
//	lossTotal = MSELossForBackPropogation(myNeuralNetwork->getLayerAt(hiddenLayerNumber + 1), targOutValue);
//	EvaluateGradientCopy();
//	AdamPass();
//	
//	
//	
//	// Weight back propogation evaluation (find VALUE and DVALUE through MSELoss for each weight and bias) OR we are finding the gradient value for the weight and biases
//	//
//	
//	
//	/*EvaluateGradient();
//	AdamPass();*/
//	//std::cout << BackPropogationRecursionMethod(1) << " it is \n";
//	
//	
//	
//	// ApplyAdamChanges();
//	
//	//
//	// Weight Adjustment based on Adam Alg. optimization with input data of VALUE and DVALUE
//}
//
//void QNetwork::UpdateBeta(Layer* inputValue, Layer* targOutValue)
//{
//
//	myNeuralNetwork->setInputLayer(inputValue);
//	myNeuralNetwork->TransactionFF();/*
//	//lossTotal = MSELossForBackPropogation(myNeuralNetwork->getLayerAt(hiddenLayerNumber + 1), targOutValue);
//	//EvaluateGradientCopy();
//	//AdamPass();*/
//}
//


