#include <iostream>
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>
#include "opencv2/core/utils/logger.hpp"

using namespace std;
using namespace cv;

int consoleGimp() {

    utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

    string white = getColor("white");
    string blue = getColor("blue");
    string red = getColor("red");
    string Set[] = { blue, white, white, white, white, white, white };
    int counter = 0;
    char key;

    for (int i = 0; ; ) {

        gotoxy(0, 0);
        cout << white << "\nWhat do you need to do ?\n";

        gotoxy(0, 3);
        cout << Set[0] << "1. Dilatation / Erosion";

        gotoxy(0, 4);
        cout << Set[1] << "2. Resizing";

        gotoxy(0, 5);
        cout << Set[2] << "3. Lighten / Darken";

        gotoxy(0, 6);
        cout << Set[3] << "4. Panorama / Stiching";

        gotoxy(0, 7);
        cout << Set[4] << "5. Canny Edge Detection";

        gotoxy(0, 8);
        cout << Set[5] << "6. Face Detection";

        gotoxy(0, 9);
        cout << Set[6] << "7. Return";


        key = _getch();

        if (key == 72 && counter > 0) {
            counter--;
        }
        if (key == 80 && counter < 6) {
            counter++;
        }
        if (key == '\r') {

            switch (counter)
            {
            case 0: //dilatation / erosion
                gotoxy(0, 0);
                system("CLS");
                cout << "Dilatation - Erosion :";
                dilation_erosion();
                break;

            case 1: //resizing
                gotoxy(0, 0);
                system("CLS");
                cout << "Resizing :";
                resizing();
                break;

            case 2: //lighten / darken
                gotoxy(0, 0);
                system("CLS");
                cout << "Lighten - Darken :";
                contrast();
                break;

            case 3: // panorama
                gotoxy(0, 0);
                system("CLS");
                cout << "Panorama - Stiching :";
                Stitching();
                break;

            case 4: // canny edge detection
                gotoxy(0, 0);
                system("CLS");
                cout << "Canny Edge Detection :";
                cannyEdgesDetection();
                break;

            case 5:
                gotoxy(0, 0);
                system("CLS");
                cout << "Face Detection :";
                faceDetection();
                break;

            case 6:
                gotoxy(0, 0);
                system("CLS");
                destroyAllWindows();
                return 0;
                break;

            default:
                break;
            }


        }

        Set[0] = white;
        Set[1] = white;
        Set[2] = white;
        Set[3] = white;
        Set[4] = white;
        Set[5] = white;
        Set[6] = white;

        switch (counter)
        {
        case 0:
            Set[0] = blue;
            break;

        case 1:
            Set[1] = blue;
            break;

        case 2:
            Set[2] = blue;
            break;

        case 3:
            Set[3] = blue;
            break;

        case 4:
            Set[4] = blue;
            break;

        case 5:
            Set[5] = blue;
            break;

        case 6:
            Set[6] = red;
            break;

        default:
            break;
        }

    }


    return 0;
}