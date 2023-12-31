#include "LeakyReLU.h"

LeakyReLU::LeakyReLU(int prevNodesNumber, int curNodesNumber, float alpha)
{
	this->alpha = alpha;
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

LeakyReLU::~LeakyReLU()
{
	delete[] this->nodesList;
}

char* LeakyReLU::getLayerType()
{
	return new char[10] {'L', 'e', 'a', 'k', 'y', 'R', 'e', 'L', 'U', '\0'};
}

float LeakyReLU::getBiasValue()
{
	return this->nodesBias;
}

void LeakyReLU::setBiasValue(float value)
{
	this->nodesBias = value;
}

int LeakyReLU::getNodesNumber()
{
	return this->nodesNumber;
}

Node** LeakyReLU::getNodesList()
{
	return this->nodesList;
}

void LeakyReLU::executeLayerFunction()
{
	for (int i = 0; i < this->nodesNumber; i++)
	{
		if (nodesList[i]->getNodeValue() < 0)
		{
			nodesList[i]->setNodeValue((float)nodesList[i]->getNodeValue() * this->alpha);
		}
	}
}

Node* LeakyReLU::getNodeAt(int index)
{
	return nodesList[index];
}

void LeakyReLU::setNodeAt(int index, Node* value)
{
	nodesList[index] = value;
}


