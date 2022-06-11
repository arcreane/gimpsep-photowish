#include <iostream>
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void saveImage(Mat image) {

	string white = getColor("white");
	string blue = getColor("blue");
	string red = getColor("red");
	string saving, savingPath, imageName;

	cout << white << "\nWould you like to save this new image ? (Yes/No) ";
	cin >> saving;

	if (saving.compare("yes") == 0) {
		cout << white << "\nEnter the saving path : ";
		cin >> savingPath;

		cout << white << "\nEnter the image name : ";
		cin >> imageName;

		imwrite(savingPath + imageName, image);
	}

}