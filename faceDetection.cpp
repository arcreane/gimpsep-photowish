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
    
    string Set[] = { "\033[36m", "\033[0m", "\033[0m"};
    int counter = 0;
    char key;

    for (int i = 0; ; ) {
        
        gotoxy(0, 2);
        cout << "\033[0m" << "\nHow would you like to use Face Detection \n";
        
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

        Set[0] = "\033[0m";
        Set[1] = "\033[0m";
        Set[2] = "\033[0m";

        if (counter == 0) {
            Set[0] = "\033[36m";
        }
        if (counter == 1) {
            Set[1] = "\033[36m";
        }
        if (counter == 2) {
            Set[2] = "\033[31m";
        }

    }

    return 0;
}

int videoCaptureDetection() {
    
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

        /*
        double aspect_ratio = (double)r.width / r.height;
        if (0.75 < aspect_ratio && aspect_ratio < 1.3)
        {
            center.x = cvRound((r.x + r.width * 0.5) * scale);
            center.y = cvRound((r.y + r.height * 0.5) * scale);
            radius = cvRound((r.width + r.height) * 0.25 * scale);
            circle(img, center, radius, color, 3, 8, 0);
        }
        else
        */
        rectangle(img, cvPoint(cvRound(r.x * scale), cvRound(r.y * scale)),
                cvPoint(cvRound((r.x + r.width - 1) * scale),
                    cvRound((r.y + r.height - 1) * scale)), color, 2, 8, 0);

        smallImgROI = smallImg(r);

        
    }

    // Show Processed Image with detected faces
    imshow("Face Detection", img);
}

int fileCaptureDetection() {

    //// 1. Load Haar feature-based cascade classifiers 
    cv::CascadeClassifier faceCascade{ "./haarcascade_frontalface_default.xml" };
    cv::CascadeClassifier eyesCascade{ "./haarcascade_eye_tree_eyeglasses.xml" };

    //// 2. Read image and convert to grayscale
    cv::Mat inputImage{ cv::imread("C:/Users/arthu/Desktop/Ecole/AppMultimedia/C++/gimpLikeApplication/chabal.jpg", cv::IMREAD_COLOR) };
    cv::Mat inputImageGray;
    cvtColor(inputImage, inputImageGray, cv::COLOR_BGR2GRAY);

    //// 3. Find areas with faces using Haar cascade classifier
    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(inputImageGray, faces);
    for (size_t i = 0; i < faces.size(); i++) {
        cv::Point faceCenter{ faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2 };
        cv::Size halfFace{ faces[i].width / 2, faces[i].height / 2 };
        // input, center, axes, angle=0, startAngle=0, endAngle=360, color, thickness=2
        cv::ellipse(inputImage, faceCenter, halfFace, 0, 0, 360, cv::Scalar(255, 0, 255), 2);
        // Get the region of interest : face rectangle sub-image in gray and colored
        cv::Mat faceROIGray{ inputImageGray(faces[i]) };

        //// 4. Find areas with eyes in faces using Haar cascade classifier
        std::vector<cv::Rect> eyes;
        eyesCascade.detectMultiScale(faceROIGray, eyes);
        for (size_t j = 0; j < eyes.size(); j++) {
            cv::Point eyeCenter{ faces[i].x + eyes[j].x + eyes[j].width / 2,
                                  faces[i].y + eyes[j].y + eyes[j].height / 2 };
            int radius{ cvRound((eyes[j].width + eyes[j].height) * 0.25) };
            // input, center, radius, color, thickness=2
            cv::circle(inputImage, eyeCenter, radius, cv::Scalar(255, 0, 0), 2);
        }
    }

    //// 5. Show the output image
    cv::imshow("Face Detection - OpenCV", inputImage);
    cv::waitKey();  // Wait Esc key to end program

    return 0;
}
