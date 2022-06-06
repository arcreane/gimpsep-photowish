#include <iostream>
#include "Menu.h"
#include <string>
using namespace std;

void gotoxy(int x, int y) {
    printf("\033[%d;%dH%s\n", y, x, "");
}

string getColor(string color){
	if (!color.compare("red")) {
		return "\033[31m";
	}
	else if (!color.compare("blue")) {
		return "\033[36m";
	}

	return "\033[0m";
}
