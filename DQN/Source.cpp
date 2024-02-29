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
	NeuralNetwork* myNN = new NeuralNetwork(2, 4, 4, 2, 0.01f);
	float* temp = new float[2] {4.0f, 3.0f};
	for(int i = 0; i < 50; i++)
	{
		myNN->TransactionFF(temp);


		myNN->TransactionBP(temp);


		myNN->NullNodesAt();
	}
	
	myNN->TransactionFF(temp);


	std::cout << "Result after training (50 iterations with lr = 0.01):\n\n";
	myNN->printl();
	std::cout << "\n";

	system("pause");

}