#include <stdlib.h>
#include <stdio.h>

#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>

#include "NeuralNetwork\Node.h"

#include "GUI\SimpleScreen.h"

#include "Matrix\Matrix.h"

#define AMOUNT_OF_TRAINING_POINTS 10000

int main(int argc, char** argv)
{
	srand(time(NULL));
	Utilities::Matrix m1(2, 3);
	m1.randomize();
	m1.printToCLI();
	m1.add(2);
	m1.printToCLI();

	Utilities::Matrix m2(2, 3);
	m2.randomize();
	m2.printToCLI();

	Utilities::Matrix m3;
	m3 = Utilities::Matrix::add(m1, m2);

	m1.add(m2);
	m1.printToCLI();

	m3.printToCLI();




	NeuralNetwork::Node n(2, NeuralNetwork::ACTIVATION_TYPE::SIGN, 0.000001);
	Data::Point* p = (Data::Point*)malloc(sizeof(Data::Point) * AMOUNT_OF_TRAINING_POINTS);

	for (unsigned long i = 0; i < AMOUNT_OF_TRAINING_POINTS; i++)
	{
		p[i] = Data::Point(Data::STRAIGHT);
	}

	GUI::SimpleScreen screen;

	uint32_t counter = 0;

	while (1)
	{
		for (size_t i = 0; i < AMOUNT_OF_TRAINING_POINTS; i++)
		{
			float inputs[AMOUNT_OF_TRAINING_POINTS] = { p[i].getX(), p[i].getY(), p[i].getBias() };
			n.train(inputs, p[i].getLabel());
		}

		float a = -(n.getWeights(0) / n.getWeights(1));
		float b = -(n.getWeights(2) / n.getWeights(1));


		printf("Iteration: %d (%.5fx+%.5f)\r\n", counter, a, b);

		if (cv::waitKey(1) == 27)
		{
			cv::destroyAllWindows();
			break;
		}
		screen.render(n, p, AMOUNT_OF_TRAINING_POINTS);

		counter++;
	}

 	system("pause");
	return 1;
}