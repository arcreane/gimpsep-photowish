#include <iostream>
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>
#include "opencv2/core/utils/logger.hpp"

using namespace std;
using namespace cv;

Mat erodedImage, srcImage;
int erosion_type = 0;
int erosion_elem = 0;
int erosion_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;

void erodeImage(int, void*) {

	if (erosion_elem == 0) { erosion_type = MORPH_RECT; }
	else if (erosion_elem == 1) { erosion_type = MORPH_CROSS; }
	else if (erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }


	Mat element = getStructuringElement(erosion_type,
		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		Point(erosion_size, erosion_size));
	erode(srcImage, erodedImage, element);

	imshow("GimpLike Application", erodedImage);

}

int erosion(Mat image) {

	//test image path: C:/Users/arthu/Desktop/Ecole/AppMultimedia/C++/crocodile.png


	srcImage = image;

	cout << "\033[0m" << "\nWhat is the erosion element ? (between 0 and 2)\n";
	cout << "\033[0m" << "[ 1: Rectangle | 2: Cross | 3: Ellipse ]\n";
	cout << "\033[0m"  << "Erosion element : ";
	cin >> erosion_elem;

	cout << "\033[0m"  << "\nWhat is the erosion size ? (between 0 and 21)\n";
	cout << "\033[0m" << "Erosion size : ";
	cin >> erosion_size;

	namedWindow("GimpLike Application", WINDOW_AUTOSIZE);
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "GimpLike Application",
		&erosion_elem, max_elem,
		erodeImage);

	createTrackbar("Kernel size:\n 2n +1", "GimpLike Application",
		&erosion_size, max_kernel_size,
		erodeImage);

	erodeImage(0, 0);
	waitKey(0);

	saveImage(erodedImage);

	system("pause");

	destroyAllWindows();

	system("CLS");

	return 0;
}