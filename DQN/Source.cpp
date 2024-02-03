#include <iostream>
#include "QNetwork.h"
#include "Adam.h"
#include <chrono>
#include <thread>
#include <random>

#include <fstream>
#include <vector>
#include <algorithm>


//float loss_function(float m)
//{
//	return (float)(m * m) - 2 * m + 1;
//}
//
//float grad_function(float m)
//{
//	return (float)2 * m - 2;
//}

bool check_convergence(float m1, float  m2)
{
	return (m1 == m2);
}


void main()
{	
	float myArray[100][100];

	float* arrayPointer = &myArray[0][0];
	std::random_device rd;
	std::mt19937 gen(rd());
	// Define a distribution for float values in a certain range
	std::uniform_real_distribution<float> dis(0.0f, 1.0f);

	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 100; ++j) {
			myArray[i][j] = dis(gen);
		}
	}

	auto start_time = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			float value = *(arrayPointer + i * 10 + j) + (*(arrayPointer + i * 10 + j) * *(arrayPointer + i * 10 + j));
		}
	}
	auto end_time = std::chrono::high_resolution_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout << "Elapsed pointer time: " << elapsed_time.count() << " microseconds." << std::endl;

	start_time = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			float value = myArray[i][j] + (myArray[i][j] * myArray[i][j]);
		}
	}
	end_time = std::chrono::high_resolution_clock::now();
	elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout << "Elapsed array time: " << elapsed_time.count() << " microseconds." << std::endl;

	Layer* c = new Linear(0,1);
	c->getNodeAt(0)->setNodeValue(1000);
	Layer* t = new Linear(0, 1);
	t->getNodeAt(0)->setNodeValue(1000);

	QNetwork* myQN1 = new QNetwork(1, 8, 8, 1);
	//myQN->DisplayNeuralNetwork();
	//myQN1->Update(c, t);
	//float temp = 0;

	start_time = std::chrono::high_resolution_clock::now();
	myQN1->Update(c, t);
	end_time = std::chrono::high_resolution_clock::now();
	elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout << "Elapsed time: " << elapsed_time.count() << " microseconds." << std::endl;

	//std::cout << "Rec: " << temp << "\n";

	system("pause");
}

