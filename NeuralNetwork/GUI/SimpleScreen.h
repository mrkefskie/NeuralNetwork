#ifndef __SIMPLESCREEN_H
#define __SIMPLESCREEN_H

#define SIZE 1000

#include "../Data/DividingLines.h"
#include "../Data/Data.h"

#include "../NeuralNetwork/SimpleNetwork.h"

#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

namespace GUI
{
	typedef struct
	{
		int pixelX;
		int pixelY;
	} pixelPoint;

	class SimpleScreen
	{
	public:
		SimpleScreen();
		~SimpleScreen();

		void render(NeuralNetwork::SimpleNetwork n, Data::DATA_TYPE* d, unsigned long l);

		void setImage(int w, int h);

		cv::Mat getimage() { return _image; }

	private:
		pixelPoint convertToScreen(float x, float y);

		cv::Mat _image;
	};
}

#endif // __SIMPLESCREEN_H
