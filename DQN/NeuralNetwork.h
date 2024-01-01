#pragma once
#include "Linear.h"
#include "ReLU.h"
#include "LeakyReLU.h"

#include <vector>
class NeuralNetwork
{
private:
	int nnSize = 0;
	std::vector <Layer*> layers;
public:
	NeuralNetwork();
	~NeuralNetwork();
	
	bool AddLinearLayer(int prevLayerSize, int currLayerSize, char* weightInitType = new char[9] {'H', 'e', 'N', 'o', 'r', 'm', 'a', 'l', '\0'}); // returns 1 on success, 0 - fail, He Normal Weight Init by default
	bool AddLeakyReLULayer(int prevLayerSize, int currLayerSize, char* weightInitType = new char[9] {'H', 'e', 'N', 'o', 'r', 'm', 'a', 'l', '\0'}, float koef = 0.01); // same as above
	bool AddReLULayer(int prevLayerSize, int currLayerSize, char* weightInitType = new char[9] {'H', 'e', 'N', 'o', 'r', 'm', 'a', 'l', '\0'}); // same as above

	Layer* getLayerAt(int index);


	//bool AddSigmoidLayer(); // Not implimented yet
};
