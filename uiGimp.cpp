#include <iostream>
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>
#include "opencv2/core/utils/logger.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/highgui.hpp"

#define CVUI_IMPLEMENTATION
#include "cvui.h"

using namespace std;
using namespace cv;


#define WINDOW_NAME "GimpLike Application"
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 1024


int uiGimp() {

    utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);;

	Mat imageOrigin;
	string imagePath;
	float resizeFactor = 1;
	int low_threshold = 50, high_threshold = 150;
	cout << "\033[0m" << "Enter the absolute path of your image : ";
	cin >> imagePath;
	imageOrigin = imread(imagePath);
	
	if (imageOrigin.size().height > WINDOW_HEIGHT || imageOrigin.size().width > WINDOW_WIDTH) {
		int imgHeight = imageOrigin.size().height, imgWidth = imageOrigin.size().width;
		while (imgWidth > WINDOW_WIDTH && imgHeight > WINDOW_HEIGHT) {
			float newHeight = resizeFactor * imgHeight, newWidth = resizeFactor * imgWidth;
			if (newWidth < WINDOW_WIDTH && newHeight < WINDOW_HEIGHT) {
				imgHeight = (int)newHeight;
				imgWidth = (int)newWidth;
				break;
			}
			else
			{
				resizeFactor -= 0.1;
			}
			;
		}

		resize(imageOrigin, imageOrigin, Size(round(resizeFactor * imageOrigin.cols), round(resizeFactor * imageOrigin.rows)), resizeFactor, resizeFactor, INTER_LINEAR);

		//cout << imageOrigin.size().width << "|" << imageOrigin.size().height;

	}
	
	cv::Mat frame = cv::Mat(WINDOW_HEIGHT, WINDOW_WIDTH, CV_8UC3);
	bool cannyEdge = false, resizing = false, dilation_erosion = false, lighten_darken = false, panorama = false;

	// Init a OpenCV window and tell cvui to use it.
	cv::namedWindow(WINDOW_NAME);
	cvui::init(WINDOW_NAME);

	while (true) {
		// Fill the frame with a nice color
		//frame = cv::Scalar(195, 195, 195);

		cvui::image(frame, WINDOW_WIDTH-imageOrigin.size().width, 0, imageOrigin);

		// Render the settings window to house the UI
		cvui::window(frame, 0, 0, 180, 180, "Settings");

		// Checkbox to enable/disable the use of Dilation / Erosion
		cvui::checkbox(frame, 15, 30, "Dilation / Erosion", &dilation_erosion);
		// Checkbox to enable/disable the use of  Resizing
		cvui::checkbox(frame, 15, 60, "Resizing", &resizing);
		// Checkbox to enable/disable the use of  Lighten / Darken
		cvui::checkbox(frame, 15, 90, "Lighten / Darken", &lighten_darken);
		// Checkbox to enable/disable the use of Panorama
		cvui::checkbox(frame, 15, 120, "Panorama", &panorama);
		// Checkbox to enable/disable the use of Canny edge
		cvui::checkbox(frame, 15, 150, "Canny Edge", &cannyEdge);

		if (cannyEdge) {
			cvui::window(frame, 0, 210, 180, 180, "Canny Edge");
			cvui::trackbar(frame, 5, 260, 165, &low_threshold, 5, 150);
			cvui::trackbar(frame, 5, 330, 165, &high_threshold, 80, 300);
		}



		// Show how many times the button has been clicked.
		// Text at position (250, 90), sized 0.4, in red.
		//cvui::printf(frame, 250, 90, 0.4, 0xff0000, "Button click count: %d", count);

		// Update cvui internal stuff
		cvui::update();

		// Show everything on the screen
		cv::imshow(WINDOW_NAME, frame);

		// Check if ESC key was pressed
		if (cv::waitKey(20) == 27) {
			destroyAllWindows();
			return -1;
		}
	}


    return 0;
}