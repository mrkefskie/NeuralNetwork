#pragma once

#include "Perceptron.h"
#include "Point.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

namespace GUI
{
	class CV_Window
	{
	public:
		CV_Window();
		~CV_Window();

		void render(Network::Perceptron b, Network::Point *p, size_t l);

		void setImage(int w, int h);

		cv::Mat getImage() { return image; }

	private:
		cv::Mat image;
	};
}
