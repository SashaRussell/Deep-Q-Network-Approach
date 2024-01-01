#pragma once
#include "Node.h"
class Layer // abstract class
{
private:
public:
	Layer() {};
	virtual ~Layer() {};

	virtual char* getLayerType() = 0;

	virtual float getBiasValue() = 0;
	virtual void setBiasValue(float value) = 0;

	virtual int getNodesNumber() = 0;

	virtual Node** getNodesList() = 0;

	virtual Node* getNodeAt(int index) = 0;
	virtual void setNodeAt(int index, Node* value) = 0;

	virtual void executeLayerFunction() = 0; // A layer convert function (new L = alpha * old L) specific for each layer type (Linear, LeakyReLU, ReLU, Sigmoid ...)
};

