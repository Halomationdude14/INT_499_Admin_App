
/*
INT 499 Capstone for Information Technology
Interactive Assignment
Date: 2024-04-22
Author: Paul Oram
NOTE: This is a modified version of the original code that has been reworked to integrate into the final project (MySQL DB).
*/

#include <iostream>
#include <string>
//#include <exception>
#include <vector>
#include <cstdlib>
using namespace std;

#include "EZTechMovie_Admin_App.h"


// Default Constructor
Global_Functions::Global_Functions() {
	tempStr = ""; //general use string
}

// Purpose: Clear the terminal screen.
void Global_Functions::clearScreen() {
	system("cls");
}

// Purpose: Convert all chars in a string to UPPER case.
string Global_Functions::strToUpperCase(string str) {
	tempStr = "";
	char c;

	for (int i = 0; i < str.size(); ++i) {
		c = str.at(i);
		if (isalpha(c) and islower(c)) {
			tempStr.push_back(toupper(c));
		}
		else {
			tempStr.push_back(c);
		}
	}
	return tempStr;
}

// Purpose: Convert all chars in a string to LOWER case.
string Global_Functions::strToLowerCase(string str) {
	tempStr = "";
	char c;

	for (int i = 0; i < str.size(); ++i) {
		c = str.at(i);
		if (isalpha(c) and isupper(c)) {
			tempStr.push_back(tolower(c));
		}
		else {
			tempStr.push_back(c);
		}
	}
	return tempStr;
}

// Purpose: Validate user input when navigating the menus.
bool Global_Functions::validate_UserOption(vector<int> list, int num) {

	for (auto& i : list) {
		if (num == i) {
			return true;
		}
	}
	return false;
}

