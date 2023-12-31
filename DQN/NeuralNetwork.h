#pragma once
#include <vector>
class NeuralNetwork
{
private:
	int numLayers; // Number of Hidden Layers
	std::vector<float>** layers; // State batch
	std::vector<float>** weights;
	std::vector<float>* bias; // Bias Values
	float Weight_HeInitNormal(int fan_in);
public:
	NeuralNetwork();
	void AddLinearLayer(int size);
	void AddLeakyReLULayer();
	void AddReLULayer();
	void AddSigmoidLayer();
	~NeuralNetwork();
};

