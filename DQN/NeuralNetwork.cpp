#include "NeuralNetwork.h"
#include "iostream"

float* NeuralNetwork::HeNormal_Init(int prevNodeNumber, int currNodesNumber, std::mt19937& generator) // INIT FOR WEIGHTS
{
	int WeightNumber = prevNodeNumber * currNodesNumber;
	float* array = new float[WeightNumber];
	for (int i = 0; i < WeightNumber; i++)
	{
		std::uniform_real_distribution<float> distribution(0.0, 1.0);
		array[i] = static_cast<float>(distribution(generator) * sqrt(2.0 / WeightNumber));
	}
	return array;
}

void NeuralNetwork::NullNodesAt()
{
	for (int j = 0; j < inputLayerSize; j++)
	{
		myNeuralNetworkNodes[0][j] = 0.0f;
	}

	for (int i = 1; i < nnSize - 1; i++)
	{
		for (int j = 0; j < hiddenLayerSize; j++)
		{
			myNeuralNetworkNodes[i][j] = 0.0f;
		}
	}
	for (int j = 0; j < outputLayerSize; j++)
	{
		myNeuralNetworkNodes[nnSize - 1][j] = 0.0f;
	}
}



NeuralNetwork::NeuralNetwork(int inputLayerSize, int hiddenLayerNumber, int hiddenLayerSize, int outputLayerSize, float learningRate)
{
	this->nnSize = hiddenLayerNumber + 2;
	this->inputLayerSize = inputLayerSize;
	this->hiddenLayerNumber = hiddenLayerNumber;
	this->hiddenLayerSize = hiddenLayerSize;
	this->outputLayerSize = outputLayerSize;
	this->learningRate = learningRate;
	{ /// Node Init
		myNeuralNetworkNodes = new float* [nnSize];
		// Input Layer
		myNeuralNetworkNodes[0] = new float[inputLayerSize];
		for (int j = 0; j < inputLayerSize; j++)
		{
			myNeuralNetworkNodes[0][j] = 0.0f;
		}
		// Inner Layers
		for (int i = 1; i < nnSize - 1; i++)
		{
			myNeuralNetworkNodes[i] = new float[hiddenLayerSize];
			for (int j = 0; j < hiddenLayerSize; j++)
			{
				myNeuralNetworkNodes[i][j] = 0.0f;
			}
		}
		// Output Layer
		myNeuralNetworkNodes[nnSize - 1] = new float[outputLayerSize];
		for (int j = 0; j < outputLayerSize; j++)
		{
			myNeuralNetworkNodes[nnSize - 1][j] = 0.0f;
		}
	}
	{ /// Weight Init

		//std::random_device rd; // for Init-ing random HeNormal Weights
		//std::mt19937 gen(rd());

		std::mt19937 gen(42);

		myNeuralNetworkWeights = new float* [nnSize];
		// Input Layer

		myNeuralNetworkWeights[0] = nullptr;
		myNeuralNetworkWeights[1] = HeNormal_Init(inputLayerSize, hiddenLayerSize, gen);
		for (int i = 2; i < nnSize - 1; i++)
		{
			myNeuralNetworkWeights[i] = HeNormal_Init(hiddenLayerSize, hiddenLayerSize, gen);
		}
		myNeuralNetworkWeights[nnSize - 1] = HeNormal_Init(hiddenLayerSize, outputLayerSize, gen);
	}
	{ /// Layer Type Init (Concept is -> Input, Layer=Input+1 , Output and Layer=Output-1 are always Linear, Inner layers - if their order %2==0 then they are ReLU, otherwise Linear)
		myLayerType = new char[nnSize];
		for (int i = 0; i < nnSize; i++)
		{
			if ((i < 2) or (i >= hiddenLayerNumber))
			{
				myLayerType[i] = 'L';
			}
			else
			{
				if (i % 2 == 0)
				{
					myLayerType[i] = 'R';
				}
				else
				{
					myLayerType[i] = 'L';
				}
			}
		}
	}
	{ /// Bias Init
		myNeuralNetworkBias = new float[nnSize];
		for (int i = 0; i < nnSize; i++)
		{
			myNeuralNetworkBias[i] = 0.0f;
		}
	}
}

