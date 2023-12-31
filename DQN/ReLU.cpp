#include "ReLU.h"

ReLU::ReLU(int prevNodesNumber, int curNodesNumber)
{
	nodesNumber = curNodesNumber;
	nodesList = new Node * [curNodesNumber];
	if (prevNodesNumber != 0)
	{
		for (int i = 0; i < curNodesNumber; i++)
		{
			nodesList[i] = new Node(prevNodesNumber);
			nodesList[i]->Weight_HeNormal_Init();
		}
	}
	else
	{
		firstLayer = true;
		for (int i = 0; i < curNodesNumber; i++)
		{
			nodesList[i] = new Node(prevNodesNumber);
		}
	}
}

ReLU::~ReLU()
{
	delete[] nodesList;
}

char* ReLU::getLayerType()
{
	return new char[5] {'R', 'e', 'L', 'U', '\0'};
}

float ReLU::getBiasValue()
{
	return nodesBias;
}

void ReLU::setBiasValue(float value)
{
	nodesBias = value;
}

int ReLU::getNodesNumber()
{
	return nodesNumber;
}

Node** ReLU::getNodesList()
{
	return nodesList;
}

void ReLU::executeLayerFunction()
{
	for (int i = 0; i < this->nodesNumber; i++)
	{
		if (nodesList[i]->getNodeValue() < 0)
		{
			nodesList[i]->setNodeValue(0);
		}
	}
}

Node* ReLU::getNodeAt(int index)
{
	return nodesList[index];
}

void ReLU::setNodeAt(int index, Node* value)
{
	nodesList[index] = value;
}
