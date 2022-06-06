// gimpLikeApplication.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Header.h"
#include "Menu.h"
using namespace std;



int main()
{
    
    //"\033[31m" :red
    //"\033[36m" : cyan

    string white = getColor("white");
    string blue = getColor("blue");
    string red = getColor("red");
    string Set[] = { blue, white, white };
    int counter = 0;
    char key;

    string text = Set[0]+"test";
    //printf("\033[%d;%dH%s\n", 1, 3, text);

    for (int i = 0; ; ) {
        
        gotoxy(0, 0);
        cout << white << "\nWelcome into the GimpLike application !\n";
        
        gotoxy(0, 2);
        cout << white  << "\nHow would you like to use this tool ?";

        gotoxy(0, 5);
        cout << Set[0] << "1. With the console";

        gotoxy(0, 6);
        cout << Set[1] << "2. With the UI";

        gotoxy(0, 7);
        cout << Set[2] << "3. Quit";


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
                consoleGimp();
            }
            if (counter == 1) {
                cout << flush;
                system("CLS");
                //uiGimp();
            }
            if (counter == 2) {
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


    return 0;
}





