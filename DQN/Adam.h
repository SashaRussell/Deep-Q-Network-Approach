#pragma once
#include "Optimizer.h"
class Adam : public Optimizer
{
private:
	float momentum_dValue = 0.0f, velocity_dValue = 0.0f;
	float learningRate = 0.01f, alpha = 0.9f, beta = 0.999f, epsilon = 1e-8;
	int timeStep = 1;
public:
	Adam(float learningRate = 0.001);
	~Adam();

	float Update(float value, float dValue) override;
};