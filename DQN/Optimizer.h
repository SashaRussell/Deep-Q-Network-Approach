#pragma once
#include "cmath" 
class Optimizer // abstract class
{
private:
public:
	Optimizer() {};
	virtual ~Optimizer() {};

	virtual float Update(float value, float dValue) = 0;
};

