
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

/*
* Purpose: Takes in a system/error message + a list of menu options for the user to choose from.
* Prints out a standard header. Then, if 'msg' is not empty, print that. Then, print the menu options.
*/
void Global_Functions::displayHeader(string msg, vector<string> menu) {
	clearScreen();

	cout << "\n##############################################################################" << endl;
	cout << "####### Welcome to the EZTechMovie Database Administration Application #######" << endl;
	cout << "##############################################################################" << endl << endl;

	// Display sys/err msg if not empty.
	if (msg.length() > 0) {
		cout << msg << endl << endl;
	}

	// Display menu options.
	for (auto& i : menu) {
		cout << i << endl;
	}
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

