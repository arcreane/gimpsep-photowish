#include <iostream>
#include "Menu.h"
#include "Header.h"
#include <opencv2/opencv.hpp>
#include "opencv2/core/utils/logger.hpp"

using namespace std;
using namespace cv;


int resizing() {

    Mat imageOrigin;
    string imagePath;

    string Set[] = { "\033[36m", "\033[0m", "\033[0m" };
    int counter = 0;
    char key;

    while (imageOrigin.empty()) {
        gotoxy(0, 3);
        cout << "\033[0m"<< "Enter the absolute path of your image : ";
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
        cout << "\033[0m" << "How would you like to resize your image ?\n";

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
                cout << "\033[0m" << "\nFactor :\n";
                factorResizing(imageOrigin);
                break;

            case 1: //dimensions resizing
                gotoxy(0, 10);
                cout << "\033[0m" << "\nDimensions :\n";
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

        Set[0] = "\033[0m";
        Set[1] = "\033[0m";
        Set[2] = "\033[0m";

        switch (counter)
        {
        case 0:
            Set[0] = "\033[36m";
            break;

        case 1:
            Set[1] = "\033[36m";
            break;

        case 2:
            Set[2] = "\033[31m";
            break;

        default:
            break;
        }

    }

	
	system("pause");

	cout << "Finished";

	return 0;

}