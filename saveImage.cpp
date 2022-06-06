#include <iostream>
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void saveImage(Mat image) {

	string saving, savingPath, imageName;

	cout << "\033[0m" << "\nWould you like to save this new image ? (Yes/No) ";
	cin >> saving;

	if (saving.compare("yes") == 0) {
		cout << "\033[0m" << "\nEnter the saving path : ";
		cin >> savingPath;

		cout << "\033[0m" << "\nEnter the image name : ";
		cin >> imageName;

		imwrite(savingPath + imageName, image);
	}

}