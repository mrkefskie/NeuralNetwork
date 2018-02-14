#include <stdlib.h>
#include <stdio.h>

#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>

#include "NeuralNetwork\Node.h"
#include "NeuralNetwork\SimpleNetwork.h"

#include "Data\Data.h"

#include "GUI\SimpleScreen.h"

#define AMOUNT_OF_TRAINING_POINTS 5

int main(int argc, char** argv)
{
	srand(time(NULL));

	Data::DATA_TYPE XOR[AMOUNT_OF_TRAINING_POINTS];
	for (int i = 0; i < AMOUNT_OF_TRAINING_POINTS; i++)
	{
		XOR[i].input_length = 2;
		XOR[i].output_length = 1;

		XOR[i].inputs = (float*)malloc(sizeof(float) * XOR[i].input_length);
		XOR[i].outputs = (float*)malloc(sizeof(float) * XOR[i].output_length);
	}

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

	XOR[4].inputs[0] = 0.5f;
	XOR[4].inputs[1] = 0.5f;
	XOR[4].outputs[0] = 0.0f;


	NeuralNetwork::SimpleNetwork network(2, 10, 1, 1);

	GUI::SimpleScreen screen;


	for (unsigned long i = 0; i < 1000000; i++)
	{
		for (unsigned long j = 0; j < AMOUNT_OF_TRAINING_POINTS; j++)
		{
			network.train(XOR[j].inputs, XOR[j].outputs);
		}
		if (cv::waitKey(1) == 27)
		{
			cv::destroyAllWindows();
			break;
		}
		if (i % 100 == 0)
		{
			screen.render(network, XOR, 4);
			//system("pause");
		}
	}

	for (size_t i = 0; i < AMOUNT_OF_TRAINING_POINTS; i++)
	{
		float* prediction = network.predict(XOR[i].inputs);
		printf("%.f and %.f = guess %.2f\t\tShould be %.2f\r\n", XOR[i].inputs[0], XOR[i].inputs[1], prediction[0], XOR[i].outputs[0]);
	}

	system("pause");
	return 1;
}
