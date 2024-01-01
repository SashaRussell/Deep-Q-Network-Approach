#pragma once
#include "Layer.h"
class ReLU : public Layer
{
private:
	Node** nodesList = nullptr;

	int nodesNumber = 0;
	float nodesBias = 0.0f;
	bool firstLayer = false;

	char* weightInitType;

public:
	ReLU(int prevNodesNumber, int curNodesNumber, char* weightInitType);
	~ReLU();
	char* getLayerType() override;

	float getBiasValue() override;
	void setBiasValue(float value) override;

	int getNodesNumber() override;

	Node** getNodesList() override;

	Node* getNodeAt(int index);
	void setNodeAt(int index, Node* value);

	void executeLayerFunction() override;
};

