#include "SimpleScreen.h"

GUI::SimpleScreen::SimpleScreen()
{
}

GUI::SimpleScreen::~SimpleScreen()
{
}

void GUI::SimpleScreen::render(NeuralNetwork::SimpleNetwork n, Data::DATA_TYPE * d, unsigned long l)
{
	// Clear the image
	setImage(SIZE, SIZE);

	int scale = 10;

	int cols = (SIZE / scale); // The amount of columns
	int rows = (SIZE / scale); // The amount of rows

	// Loop through every column and row
	for (int i = 0; i <= cols; i++)
	{
		for (int j = 0; j <= rows; j++)
		{
			// Get the inputs (between 0 and 1)
			float x1 = (float)i / (float)cols;
			float x2 = (float)j / (float)cols;

			// Store them in a data object
			Data::DATA_TYPE data;
			data.input_length = 2;
			data.inputs = (float*)malloc(sizeof(float) * data.input_length);

			data.inputs[0] = x1;
			data.inputs[1] = x2;

			// Predict with the network
			float* y = n.predict(data.inputs);

			// Get the first value from the prediction and make a square with a color corresponding to the output
			int c = y[0] * 255;
			cv::rectangle(_image, cv::Rect(i*scale, j*scale, scale, scale), cv::Scalar(c,c,c), CV_FILLED);
			
			// Cleanup
			free(data.inputs);
			free(y);
		}
	}

	// Show the image
	cv::namedWindow("Output");
	cv::imshow("Output", _image);
}

void GUI::SimpleScreen::setImage(int w, int h)
{
	_image = cv::Mat(w, h, CV_8UC3, cv::Scalar(100, 100, 100));
}

GUI::pixelPoint GUI::SimpleScreen::convertToScreen(float x, float y)
{
	pixelPoint output;
	output.pixelX = (x * (SIZE / 2)) + (SIZE / 2);
	output.pixelY = -(y * (SIZE / 2)) + (SIZE / 2);

	return output;
}
