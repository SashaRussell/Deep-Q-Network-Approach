#pragma once
#include "Layer.h"
class LeakyReLU : public Layer
{
private:
	Node** nodesList = nullptr;

	int nodesNumber = 0;
	float nodesBias = 0.0f;
	bool firstLayer = false;

	char* weightInitType;

	float koef = 0.01;

public:
	LeakyReLU(int prevNodesNumber, int curNodesNumber, char* weightInitType = new char[9] {'H', 'e', 'N', 'o', 'r', 'm', 'a', 'l', '\0'}, float koef = 0.01);
	~LeakyReLU();
	char* getLayerType() override;

	float getBiasValue() override;
	void setBiasValue(float value) override;

	int getNodesNumber() override;

	Node** getNodesList() override;

	Node* getNodeAt(int index);
	void setNodeAt(int index, Node* value);

	void executeLayerFunction() override;
};


