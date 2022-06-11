#include <iostream>
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int factorResizing(Mat image) {

	//test image path: C:/Users/arthu/Desktop/Ecole/AppMultimedia/C++/crocodile.png
	//C:\Users\arthu\Documents\THALES\Alternance\ARTHUR_DELERUE_head_shot.png
	string white = getColor("white");
	string blue = getColor("blue");
	string red = getColor("red");

	Mat modifiedImage;
	float resizingFactor;
	string saving, savingPath, imageName;

	gotoxy(0, 11);
	cout << white << "\nEnter the resizing factor : \n";
	cout << white  << "[factor > 1 means to upsize the image and factor < 1 means to downsize the image: \n";
	cout << white << "Factor: ";
	cin >> resizingFactor;

	// Scaling down the image 0.6 times
	modifiedImage = resizeMethod(image, resizingFactor * image.rows, resizingFactor * image.cols, resizingFactor, resizingFactor);
	imshow("GimpLike Application", modifiedImage);
	waitKey(0);

	saveImage(modifiedImage);

	system("pause");

	destroyAllWindows();

	system("CLS");


	return 0;

}