bool NeuralNetwork::TransactionFF(float* InputLayer)
{
	if (nnSize > 3)
	{
		for (int i = 0; i < inputLayerSize; i++)
		{
			myNeuralNetworkNodes[0][i] = InputLayer[i];
		}

		int lastLayerIndex = nnSize - 1;
		// Input layers case
		float summ = 0.0f;
		for (int j = 0; j < hiddenLayerSize; j++)
		{
			int scale = j * inputLayerSize;
			for (int k = 0; k < inputLayerSize; k++)
			{
				summ = summ + static_cast<float>(myNeuralNetworkWeights[1][k + scale] * myNeuralNetworkNodes[0][k]);
				//std::cout << "\nIm multiplying " << (float)myNeuralNetworkWeights[1][k + scale] << " to " << (float)myNeuralNetworkNodes[0][k] << "\n";
			}
			summ = summ + myNeuralNetworkBias[1];
			myNeuralNetworkNodes[1][j] = (float)summ;
			summ = 0.0f;
		}
		// Inner layer case
		summ = 0.0f;
		for (int i = 2; i < lastLayerIndex; i++)
		{

			for (int j = 0; j < hiddenLayerSize; j++)
			{
				int scale = j * hiddenLayerSize;
				for (int k = 0; k < hiddenLayerSize; k++)
				{
					summ = summ + static_cast<float>(myNeuralNetworkWeights[i][k + scale] * myNeuralNetworkNodes[i - 1][k]);
					//std::cout << "\nIm multiplying " << (float)myNeuralNetworkWeights[i][k + scale] << " to " << (float)myNeuralNetworkNodes[i - 1][k] << "\n";
				}
				summ = summ + myNeuralNetworkBias[i];
				if ((myLayerType[i] == 'R') and (summ < 0)) {
					myNeuralNetworkNodes[i][j] = 0.0f;
				}
				else
				{
					myNeuralNetworkNodes[i][j] = (float)summ;
				}
				summ = 0.0f;
			}
		}
		summ = 0.0f;
		// Output layer case
		for (int j = 0; j < outputLayerSize; j++)
		{
			int scale = j * hiddenLayerSize;
			for (int k = 0; k < hiddenLayerSize; k++)
			{
				summ = summ + static_cast<float>(myNeuralNetworkWeights[lastLayerIndex][k + scale] * myNeuralNetworkNodes[hiddenLayerNumber][k]);
				//std::cout << "\nIm multiplying " << (float)myNeuralNetworkWeights[lastLayerIndex][k + scale] << " to " << (float)myNeuralNetworkNodes[hiddenLayerNumber][k] << "\n";
			}
			summ = summ + myNeuralNetworkBias[lastLayerIndex];
			myNeuralNetworkNodes[lastLayerIndex][j] = (float)summ;
			summ = 0.0f;
		}
		return true;
	}
	return false;
}

float* NeuralNetwork::LocalErrorMSE(float* targetOutput)
{
	float* localError = new float[outputLayerSize];
	int temp = nnSize - 1;
	for (int i = 0; i < outputLayerSize; i++)
	{
		localError[i] = static_cast<float>( - (2 * (targetOutput[i] - myNeuralNetworkNodes[temp][i]) / outputLayerSize));
	}

	return localError;
}

