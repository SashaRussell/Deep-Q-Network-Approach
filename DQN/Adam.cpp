#include "Adam.h"

Adam::Adam(float learningRate)
{
	this->learningRate = learningRate;
}

Adam::~Adam()
{

}

float Adam::Update(float value, float dValue)
{
	// momentum with alpha

	this->momentum_dValue = (float)alpha * this->momentum_dValue + (1 - alpha) * dValue;

	// velocity with beta

	this->velocity_dValue = (float)beta * this->velocity_dValue + (1 - beta) * ((float)dValue * dValue);


	// evaluate correlation

	float temp_momentum_corr = (float)momentum_dValue / (1 - pow(beta, timeStep));

	float temp_velocity_corr = (float)velocity_dValue / (1 - pow(beta, timeStep));
	
	timeStep = timeStep + 1;

	return (float)value - ((float) learningRate * ((float) temp_momentum_corr / ((float) sqrt(temp_velocity_corr) + epsilon)));
}


