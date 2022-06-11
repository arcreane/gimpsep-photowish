#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;


//int uiGimp();
int consoleGimp();

int resizing();
int dimensionsResizing(Mat image);
int factorResizing(Mat image);
Mat resizeMethod(Mat image, float height, float width, float heightFactor, float widthFactor);

int contrast();
int changeBrightness(Mat image);
int changeContrast(Mat image);

int dilation_erosion();
int erosion(Mat image);
int dilation(Mat image);

int Stitching();
int cannyEdgesDetection();

void saveImage(Mat image);

int faceDetection();