#include <iostream>
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int changeContrast(Mat image) {

    //test image path: C:/Users/arthu/Desktop/Ecole/AppMultimedia/C++/crocodile.png

    Mat modifiedImage = Mat::zeros(image.size(), image.type()); 
    string white = getColor("white");
    string blue = getColor("blue");
    string red = getColor("red");
    //asking for alpha 
    double alpha = 0;

    gotoxy(0, 11);
    cout << white << "\nEnter the brightness factor : ";
    cout << white << "[alpha > 1 means to increase the brightness and alpha < 1 means to reduce the brightness]\n";
    cout << white << "\nalpha : ";
    cin >> alpha;

    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            for (int c = 0; c < image.channels(); c++) {
                modifiedImage.at<Vec3b>(y, x)[c] =
                    saturate_cast<uchar>(alpha * image.at<Vec3b>(y, x)[c]);
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