bool NeuralNetwork::TransactionBP(float* targetOutput) // PRINCIPLE :: TO SHORTEN COMPUTE TIME WE USE NODE STORAGE AS A TEMP VALUE OF ALL THE WEIGHT MULITPLICATION FROM THE RIGHT SIDE. THAT WAY WE DONT HAVE TO DO UNESSESARY MULTIPLICATIONS AGAIN AND AGAIN (WHEN WE ALREADY DID THEM BEFORE). 
//IF WE WANT TO COMPUTE A GRADIENT FOR A GIVEN WEIGHT WE JUST USE THE VALUE IN THE RIGHT NODE AS IT CONTAINS ALL THE VALUES OF PREVIOUS EVALUATIONS.
//ADDITIONALLY WE SAVE SPACE AS WE ARE JUST REUSING THE NODES ARRAY WHICH WE ALREADY MADE
{

	localError = LocalErrorMSE(targetOutput);

	//NullNodesAt();

	int lastLayerIndex = nnSize - 1;
	for (int i = 0; i < outputLayerSize; i++) // WE START OUR OPERATION FROM OUTPUT NODES, SO LETS SET THEM TO ERROR VALUE 
	{
		myNeuralNetworkNodes[lastLayerIndex][i] = (float)learningRate * localError[i];
	}

	// output case
	float sum = 0.0f;

	for (int i = 0; i < hiddenLayerSize; i++)
	{
		for (int j = 0; j < outputLayerSize; j++)
		{
			int scale = j * hiddenLayerSize;
			sum += static_cast<float>(myNeuralNetworkNodes[lastLayerIndex][j] * myNeuralNetworkWeights[lastLayerIndex][i + scale]);
			//std::cout << "this " << myNeuralNetworkNodes[lastLayerIndex][j] << " multiply by " << myNeuralNetworkWeights[lastLayerIndex][i + scale] << " and summ " << sum << "\n";
			if (myNeuralNetworkWeights[lastLayerIndex][i + scale] > 0.0000001 or myNeuralNetworkWeights[lastLayerIndex][i + scale] < -0.0000001)
			{
				myNeuralNetworkWeights[lastLayerIndex][i + scale] -= static_cast<float>(myNeuralNetworkNodes[hiddenLayerNumber][i] * myNeuralNetworkNodes[lastLayerIndex][j]); // gdarient update for the weights in the last layer
			}
			else
			{
				myNeuralNetworkWeights[lastLayerIndex][i + scale] = 0.0f;
			}

		}
		//std::cout << "finish adding.the layer " << hiddenLayerNumber << " item " << i << " which was " << myNeuralNetworkNodes[hiddenLayerNumber][i] << " became " << (float)sum << "\n\n";
		myNeuralNetworkNodes[hiddenLayerNumber][i] = (float)sum;
		sum = 0.0f;
	}

	// hidden layer case
	bool flag = false;
	for (int l = hiddenLayerNumber; l > 1; l--)
	{
		if (myLayerType[l - 1] == 'R') // 
		{
			for (int i = 0; i < hiddenLayerSize; i++)
			{
				if (myNeuralNetworkNodes[l - 1][i] > 0)
				{
					for (int j = 0; j < hiddenLayerSize; j++)
					{
						int scale = j * hiddenLayerSize;
						sum += static_cast<float>(myNeuralNetworkNodes[l][j] * myNeuralNetworkWeights[l][i + scale]);
						if (myNeuralNetworkWeights[l][i + scale] > 0.0000001f or myNeuralNetworkWeights[l][i + scale] < -0.0000001f)
						{
							myNeuralNetworkWeights[l][i + scale] -= static_cast<float>(myNeuralNetworkNodes[l - 1][i] * myNeuralNetworkNodes[l][j]); // gdarient update for the weights in the last layer
						}
						else
						{
							myNeuralNetworkWeights[l][i + scale] = 0.0f;
						}

						//std::cout << "multiply learning rate  (next node) " << myNeuralNetworkNodes[l - 1][i] << " with prev values " << myNeuralNetworkNodes[l][j] << "\n";
					}
				}
				else
				{
					for (int j = 0; j < hiddenLayerSize; j++)
					{
						int scale = j * hiddenLayerSize;
						sum += static_cast<float>(myNeuralNetworkNodes[l][j] * myNeuralNetworkWeights[l][i + scale]);
						if (myNeuralNetworkWeights[l][i + scale] > 0.0000001f or myNeuralNetworkWeights[l][i + scale] < -0.0000001f)
						{
							myNeuralNetworkWeights[l][i + scale] -= static_cast<float>(myNeuralNetworkNodes[l - 1][i] * myNeuralNetworkNodes[l][j]); // gdarient update for the weights in the last layer
						}
						else
						{
							myNeuralNetworkWeights[l][i + scale] = 0.0f;
						}
					}
				}
				myNeuralNetworkNodes[l - 1][i] = (float)sum;
				sum = 0.0f;
			}
		}
		else if (myLayerType[l - 1] == 'L')
		{
			for (int i = 0; i < hiddenLayerSize; i++)
			{
				for (int j = 0; j < hiddenLayerSize; j++)
				{
					int scale = j * hiddenLayerSize;
					sum += static_cast<float>(myNeuralNetworkNodes[l][j] * myNeuralNetworkWeights[l][i + scale]);
					if (myNeuralNetworkWeights[l][i + scale] > 0.0000001f or myNeuralNetworkWeights[l][i + scale] < -0.0000001f)
					{
						myNeuralNetworkWeights[l][i + scale] -= static_cast<float>(myNeuralNetworkNodes[l - 1][i] * myNeuralNetworkNodes[l][j]); // gdarient update for the weights in the last layer
					}
					else
					{
						myNeuralNetworkWeights[l][i + scale] = 0.0f;
					}
				}
				myNeuralNetworkNodes[l - 1][i] = (float)sum;
					sum = 0.0f;
			}
		}
	}

	// input layer case

	for (int i = 0; i < inputLayerSize; i++)
	{
		for (int j = 0; j < hiddenLayerSize; j++)
		{
			int scale = j * inputLayerSize + i;
			if (myNeuralNetworkWeights[1][scale] > 0.0000001 or myNeuralNetworkWeights[1][scale] < -0.0000001f)
			{
				myNeuralNetworkWeights[1][scale] -= static_cast<float>(myNeuralNetworkNodes[0][i] * myNeuralNetworkNodes[1][j]); // gdarient update for the weights in the last layer
			}
			else
			{
				myNeuralNetworkWeights[1][scale] = 0.0f;
			}
		}
		sum = 0.0f;
	}

	return true;
}

