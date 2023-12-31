#pragma once
#include "Layer.h"
class Linear : public Layer
{
private:
	Node** nodesList = nullptr;

	int nodesNumber = 0;
	float nodesBias = 0.0f;
	bool firstLayer = false;

public:
	Linear(int prevNodesNumber, int curNodesNumber);
	~Linear();
	char* getLayerType() override;

	float getBiasValue() override;
	void setBiasValue(float value) override;

	int getNodesNumber() override;

	Node** getNodesList() override;

	Node* getNodeAt(int index);
	void setNodeAt(int index, Node* value);

	void executeLayerFunction() override {};
};

