#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>

#include "Perceptron.h"
#include "Point.h"

/**
 * @brief The amount of points to train the network with
 * 
 */
#define AMOUNT_OF_POINTS 100
/**
 * @brief The amount of stops in the training
 * 
 */
#define AMOUNT_OF_STOPS 5

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
	srand(time(NULL));
	Perceptron brain;

	Point points[AMOUNT_OF_POINTS];

	drawLabels(points);
	system("pause");

	for (size_t i = 0; i < AMOUNT_OF_POINTS; i++)
	{
		float inputs[AMOUNT_OF_INPUTS] = { points[i].x, points[i].y, points[i].bias };
		brain.train(inputs, points[i].label);

		if ((i % (AMOUNT_OF_POINTS / AMOUNT_OF_STOPS)) == 0)
		{
			counter = 0;
			drawScreen(brain, points, AMOUNT_OF_POINTS);
			printf("\r\nInterval[%d]\t=> Correct guesses: %d\r\n", i, counter);
			system("pause");
		}
	}

	/*counter = 0;
	drawScreen(brain, points);
	printf("\r\nInterval[%d]\t=> Correct guesses: %d\r\n", AMOUNT_OF_POINTS, counter);
	*/
	Point test[50];

	counter = 0;
	drawScreen(brain, test, 50);
	printf("\r\nTestSet: %d correct\r\n", counter);


	system("PAUSE");
	return 1;
}