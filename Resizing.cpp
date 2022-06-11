#include <iostream>
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>
#include "opencv2/core/utils/logger.hpp"

using namespace std;
using namespace cv;


int resizing() {

    string white = getColor("white");
    string blue = getColor("blue");
    string red = getColor("red");

    Mat imageOrigin;
    string imagePath;

    string Set[] = { blue, white, white };
    int counter = 0;
    char key;

    while (imageOrigin.empty()) {
        gotoxy(0, 3);
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

    //imshow("source image", imageOrigin);
    //waitKey(0);

    

    for (int i = 0; ; ) {

        gotoxy(0, 5);
        cout << white << "How would you like to resize your image ?\n";

        gotoxy(0, 6);
        cout << Set[0] << "1. With a factor";

        gotoxy(0, 7);
        cout << Set[1] << "2. With two dimensions";

        gotoxy(0, 8);
        cout << Set[2] << "3. Return";


        key = _getch();

        if (key == 72 && counter > 0) {
            counter--;
        }
        if (key == 80 && counter < 2) {
            counter++;
        }
        if (key == '\r') {
            gotoxy(0, 17);
            cout << "                           ";

            switch (counter)
            {
            case 0: //factor resizing
                gotoxy(0, 10);
                cout << white << "\nFactor :\n";
                factorResizing(imageOrigin);
                break;

            case 1: //dimensions resizing
                gotoxy(0, 10);
                cout << white << "\nDimensions :\n";
                dimensionsResizing(imageOrigin);
                break;

            case 2:
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

        switch (counter)
        {
        case 0:
            Set[0] = blue;
            break;

        case 1:
            Set[1] = blue;
            break;

        case 2:
            Set[2] = red;
            break;

        default:
            break;
        }

    }

	
	system("pause");

	cout << "Finished";

	return 0;

}