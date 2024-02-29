#include <iostream>
#include "QNetwork.h"
#include "Adam.h"
#include <chrono>
#include <thread>
#include <random>

#include <fstream>
#include <vector>
#include <algorithm>


void main()
{	
	NeuralNetwork* myNN = new NeuralNetwork(2, 2, 2, 2);
	float* temp = new float[2]{4.0f, 3.0f};
	myNN->SetInputLayer(temp);
	myNN->TransactionFF();
	myNN->print();
	//float value = myNN->evaluateWeightSum();
	std::cout << "\n\n";
	//myNN->LocalErrorMSE(temp);
	//std::cout << (float)myNN->evaluateWeightSum();
	myNN->TransactionBP(temp);
	myNN->print();
	std::cout << "\n\n";
	//std::cout << (float)myNN->evaluateWeightSum();

	system("pause");

}