float NeuralNetwork::evaluateWeightSum()
{
	// start case



	// inner case



	// end case



	return 0.0f;
}


void NeuralNetwork::print()
{	// Nodes

	std::cout << "Layer input: ";
	for (int i = 0; i < inputLayerSize; i++)
	{
		std::cout << myNeuralNetworkNodes[0][i] << " ";
	}
	std::cout << "\n";

	
	for (int i = 1; i <= hiddenLayerNumber; i++)
	{
		std::cout << "Layer " << i <<": ";
		for (int j = 0; j < hiddenLayerSize; j++)
		{
			std::cout << myNeuralNetworkNodes[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "Layer output: ";
	for (int i = 0; i < outputLayerSize; i++)
	{
		std::cout << myNeuralNetworkNodes[nnSize - 1][i] << " ";
	}
	std::cout << "\n\n";

	// Weights
	std::cout << "Weight Layer 1: ";
	for (int i = 0; i < inputLayerSize * hiddenLayerSize; i++)
	{
		std::cout << myNeuralNetworkWeights[1][i] << " ";
	}
	std::cout << "\n";
	for (int i = 2; i < nnSize - 1; i++)
	{
		std::cout << "Weight Layer " << i <<": ";
		for (int j = 0; j < hiddenLayerSize * hiddenLayerSize; j++)
		{
			std::cout << myNeuralNetworkWeights[i][j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "Weight Layer " << nnSize-1 << ": ";
	for (int i = 0; i < hiddenLayerSize * outputLayerSize; i++)
	{
		std::cout << myNeuralNetworkWeights[nnSize - 1][i] << " ";
	}
	std::cout << "\n";

};

void NeuralNetwork::printl()
{	// Nodes

	std::cout << "Layer input: ";
	for (int i = 0; i < inputLayerSize; i++)
	{
		std::cout << myNeuralNetworkNodes[0][i] << " ";
	}
	std::cout << "\n";


	for (int i = 1; i <= hiddenLayerNumber; i++)
	{
		std::cout << "Layer " << i << ": ";
		for (int j = 0; j < hiddenLayerSize; j++)
		{
			std::cout << myNeuralNetworkNodes[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "Layer output: ";
	for (int i = 0; i < outputLayerSize; i++)
	{
		std::cout << myNeuralNetworkNodes[nnSize - 1][i] << " ";
	}
	std::cout << "\n\n";

};


NeuralNetwork::~NeuralNetwork()
{

}

