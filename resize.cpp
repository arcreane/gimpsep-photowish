#include <iostream>
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


Mat resizeMethod(Mat image, float height, float width, float heightFactor, float widthFactor) {
	Mat modifiedImage;
	resize(image, modifiedImage, Size(), widthFactor, heightFactor, INTER_LINEAR);
	return modifiedImage;
}