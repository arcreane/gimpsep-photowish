#include <iostream>
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int dimensionsResizing(Mat image) {

	//test image path: C:/Users/arthu/Desktop/Ecole/AppMultimedia/C++/crocodile.png

	string white = getColor("white");
	string blue = getColor("blue");
	string red = getColor("red");
	Mat modifiedImage;
	float height, width;

	gotoxy(0, 11);
	cout << white << "\nEnter the new sizes : \n";
	cout << white << "Height : ";
	cin >> height;
	cout << white << "Width : ";
	cin >> width;
	

	// Scaling the image with the new dimensions
	modifiedImage = resizeMethod(image, height, width, 0, 0);
	imshow("GimpLike Application", modifiedImage);
	waitKey(0);

	saveImage(modifiedImage);

	system("pause");

	destroyAllWindows();

	system("CLS");

	return 0;

}