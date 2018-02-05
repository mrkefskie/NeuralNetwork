#include "SimpleScreen.h"

GUI::SimpleScreen::SimpleScreen()
{
}

GUI::SimpleScreen::~SimpleScreen()
{
}

void GUI::SimpleScreen::render(NeuralNetwork::Node n, Data::Point *dp, unsigned long l)
{
	// Clear the image
	setImage(SIZE, SIZE);

	Data::LINE_TYPE lineType = dp[0].getLineType();

	float x0 = -1.f;
	float x1 = 1.f;
	float y0, y1;

	pixelPoint p0, p1;

	if (lineType != Data::STRAIGHT)
	{
		for (unsigned long i = 0; i < SIZE; i++)
		{
			x0 = ((float)i / (SIZE / 2.f)) - 1.f;
			x1 = ((float)(i + 1.f) / (SIZE / 2.f)) - 1.f;
			switch (lineType)
			{
			case Data::PARABOLIC:
				y0 = Data::DivindingLines::Parabolic(x0);
				y1 = Data::DivindingLines::Parabolic(x1);
				break;
			default:
				break;
			}


			p0 = convertToScreen(x0, y0);
			p1 = convertToScreen(x1, y1);

			cv::line(_image, cv::Point(p0.pixelX, p0.pixelY), cv::Point(p1.pixelX, p1.pixelY), cv::Scalar(255, 0, 0));
		}
	}
	else
	{
		x0 = -1.f;
		x1 = 1.f;

		y0 = Data::DivindingLines::straightLine(x0);
		y1 = Data::DivindingLines::straightLine(x1);

		p0 = convertToScreen(x0, y0);
		p1 = convertToScreen(x1, y1);

		cv::line(_image, cv::Point(p0.pixelX, p0.pixelY), cv::Point(p1.pixelX, p1.pixelY), cv::Scalar(255, 0, 0));
	}

	// Draw the points
	for (unsigned long i = 0; i < l; i++)
	{
		pixelPoint point = convertToScreen(dp[i].getX(), dp[i].getY());
		cv::circle(_image, cv::Point(point.pixelX, point.pixelY), 3, cv::Scalar(255, 255, 255));

		float inputs[3] = { dp[i].getX(),dp[i].getY(),dp[i].getBias() };

		if (n.guess(inputs) == dp[i].getLabel())
		{
			cv::circle(_image, cv::Point(point.pixelX, point.pixelY), 2, cv::Scalar(0, 255, 0), 1);
		}
		else
		{
			cv::circle(_image, cv::Point(point.pixelX, point.pixelY), 2, cv::Scalar(0, 0, 255), 1);
		}
	}
	
	if (lineType != Data::STRAIGHT)
	{
	}
	else
	{
		x0 = -1.f;
		x1 = 1.f;

		y0 = -(n.getWeights(0) / n.getWeights(1))*x0 - (n.getWeights(2) / n.getWeights(1));
		y1 = -(n.getWeights(0) / n.getWeights(1))*x1 - (n.getWeights(2) / n.getWeights(1));

		p0 = convertToScreen(x0, y0);
		p1 = convertToScreen(x1, y1);

		cv::line(_image, cv::Point(p0.pixelX, p0.pixelY), cv::Point(p1.pixelX, p1.pixelY), cv::Scalar(255, 255, 0));
	}
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
