#pragma once
//#include <ctime>
//#include <cstdlib>
#include <random>
class Node
{
private:
	float nodeValue = 0.0f;

	float* nodeWeights = nullptr;

	int weightsNumber;  // It's a pointer, bc all nodes in a layer will have same amount of Weights !!! But need to be careful when deleting 1 node in a layer

	float weightsDistribution = 0.0f;

public:
	Node(int weightsNumber);
	~Node();

	void Weight_HeNormal_Init();

	void setWeightValueAt(int index, float value);
	float getWeightValueAt(int index);

	void setNodeValue(float value);
	float getNodeValue();

	int getTotalWeightNumber();
};