//void main()
//{
//
//	bool converge = false;
//
//	auto start_time = std::chrono::high_resolution_clock::now();
//	Layer* current = new Linear(0, 2);
//	current->getNodeAt(0)->setNodeValue(0.5f);
//	current->getNodeAt(1)->setNodeValue(0.5f);
//	Layer* output = new Linear(0, 2);
//	output->getNodeAt(0)->setNodeValue(0.99f);
//	output->getNodeAt(1)->setNodeValue(0.01f);
//
//
//	QNetwork* myQN = new QNetwork(2, 32, 32, 2);
//
//	myQN->Update(current, output);
//
//	float th = 0.01f;
//	float currValue = myQN->CheckError(output);
//	int t = 0;
//
//	float oldWeight = 10;
//	int kakar = 10;
//	///std::cout << (float)oldWeight << "\n";
//	while (/*converge != true*/ kakar > 1 /*t <5000*/)      ////  Can take out comment to stop at converege
//	{
//		//float dWeight = grad_function(weight);
//		oldWeight = myQN->CheckError(output);
//		myQN->Update(current, output);
//		kakar =(float)100000*myQN->CheckError(output);
//		t++;
//		if (check_convergence(myQN->CheckError(output), oldWeight))
//		{
//			std::cout << "At iteration " << t << " converegerd, value = " << (float)myQN->CheckError(output) << "\n";
//			converge = true;
//		}
//		else
//		{
//			//system()
//			std::cout << "Iteration: " << t << " and value = " << (float)myQN->CheckError(output) << "\n";
//		}
//		//std::this_thread::sleep_for(std::chrono::seconds(1));
//	}
//
//	myQN->myNeuralNetwork->TransactionFF();
//	float sum = 0.0f;
//	for (int i = 0; i < 2; i++)
//	{
//		sum = sum + myQN->myNeuralNetwork->getLayerAt(4)->getNodeAt(i)->getNodeValue();
//	}
//	std::cout << "Node: " << (float) myQN->myNeuralNetwork->getLayerAt(4)->getNodeAt(0)->getNodeValue() << "\n";
//	std::cout << "Node: " << (float) myQN->myNeuralNetwork->getLayerAt(4)->getNodeAt(1)->getNodeValue() << "\n";
//	
//	std::cout << "Node: " << (float)myQN->myNeuralNetwork->getLayerAt(0)->getNodeAt(0)->getNodeValue() << "\n";
//	std::cout << "Node: " << (float)myQN->myNeuralNetwork->getLayerAt(0)->getNodeAt(1)->getNodeValue() << "\n";
//
//
//	//while ()
//	//{
//	//	//if ((float)currValue > 1) break;
//	//	myQN->Update(current, output);
//	//	std::cout << "Error : " << (float) myQN->CheckError() << "\n";
//	//	currValue = myQN->CheckError();
//	//}
//	//std::cout << "Error : " << (float) myQN->CheckError() << "\n";
//
//	auto end_time = std::chrono::high_resolution_clock::now();
//
//	// Calculate the elapsed time
//	auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
//
//	// Output the result
//	std::cout << "Time taken: " << elapsed_time.count() << " microseconds" << std::endl; // currently 0.00137 sec which is good
//
//
//
//	//std::cout << "hello world!\n\n";
//
//	//Optimizer* myAdam = new Adam();
//
//	//float weight = 0.0f;
//	//int t = 0;
//
//
//
//	//while (converge != true)
//	//{
//	//	t++;
//	//	float dWeight = grad_function(weight);
//	//	float oldWeight = weight;
//	//	weight = myAdam->Update(weight, dWeight);
//	//	if (check_convergence(weight, oldWeight))
//	//	{
//	//		std::cout << "At iteration " << t << " converegerd, value = " << (float)weight << "\n";
//	//		converge = true;
//	//	}
//	//	else
//	//	{
//	//		std::cout << "Iteration: " << t << " and value = " << (float)weight << "\n";
//	//	}
//	//}
//
//	system("pause");
//}
//
//
//uint32_t swapEndian(uint32_t value) {
//    return ((value >> 24) & 0x000000FF) | ((value >> 8) & 0x0000FF00) | ((value << 8) & 0x00FF0000) | ((value << 24) & 0xFF000000);
//}
//
//// Function to read MNIST images
//std::vector<std::vector<uint8_t>> readMNISTImages(const std::string& filePath) {
//    std::ifstream file(filePath, std::ios::binary);
//
//    if (!file.is_open()) {
//        std::cerr << "Unable to open file: " << filePath << std::endl;
//        return {};
//    }
//
//    uint32_t magicNumber, numImages, numRows, numCols;
//    file.read(reinterpret_cast<char*>(&magicNumber), sizeof(magicNumber));
//    file.read(reinterpret_cast<char*>(&numImages), sizeof(numImages));
//    file.read(reinterpret_cast<char*>(&numRows), sizeof(numRows));
//    file.read(reinterpret_cast<char*>(&numCols), sizeof(numCols));
//
//    magicNumber = swapEndian(magicNumber);
//    numImages = swapEndian(numImages);
//    numRows = swapEndian(numRows);
//    numCols = swapEndian(numCols);
//
//    std::vector<std::vector<uint8_t>> images(numImages, std::vector<uint8_t>(numRows * numCols));
//
//    for (auto& image : images) {
//        file.read(reinterpret_cast<char*>(image.data()), numRows * numCols);
//    }
//
//    return images;
//}
//
//// Function to read MNIST labels
//std::vector<uint8_t> readMNISTLabels(const std::string& filePath) {
//    std::ifstream file(filePath, std::ios::binary);
//
//    if (!file.is_open()) {
//        std::cerr << "Unable to open file: " << filePath << std::endl;
//        return {};
//    }
//
//    uint32_t magicNumber, numLabels;
//    file.read(reinterpret_cast<char*>(&magicNumber), sizeof(magicNumber));
//    file.read(reinterpret_cast<char*>(&numLabels), sizeof(numLabels));
//
//    magicNumber = swapEndian(magicNumber);
//    numLabels = swapEndian(numLabels);
//
//    std::vector<uint8_t> labels(numLabels);
//
//    file.read(reinterpret_cast<char*>(labels.data()), numLabels);
//
//    return labels;
//}
//
////////////int main() {
////////////    std::string trainImagesPath = "C:/MNIST/archive/train-images.idx3-ubyte";
////////////    std::string trainLabelsPath = "C:/MNIST/archive/train-labels.idx1-ubyte";
////////////
////////////    std::vector<std::vector<uint8_t>> trainImages = readMNISTImages(trainImagesPath);
////////////    std::vector<uint8_t> trainLabels = readMNISTLabels(trainLabelsPath);
////////////
////////////    Layer* current = new Linear(0, 784);
////////////    /*current->getNodeAt(0)->setNodeValue(0.5f);
////////////    current->getNodeAt(1)->setNodeValue(0.5f);*/
////////////    Layer* desiredOutput = new Linear(0, 10);
////////////    /*output->getNodeAt(0)->setNodeValue(0.99f);
////////////    output->getNodeAt(1)->setNodeValue(0.01f);*/
////////////
////////////
////////////    QNetwork* myQN = new QNetwork(784, 16, 16, 10);
////////////
////////////
////////////    for (int i = 0; i < 500; i++)
////////////    {
////////////        if (i % 50 == 0)
////////////        {
////////////            std::cout << "iteration " << i << "\n";
////////////        }
////////////        for (int j = 0; j < trainImages[i].size(); j++) 
////////////        {
////////////            current->getNodeAt(j)->setNodeValue((float) static_cast<int>(trainImages[i][j]));
////////////        }
////////////        int labelNum = (int)static_cast<int>(trainLabels[i]);
////////////        for (int j = 0; j < 10; j++)
////////////        {
////////////            if (labelNum != j)
////////////            {
////////////                desiredOutput->getNodeAt(j)->setNodeValue(1);
////////////            }
////////////            else
////////////            {
////////////                desiredOutput->getNodeAt(j)->setNodeValue(100);
////////////            }
////////////        }
////////////        myQN->Update(current, desiredOutput);
////////////    }
////////////
////////////    int whichOne = 1;
////////////
////////////
////////////    std::cout << "Label: " << static_cast<int>(trainLabels[whichOne]) << "\n";
////////////
////////////    for (int j = 0; j < trainImages[whichOne].size(); j++) {
////////////        current->getNodeAt(j)->setNodeValue((float) static_cast<int>(trainImages[whichOne][j]));
////////////    }
////////////    int labelNum = (int)static_cast<int>(trainLabels[whichOne]);
////////////    for (int j = 0; j < 10; j++)
////////////    {
////////////        if (labelNum != j)
////////////        {
////////////            desiredOutput->getNodeAt(j)->setNodeValue(0.01f);
////////////        }
////////////        else
////////////        {
////////////            desiredOutput->getNodeAt(j)->setNodeValue(100.0f);
////////////        }
////////////    }
////////////    myQN->Update(current, desiredOutput);
////////////
////////////    for (int i = 0; i < 10; i++)
////////////    {
////////////        std::cout << myQN->myNeuralNetwork->getLayerAt(17)->getNodeAt(i)->getNodeValue() << " ";
////////////    }
////////////
////////////
////////////    // Read MNIST training images and labels
////////////   
////////////    //int counter = 0;
////////////    //// Use the data as needed..
////////////    //std::cout << "hello world!\n";
////////////    //for (int j = 5; j < 6; j++) {
////////////    //    std::cout << "Label: " << static_cast<int>(trainLabels[j]) << "\n";
////////////    //    for (int i = 0; i < trainImages[j].size(); i++) {
////////////    //        std::cout << static_cast<int>(trainImages[j][i]) << "\t";
////////////
////////////    //        if (counter == 27)
////////////    //        {
////////////    //            std::cout << "\n";
////////////    //            counter = 0;
////////////    //        }
////////////    //        else
////////////    //        {
////////////    //            counter++;
////////////    //        }
////////////    //    }
////////////    //}  
////////////    //
////////////    //std::cout << "\n";
////////////    system("pause");
////////////
////////////
////////////    return 0;
////////////}

