#pragma once
#include "Layer.h"
class Linear : public Layer
{
private:
	Node** nodesList = nullptr;

	int nodesNumber = 0;
	float nodesBias = 0.0f;
	bool firstLayer = false;

	char* weightInitType;

public:
	Linear(int prevNodesNumber, int curNodesNumber, char* weightInitType = new char[9] {'H', 'e', 'N', 'o', 'r', 'm', 'a', 'l', '\0'});
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

