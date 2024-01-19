#include <iostream>
#include "QNetwork.h"
#include "Adam.h"
#include <chrono>


//float loss_function(float m)
//{
//	return (float)(m * m) - 2 * m + 1;
//}
//
//float grad_function(float m)
//{
//	return (float)2 * m - 2;
//}

bool check_convergence(float m1, float  m2)
{
	return (m1 == m2);
}

void main()
{

	bool converge = false;

	auto start_time = std::chrono::high_resolution_clock::now();
	Layer* current = new Linear(0,3);
	current->getNodeAt(0)->setNodeValue(0.5f);
	current->getNodeAt(1)->setNodeValue(0.46f);
	current->getNodeAt(2)->setNodeValue(0.22f);
	Layer* output = new Linear(0, 4);
	output->getNodeAt(0)->setNodeValue(1.0f);


	QNetwork* myQN = new QNetwork(3, 10, 5, 4);

	float th = 0.01f;
	float currValue = myQN->CheckError();
	int t = 0;


	while (/*converge != */true)      ////  Can take out comment to stop at converege
	{
		//float dWeight = grad_function(weight);
		float oldWeight = myQN->CheckError();
		myQN->Update(current, output);
		t++;
		if (check_convergence(myQN->CheckError(), oldWeight))
		{
			std::cout << "At iteration " << t << " converegerd, value = " << (float)myQN->CheckError() << "\n";
			converge = true;
		}
		else
		{
			std::cout << "Iteration: " << t << " and value = " << (float)myQN->CheckError() << "\n";
		}
	}



	//while ()
	//{
	//	//if ((float)currValue > 1) break;
	//	myQN->Update(current, output);
	//	std::cout << "Error : " << (float) myQN->CheckError() << "\n";
	//	currValue = myQN->CheckError();
	//}
	//std::cout << "Error : " << (float) myQN->CheckError() << "\n";

	auto end_time = std::chrono::high_resolution_clock::now();

	// Calculate the elapsed time
	auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time); 

	// Output the result
	std::cout << "Time taken: " << elapsed_time.count() << " microseconds" << std::endl; // currently 0.00137 sec which is good



	//std::cout << "hello world!\n\n";

	//Optimizer* myAdam = new Adam();

	//float weight = 0.0f;
	//int t = 0;

	

	//while (converge != true)
	//{
	//	t++;
	//	float dWeight = grad_function(weight);
	//	float oldWeight = weight;
	//	weight = myAdam->Update(weight, dWeight);
	//	if (check_convergence(weight, oldWeight))
	//	{
	//		std::cout << "At iteration " << t << " converegerd, value = " << (float)weight << "\n";
	//		converge = true;
	//	}
	//	else
	//	{
	//		std::cout << "Iteration: " << t << " and value = " << (float)weight << "\n";
	//	}
	//}

	system("pause");
}



