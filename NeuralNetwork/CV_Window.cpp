#include "CV_Window.h"

#include "Defines.h"


GUI::CV_Window::CV_Window()
{
}


GUI::CV_Window::~CV_Window()
{
}

void GUI::CV_Window::render(Network::Perceptron b, Network::Point * p, size_t l)
{
	// Clear the image
	setImage(SIZE, SIZE);

	float x0 = -1;
	float x1 = 1;
	float y0 = p[0].line(x0);
	float y1 = p[0].line(x1);

	Network::Point p0(x0, y0);
	Network::Point p1(x1, y1);

	cv::line(image, cv::Point(p0.pixelX(), p0.pixelY()), cv::Point(p1.pixelX(), p1.pixelY()), cv::Scalar(255, 0, 0));

	for (size_t i = 0; i < l; i++)
	{
		cv::circle(image, cv::Point(p[i].pixelX(), p[i].pixelY()), 3, cv::Scalar(255, 255, 255));

		float inputs[3] = { p[i].x,p[i].y,p[i].bias };

		if (b.guess(inputs) == p[i].label)
		{
			cv::circle(image, cv::Point(p[i].pixelX(), p[i].pixelY()), 2, cv::Scalar(0, 255, 0), 1);
		}
		else
		{
			cv::circle(image, cv::Point(p[i].pixelX(), p[i].pixelY()), 2, cv::Scalar(0, 0, 255), 1);
		}
	}


	y0 = -(b.weights[0] / b.weights[1])*x0 - (b.weights[2] / b.weights[1]);
	y1 = -(b.weights[0] / b.weights[1])*x1 - (b.weights[2] / b.weights[1]);

	p0 = Network::Point(x0, y0);
	p1 = Network::Point(x1, y1);

	cv::line(image, cv::Point(p0.pixelX(), p0.pixelY()), cv::Point(p1.pixelX(), p1.pixelY()), cv::Scalar(255, 255, 0));

	cv::namedWindow("Output");
	cv::imshow("Output", image);
	cv::moveWindow("Output", 800, 0);
}

void GUI::CV_Window::setImage(int w, int h)
{
	image = cv::Mat(w, h, CV_8UC3);
}
