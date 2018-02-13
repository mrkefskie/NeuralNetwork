#include <stdlib.h>
#include <stdio.h>

#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>

#include "NeuralNetwork\Node.h"
#include "NeuralNetwork\SimpleNetwork.h"

#include "Data\Data.h"

#include "GUI\SimpleScreen.h"

#define AMOUNT_OF_TRAINING_POINTS 10000


int main(int argc, char** argv)
{
	srand(time(NULL));

	Data::DATA_TYPE XOR[4];
	for (int i = 0; i < 4; i++)
	{
		XOR[i].input_length = 2;
		XOR[i].output_length = 1;

		XOR[i].inputs = (float*)malloc(sizeof(float) * XOR[i].input_length);
		XOR[i].outputs = (float*)malloc(sizeof(float) * XOR[i].output_length);
	}

	XOR[0].inputs[0] = 0;
	XOR[0].inputs[1] = 0;
	XOR[0].outputs[0] = 0;

	XOR[1].inputs[0] = 0;
	XOR[1].inputs[1] = 1;
	XOR[1].outputs[0] = 1;

	XOR[2].inputs[0] = 1;
	XOR[2].inputs[1] = 0;
	XOR[2].outputs[0] = 0;

	XOR[3].inputs[0] = 1;
	XOR[3].inputs[1] = 1;
	XOR[3].outputs[0] = 0;

	NeuralNetwork::SimpleNetwork network(2, 2, 1);

	GUI::SimpleScreen screen;

	float* prediction = network.predict(XOR[2].inputs);
	printf("guess = %.2f\r\n", prediction[0]);

	//network.train(XOR[0].inputs, XOR[0].outputs);

	for (unsigned long i = 0; i < 1000000; i++)
	{
		int random = rand() % (3 - 0 + 1) + 0;

		network.train(XOR[random].inputs, XOR[random].outputs);

		prediction = network.predict(XOR[0].inputs);
		printf("iteration: %d\t\tguess = %.2f\r\n", i, prediction[0]);

		if (cv::waitKey(1) == 27)
		{
			cv::destroyAllWindows();
			break;
		}
		if (i % 100 == 0)
			screen.render(network, XOR, 4);
	}

	prediction = network.predict(XOR[0].inputs);
	printf("guess = %.2f\r\n", prediction[0]);

	system("pause");
	return 1;
}
