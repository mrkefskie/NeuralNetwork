#include <stdlib.h>
#include <stdio.h>

#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>

//#include "NeuralNetwork\Node.h"
#include "NeuralNetwork\SimpleNetwork.h"

#include "Data\Data.h"

#include "GUI\SimpleScreen.h"

#define AMOUNT_OF_TRAINING_POINTS 5

int main(int argc, char** argv)
{
#pragma region DATA_DEFINE
	Data::DATA_TYPE XOR[AMOUNT_OF_TRAINING_POINTS]; // Create data object

	for (int i = 0; i < AMOUNT_OF_TRAINING_POINTS; i++)
	{
		// Allocate memory for every instance
		XOR[i].input_length = 2;
		XOR[i].output_length = 1;

		XOR[i].inputs = (float*)malloc(sizeof(float) * XOR[i].input_length);
		XOR[i].outputs = (float*)malloc(sizeof(float) * XOR[i].output_length);
	}

	// Set the data for XOR
	XOR[0].inputs[0] = 0.0f;
	XOR[0].inputs[1] = 0.0f;
	XOR[0].outputs[0] = 0.0f;

	XOR[1].inputs[0] = 0.0f;
	XOR[1].inputs[1] = 1.0f;
	XOR[1].outputs[0] = 1.0f;

	XOR[2].inputs[0] = 1.0f;
	XOR[2].inputs[1] = 0.0f;
	XOR[2].outputs[0] = 1.0f;

	XOR[3].inputs[0] = 1.0f;
	XOR[3].inputs[1] = 1.0f;
	XOR[3].outputs[0] = 0.0f;

	// Add an extra point
	XOR[4].inputs[0] = 0.5f;
	XOR[4].inputs[1] = 0.5f;
	XOR[4].outputs[0] = 0.0f;
#pragma endregion

	NeuralNetwork::SimpleNetwork network(2, 10, 1, 1); // Create neural network
	GUI::SimpleScreen screen; // Create a screen

	// Training loop
	for (unsigned long i = 0; i < 1000000; i++)
	{
		// Make sure every point is trained
		for (unsigned long j = 0; j < AMOUNT_OF_TRAINING_POINTS; j++)
		{
			network.train(XOR[j].inputs, XOR[j].outputs);
		}

		if (cv::waitKey(1) == 27) // Check if escape is pressed
		{
			cv::destroyAllWindows(); // Close openCV windows
			break; // Break for loop
		}

		if (i % 100 == 0) // Update screen every 100 iterations
		{
			screen.render(network, XOR, 4);
		}
	}

	// Add text output for every training point
	for (size_t i = 0; i < AMOUNT_OF_TRAINING_POINTS; i++)
	{
		float* prediction = network.predict(XOR[i].inputs);
		printf("%.f and %.f = guess %.2f\t\tShould be %.2f\r\n", XOR[i].inputs[0], XOR[i].inputs[1], prediction[0], XOR[i].outputs[0]);
	}

	system("pause");
	return 1;
}
