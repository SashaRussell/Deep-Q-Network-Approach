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
	NeuralNetwork* myNN = new NeuralNetwork(2, 100, 100, 2);
	float* temp = new float[2]{4.0f, 4.0f};
	myNN->SetInputLayer(temp);
	myNN->TransactionFF();
	//myNN->print();

	system("pause");
}