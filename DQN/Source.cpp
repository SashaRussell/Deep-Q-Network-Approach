#include <iostream>
#include "NeuralNetwork.h"

void main()
{

	std::cout << "hello world!\n\n";

	///

	NeuralNetwork myNN;

	myNN.AddLinearLayer(0, 5);
	myNN.AddReLULayer(5, 6);
	myNN.AddLinearLayer(6, 7);
	myNN.AddLeakyReLULayer(7, 8);
	myNN.AddLinearLayer(8, 9);
	myNN.AddLinearLayer(9, 10);

	Layer* myLayer = myNN.getLayerAt(0);

	for (int i = 0; i < myLayer->getNodesNumber(); i++)
	{
		myLayer->getNodeAt(i)->setNodeValue(10);
	}

	myNN.TransactionFF(); // Feed Forward

	for (int i = 1; i < 6; i++)
	{
		for (int j = 0; j < myNN.getLayerAt(i)->getNodesNumber(); j++)
		{
			std::cout << "weights in " << i << " " << j << ": ";
			for (int m = 0; m < myNN.getLayerAt(i)->getNodeAt(j)->getTotalWeightNumber(); m++)
			{
				std::cout << myNN.getLayerAt(i)->getNodeAt(j)->getWeightValueAt(m) << " / ";
			}

			std::cout << "\nNode value: " << myNN.getLayerAt(i)->getNodeAt(j)->getNodeValue() << "\n\n";
		}
	}

	std::cout << "\n\n";

	system("pause");
}