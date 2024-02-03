#include "Node.h"
#include <math.h>

Node::Node(int weightsNumber)
{
	if (weightsNumber != 0)
	{
		this->weightsNumber = weightsNumber;
		nodeWeights = new float[weightsNumber];
	}
}

Node::~Node()
{
	delete[] nodeWeights;
}

void Node::Weight_HeNormal_Init()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution(0.0, 1.0);
	this->weightsDistribution = (float) sqrt((float) 2/ this->weightsNumber);
	for (int i = 0; i < this->weightsNumber; i++)
	{
		nodeWeights[i] = (float) distribution(gen) * weightsDistribution;
	}
}

void Node::setWeightValueAt(int index, float value)
{
	nodeWeights[index] = value;
}

float Node::getWeightValueAt(int index)
{
	return nodeWeights[index];
}

void Node::setNodeValue(float value)
{
	nodeValue = value;
}

float Node::getNodeValue()
{
	return (float)nodeValue;
}

int Node::getTotalWeightNumber()
{
	return weightsNumber;
}