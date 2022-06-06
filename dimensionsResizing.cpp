#include <iostream>
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int dimensionsResizing(Mat image) {

	//test image path: C:/Users/arthu/Desktop/Ecole/AppMultimedia/C++/crocodile.png

	Mat modifiedImage;
	float height, width;
	string saving, savingPath, imageName;

	gotoxy(0, 11);
	cout << "\033[0m" << "\nEnter the new sizes : \n";
	cout << "\033[0m" << "Height : ";
	cin >> height;
	cout << "\033[0m" << "Width : ";
	cin >> width;
	

	// Scaling the image with the new dimensions
	resize(image, modifiedImage, Size(round(height),
		round(width)), height, width, INTER_LINEAR);
	imshow("GimpLike Application", modifiedImage);
	waitKey(0);

	saveImage(modifiedImage);

	system("pause");

	destroyAllWindows();

	system("CLS");

	return 0;

}