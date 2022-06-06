#include <iostream>
#include <conio.h>
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

Mat imageOrigin, src_gray;
Mat dst, detected_edges;
int lowThreshold = -1;
const int max_lowThreshold = 100;
const int ratioValue = 3;
const int kernel_size = 3;
const char* window_name = "GimpLike Application";


static void CannyThreshold(int, void*)
{
    blur(src_gray, detected_edges, Size(3, 3));
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratioValue, kernel_size);
    dst = Scalar::all(0);
    imageOrigin.copyTo(dst, detected_edges);
    imshow(window_name, dst);
}


int cannyEdgesDetection() {

    string imagePath;
    int precision = -1;

    while (imageOrigin.empty()) {
        gotoxy(0, 3);
        cout << "\033[0m" << "Enter the absolute path of your image : ";
        cin >> imagePath;

        try
        {
            imageOrigin = imread(imagePath);

        }
        catch (const std::exception& e)
        {
            cerr << e.what();
        }

    }

    while (precision < 0 || precision > 100) {
        gotoxy(0, 5);
        cout << "                                                ";
        gotoxy(0, 5);
        cout << "\033[0m" << "Enter the precision you want [0 - 100]: ";
        cin >> precision;
    }
    lowThreshold = 100-precision;


    dst.create(imageOrigin.size(), imageOrigin.type());
    cvtColor(imageOrigin, src_gray, COLOR_BGR2GRAY);
    namedWindow(window_name, WINDOW_AUTOSIZE);
    createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
    
    CannyThreshold(0, 0);
    waitKey(0);

    saveImage(src_gray);

    system("pause");

    destroyAllWindows();

    system("CLS");

    return 0;

}