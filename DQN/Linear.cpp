#include "Linear.h"

Linear::Linear(int prevNodesNumber, int curNodesNumber, char* weightInitType)
{
	this->weightInitType = weightInitType;
	nodesNumber = curNodesNumber;
	nodesList = new Node * [curNodesNumber];
	if (prevNodesNumber != 0)
	{
		if (memcmp(this->weightInitType, new char[9] {'H', 'e', 'N', 'o', 'r', 'm', 'a', 'l', '\0'}, sizeof(this->weightInitType)) == 0)
		{
			for (int i = 0; i < curNodesNumber; i++)
			{
				nodesList[i] = new Node(prevNodesNumber);
				nodesList[i]->Weight_HeNormal_Init();
			}
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

Linear::~Linear()
{
	delete[] nodesList;
}

char* Linear::getLayerType()
{
	return new char[7] {'L', 'i', 'n', 'e', 'a', 'r', '\0'};;
}

float Linear::getBiasValue()
{
	return nodesBias;
}

void Linear::setBiasValue(float value)
{
	nodesBias = value;
}

int Linear::getNodesNumber()
{
	return nodesNumber;
}

Node** Linear::getNodesList()
{
	return nodesList;
}


Node* Linear::getNodeAt(int index)
{
	return nodesList[index];
}

void Linear::setNodeAt(int index, Node* value)
{
	nodesList[index] = value;
}
