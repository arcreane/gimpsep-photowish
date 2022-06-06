#include <iostream>
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>
#include "opencv2/core/utils/logger.hpp"

using namespace std;
using namespace cv;

Mat dilatedImage, imageSrc;
int dilation_type = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;

void dilate(int, void*) {

	if (dilation_elem == 0) { dilation_type = MORPH_RECT; }
	else if (dilation_elem == 1) { dilation_type = MORPH_CROSS; }
	else if (dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }


	Mat element = getStructuringElement(dilation_type,
		Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		Point(dilation_size, dilation_size));
	dilate(imageSrc, dilatedImage, element);
	imshow("GimpLike Application", dilatedImage);

}

int dilation(Mat image) {

	//test image path: C:/Users/arthu/Desktop/Ecole/AppMultimedia/C++/crocodile.png

	string white = getColor("white");
	string blue = getColor("blue");
	string red = getColor("red");
	imageSrc = image;

	cout << white << "\nWhat is the dilation element ? (between 0 and 2)\n";
	cout << white << "[ 1: Rectangle | 2: Cross | 3: Ellipse ]\n";
	cout << white << "Dilation element : ";
	cin >> dilation_elem;

	cout << white << "\nWhat is the dilation size ? (between 0 and 21)\n";
	cout << white << "Dilation size : ";
	cin >> dilation_size;

	namedWindow("GimpLike Application", WINDOW_AUTOSIZE);
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "GimpLike Application",
		&dilation_elem, max_elem,
		dilate);

	createTrackbar("Kernel size:\n 2n +1", "GimpLike Application",
		&dilation_size, max_kernel_size,
		dilate);
	
	dilate(0, 0);
	waitKey(0);

	saveImage(dilatedImage);

	system("pause");

	destroyAllWindows();

	system("CLS");

	return 0;
}