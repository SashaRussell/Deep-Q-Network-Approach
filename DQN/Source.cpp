#include <iostream>
#include "NeuralNetwork.h"

void main()
{

	std::cout << "hello world!\n\n";

	///

	NeuralNetwork myNN;

	myNN.AddLinearLayer(0, 5);
	myNN.AddReLULayer(5, 5);
	myNN.AddLeakyReLULayer(5, 5);

	Layer* myLayer = myNN.getLayerAt(2);

	/*myLayer->*/

	Node* myNode = myLayer->getNodeAt(4);


	if (myLayer != nullptr)
	{

		std::cout << "True! ";
		myNode->setNodeValue(10);
		std::cout << "Value = " << myNode->getNodeValue(); // checker

		std::cout << "\n\n";
	}
	else
	{
		std::cout << "False!\n\n";
	};

	//////


	/*Layer* ll = new LeakyReLU(4,8);
	Node** nodes = ll->getNodesList();

	for (int i = 0; i < ll->getNodesNumber(); i++)
	{
		if (i % 2 == 0)
		{
			nodes[i]->setNodeValue(-10);
		}
		else
		{
			nodes[i]->setNodeValue(10);
		}
		std::cout << (float)nodes[i]->getNodeValue() << "; ";
	}


	std::cout << "\n\n";
	ll->executeLayerFunction();
	
	
	for (int i = 0; i < ll->getNodesNumber(); i++)
	{
		std::cout << (float)nodes[i]->getNodeValue() << "; ";
	}*/


	/*char* ch = linear->getLayerType();
	
	for (int i = 0; true; i++)
	{
		if (*(ch + i) != '\0')
		{
			std::cout << *(ch + i);
		}
		else
		{
			std::cout << "\n\n";
			break;
		}
	}*/

	/*Node** nodes = linear->getNodesList();

	for (int i = 0; i < linear->getNodesNumber(); i++)
	{
		for (int j = 0; j < nodes[i]->getTotalWeightNumber(); j++)
		{
			std::cout << " (i = " << i << ", " << " j = " << j << ") = " << nodes[i]->getWeightValueAt(j) << "; ";
		}

		std::cout << "\n\n";
	}*/

	///

	/*Node** ns = new Node*[10];
	for(int )
	int prevLayer = 10;
	Node* n = new Node(prevLayer);
	n->Weight_HeNormal_Init();
	float val = ;
	for (int i = 0; i < 10; i++)
	{
		n->setNodeValue(i, 0.22222);
		std::cout << (float) n->getWeightValueAt(i) << "\n";
	}

	float sum = 0;
	for (int i = 0; i < 10; i++)
	{
		sum = (float) sum + n->getWeightValueAt(i);
	}
	n->setNodeValue(sum);
	std::cout << "\n\n" << (float)n->getNodeValue() << "\n";

	n->setNode(0, 0.222);
	std::cout << (float)n->getNode(0) << "\n";

	
	
	NeuralNetwork* nn = new NeuralNetwork();
	nn->AddLinearLayer(11);
	nn->AddLinearLayer(11);
	nn->AddLinearLayer(12);
	srand((unsigned)time(NULL));
	std::cout << (float)rand() / 32767 << "\n";*/

	system("pause");
}