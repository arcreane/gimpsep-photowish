// Include required header files from OpenCV directory
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>
#include "opencv2/core/utils/logger.hpp"
#include "opencv2/core/types_c.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/highgui.hpp"
#include <iostream>

#include <sstream>
#include <vector>
#include <string>
#include "FaceDetector.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int videoCaptureDetection();
int fileCaptureDetection();
// Function for Face Detection
void detectAndDraw(Mat& img, CascadeClassifier& cascade, double scale);
string cascadeName;



int faceDetection()
{
    string white = getColor("white");
    string blue = getColor("blue");
    string red = getColor("red");

    string Set[] = { blue, white, white };
    int counter = 0;
    char key;

    for (int i = 0; ; ) {
        
        gotoxy(0, 2);
        cout << white << "\nHow would you like to use Face Detection \n";
        
        gotoxy(0, 5);
        cout << Set[0] << "1. With the camera";

        gotoxy(0, 6);
        cout << Set[1] << "2. From a saved file";

        gotoxy(0, 7);
        cout << Set[2] << "3. Return";


        key = _getch();

        if (key == 72 && (counter > 0)) {
            counter --;
        }
        if (key == 80 && (counter < 2)) {
            counter ++;
        }
        if (key == '\r') {
            if (counter == 0) {
                cout << flush;
                system("CLS");
                videoCaptureDetection();
            }
            if (counter == 1) {
                cout << flush;
                system("CLS");
                fileCaptureDetection();
            }
            if (counter == 2) {
                gotoxy(0, 0);
                system("CLS");
                destroyAllWindows();
                return 0;
            }
        }

        Set[0] = white;
        Set[1] = white;
        Set[2] = white;

        if (counter == 0) {
            Set[0] = blue;
        }
        if (counter == 1) {
            Set[1] = blue;
        }
        if (counter == 2) {
            Set[2] = red;
        }

    }

    
    system("pause");

    destroyAllWindows();

    system("CLS");

    return 0;
}


int videoCaptureDetection() {
    string white = getColor("white");
    gotoxy(0, 2);
    cout << white << "\nVideo face detection : \n";
    
    cv::VideoCapture video_capture;
    if (!video_capture.open(0)) {
        return 0;
    }
    // PreDefined trained XML classifiers with facial features
    CascadeClassifier cascade;
    double scale = 1;
    // Change path before execution 
    cascade.load("./haarcascade_frontalcatface_default.xml");

    cv::Mat frame;
    while (true) {
        
        video_capture >> frame;
        if (frame.empty())
            break;
        Mat frame1 = frame.clone();
        //imshow("Video", frame);
        detectAndDraw(frame1, cascade, scale);
        char c = (char)waitKey(10);

        // Press q to exit from window
        if (c == 27 || c == 'q' || c == 'Q')
            break;
    }

    destroyAllWindows();
    video_capture.release();
    
    return 0;

}

void detectAndDraw(Mat& img, CascadeClassifier& cascade,
    double scale)
{
    vector<Rect> faces, faces2;
    Mat gray, smallImg;

    cvtColor(img, gray, COLOR_BGR2GRAY); // Convert to Gray Scale
    double fx = 1 / scale;

    // Resize the Grayscale Image 
    resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
    equalizeHist(smallImg, smallImg);

    // Detect faces of different sizes using cascade classifier 
    cascade.detectMultiScale(smallImg, faces, 1.1,
        2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    // Draw rect around the faces
    for (size_t i = 0; i < faces.size(); i++)
    {
        Rect r = faces[i];
        Mat smallImgROI;
        vector<Rect> nestedObjects;
        Point center;
        Scalar color = Scalar(255, 0, 0); // Color for Drawing tool
        int radius;

        rectangle(img, cvPoint(cvRound(r.x * scale), cvRound(r.y * scale)),
                cvPoint(cvRound((r.x + r.width - 1) * scale),
                    cvRound((r.y + r.height - 1) * scale)), color, 2, 8, 0);

        smallImgROI = smallImg(r);

        
    }

    // Show Processed Image with detected faces
    imshow("Face Detection", img);
}

int fileCaptureDetection() {

    string white = getColor("white");

    gotoxy(0, 0);
    cout << white << "\nFile face detection : \n";

    Mat imageOrigin;//Declaring a matrix to load image with human faces//
    String imagePath;

    while (imageOrigin.empty()) {
        gotoxy(0, 4);
        cout << white << "Enter the absolute path of your image : ";
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

    imageOrigin = imread(imagePath);//loading an image that contains human face in it//
    namedWindow("Face Detection");//Declaring a window to show the result//
    
    string trained_classifier_location = "C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
    CascadeClassifier faceDetector;

    faceDetector.load(trained_classifier_location);
    vector<Rect>faces;
    vector<Rect>boundary;


    faceDetector.detectMultiScale(imageOrigin, faces, 1.1, 4, CASCADE_SCALE_IMAGE, Size(20, 20));
    for (size_t i = 0; i < faces.size(); i++) { 
        Mat faceROI = imageOrigin(faces[i]);//Storing the face in a matrix//
        int x = faces[i].x;
        int y = faces[i].y;
        int h = y + faces[i].height;//Calculating the height of the rectangle//
        int w = x + faces[i].width;//Calculating the width of the rectangle//
        rectangle(imageOrigin, Point(x, y), Point(w, h), Scalar(255, 0, 255), 2, 8, 0);//Drawing a rectangle using around the faces//
    }
        
    Mat imageCopy = imageOrigin;
    float resizingFactor = 1;

    while (imageCopy.cols * resizingFactor > 500 && imageCopy.rows * resizingFactor > 500) {
        resizingFactor -= 0.1;
    }

    imageCopy = resizeMethod(imageCopy,resizingFactor * imageCopy.rows, resizingFactor * imageCopy.cols, resizingFactor, resizingFactor);
    imshow("Face Detection", imageCopy);//Showing the detected face//
   

    waitKey(0);//To wait for keystroke to terminate the program//

    saveImage(imageOrigin);

    system("pause");

    destroyAllWindows();

    system("CLS");

    return 0;
}
