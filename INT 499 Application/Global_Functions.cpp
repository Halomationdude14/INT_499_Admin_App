
/*
INT 499 Capstone for Information Technology
Interactive Assignment
Date: 2024-04-22
Author: Paul Oram
NOTE: This is a modified version of the original code that has been reworked to integrate into the final project (MySQL DB).
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

#include "EZTechMovie_Admin_App.h"


// Default Constructor
Global_Functions::Global_Functions() {
	SYS_Msgs = {}; // Array of strings to display between the header and the menu
	tempStr = ""; // General use string
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
	//Once rework is complete, remove "string msg" from method variables!
	clearScreen();

	cout << "\n##############################################################################" << endl;
	cout << "####### Welcome to the EZTechMovie Database Administration Application #######" << endl;
	cout << "##############################################################################" << endl << endl;

	/*
	if (msg.length() > 0) {
		cout << msg << endl << endl;
	}
	*/

	// Display sys/err messages if the array is not empty.
	if (SYS_Msgs.size() > 0) {
		for (auto& i : SYS_Msgs) {
			cout << i << endl;
		}
	}

	// Display menu options.
	for (auto& i : menu) {
		cout << i << endl;
	}
}

// Purpose: Adds a message to SYS_Msgs to display with the header.
void Global_Functions::addMsg(string msg) {

}

// Purpose: Removes a message from SYS_Msgs to display with the header.
void Global_Functions::removeMsg(string msg) {

}

// Purpose: Clears the entire SYS_Msgs array.
void Global_Functions::clearAllMsgs() {
	SYS_Msgs = {};
}

// Purpose: Validate user input when navigating the menus.
bool Global_Functions::validate_UserOption(vector<int> list, int num) {

	for (auto& i : list) {
		if (num == i) {
			return true;
		}
		else {
			string s = "ERROR: [" + to_string(num) + "] is not a valid entry!";
			SYS_Msgs.push_back(s);
			return false;
		}
	}
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

