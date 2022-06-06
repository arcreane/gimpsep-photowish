#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

#include "Menu.h"
#include "Header.h"
#include "opencv2/core/utils/logger.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"


using namespace std;
using namespace cv;

Stitcher::Mode mode = Stitcher::PANORAMA;

// Array for pictures
vector<Mat> imgs;


int Stitching() {

    string folderPath, currentFile;
    int numberOfFiles = 0, i=0;
    
    gotoxy(0, 3);
    cout << "\033[0m" << "\nEnter the folder path : ";
    cin >> folderPath;

    string listOfFiles[100];

    while(currentFile != "&") {
        cout << "\033[0m" << "\nEnter the name of the " << i+1 << " : (enter & key to end)\n";
        cout << "\033[0m" << "Name : ";
        cin >> currentFile;
        listOfFiles[i] = folderPath + "\\" + currentFile;
        numberOfFiles = i;
        i++;
    }


    for (int i = 0; i < numberOfFiles; i++) {
        cout << "\n" << listOfFiles[i];
    }
    
    // Get all the images that need to be
    // stitched as arguments from command line
    for (int i = 1; i < numberOfFiles; ++i)
    {
        // Read the ith argument or image
        // and push into the image array
        Mat img = imread(listOfFiles[i]);
        if (img.empty())
        {
            // Exit if image is not present
            cout << "\033[0m" << "Can't read image '" << listOfFiles[i] << "\n";

            system("pause");
            destroyAllWindows();
            system("CLS");
            return -1;
        }
        imgs.push_back(img);
    }


    // Define object to store the stitched image
    Mat pano;

    // Create a Stitcher class object with mode panoroma
    Ptr<Stitcher> stitcher = Stitcher::create(mode);

    // Command to stitch all the images present in the image array
    Stitcher::Status status = stitcher->stitch(imgs, pano);

    if (status != Stitcher::OK)
    {
        // Check if images could not be stitched
        // status is OK if images are stitched successfully
        cout << "\033[0m" << "\n\nCan't stitch images\n";

        system("pause");
        destroyAllWindows();
        system("CLS");

        return -1;
    }

    // Store a new image stitched from the given
    //set of images as "result.jpg"
    //imwrite("result.jpg", pano);

    // Show the result
    imshow("GimpLike Application", pano);

    waitKey(0);
    
    saveImage(pano);

    cout << "\n";

    system("pause");

    destroyAllWindows();

    system("CLS");

	return 0;
}