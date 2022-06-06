#include <iostream>
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int factorResizing(Mat image) {

	//test image path: C:/Users/arthu/Desktop/Ecole/AppMultimedia/C++/crocodile.png

	Mat modifiedImage;
	float resizingFactor;
	string saving, savingPath, imageName;

	gotoxy(0, 11);
	cout << "\033[0m" << "\nEnter the resizing factor : \n";
	cout << "\033[0m"  << "[factor > 1 means to upsize the image and factor < 1 means to downsize the image: \n";
	cout << "\033[0m" << "Factor: ";
	cin >> resizingFactor;

	// Scaling down the image 0.6 times
	resize(image, modifiedImage, Size(round(resizingFactor * image.cols), 
		round(resizingFactor * image.rows)), resizingFactor, resizingFactor, INTER_LINEAR);
	imshow("GimpLike Application", modifiedImage);
	waitKey(0);

	saveImage(modifiedImage);

	system("pause");

	destroyAllWindows();

	system("CLS");


	return 0;

}