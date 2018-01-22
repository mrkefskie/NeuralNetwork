#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>

#include "Defines.h"

#include "Perceptron.h"
#include "Point.h"


#ifdef OPENCV
#include "CV_Window.h"
#include <opencv2\core.hpp>

using namespace GUI;
#endif


using namespace Network;

/**
 * @brief A counter to track how many hits we have
 * 
 */
int counter = 0;

/**
 * @brief A simple function to draw the labels to a console screen
 * 
 * @param points The points to draw
 */
void drawLabels(Point points[AMOUNT_OF_POINTS])
{
	system("CLS");
	for (size_t i = 0; i < AMOUNT_OF_POINTS; i++)
	{
		Point p = points[i];

		COORD pos = { p.pixelX(), p.pixelY() };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

		if (p.label == -1)
			printf("#");
		else
			printf("*");
	}

	COORD pos = { SIZE,SIZE };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/**
 * @brief A function to draw the guessed label on the screen
 * 
 * @param brain The network to use
 * @param points A pointer to the points to guess
 * @param l The amount of points in the pointer
 */
void drawScreen(Perceptron brain, Point* points, size_t l)
{
	system("CLS");

	Point p;

	for (size_t i = 0; i < l; i++)
	{
		p = points[i];

		float input[AMOUNT_OF_INPUTS] = { p.x, p.y, p.bias };
		int guess = brain.guess(input);

		COORD pos = { p.pixelX(), p.pixelY() };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

		if (guess == p.label)
		{
			counter++;
			if (p.label == -1)
				printf("O");
			else
				printf("o");
		}
		else
		{
			if (p.label == -1)
				printf("X");
			else
				printf("x");
		}
	}

	COORD pos = { SIZE ,SIZE };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("\r\n");
}

int main(int argc, char** argv)
{
	CV_Window window;

	window.setImage(SIZE, SIZE);

	srand(time(NULL));
	Perceptron brain;

	Point points[AMOUNT_OF_POINTS];

	//drawLabels(points);
	//system("pause");
	
	counter = 0;

	while (1)
	{
		for (size_t i = 0; i < AMOUNT_OF_POINTS; i++)
		{
			float inputs[AMOUNT_OF_INPUTS] = { points[i].x, points[i].y, points[i].bias };
			brain.train(inputs, points[i].label);
		}

		float a = -(brain.weights[0] / brain.weights[1]);
		float b = -(brain.weights[2] / brain.weights[1]);


		printf("Iteration: %d (%.5fx+%.5f)\r\n", counter, a, b);

		window.render(brain, points, AMOUNT_OF_POINTS);
		if (cv::waitKey(1) == 27)
		{
			cv::destroyAllWindows();
			break;
		}
		//Sleep(100);

		counter++;
	}

	float a = -(brain.weights[0] / brain.weights[1]);
	float b = -(brain.weights[2] / brain.weights[1]);
	printf("Final funcion: %.5fx+%.5f\r\n", a, b);

	Point testP[AMOUNT_OF_TEST_POINTS];
	window.render(brain, testP, AMOUNT_OF_TEST_POINTS);
	if (cv::waitKey(0) == 27)
	{
		cv::destroyAllWindows();
	}

	system("PAUSE");
	return 1;
}

