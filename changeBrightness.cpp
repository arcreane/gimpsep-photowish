#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int changeBrightness(Mat image) {


    //test image path: C:/Users/arthu/Desktop/Ecole/AppMultimedia/C++/crocodile.png

    Mat modifiedImage = Mat::zeros(image.size(), CV_8UC3);;
    string white = getColor("white");
    string blue = getColor("blue");
    string red = getColor("red");
    //asking for alpha 
    float alpha = 0;

    gotoxy(0, 11);
    cout << white << "\nEnter the brightness factor : ";
    cout << white << "[alpha > 1 means to increase the brightness and alpha < 1 means to reduce the brightness]\n";
    cout << white << "\nalpha : ";
    cin >> alpha;

    for (int y = 0; y < image.cols; y++) {
        for (int x = 0; x < image.rows; x++) {
            for (int c = 0; c < 2; c++) {
                modifiedImage.at<Vec3b>(y, x)[c] =
                    saturate_cast<uchar>(alpha * (image.at<Vec3b>(y, x)[c]));
            }
        }
    }

    imshow("GimpLike Application", modifiedImage);
    waitKey(0);

    saveImage(modifiedImage);

    system("pause");

    destroyAllWindows();

    system("CLS");

	return 0;
}