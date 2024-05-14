
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

#include "EZTechMovie_Admin_App.h"


// Default Constructor
Global_Functions::Global_Functions() {
	Notifications = {}; // Vector<Vector<String>> | Contains vector objects sent from various classes to display error/system messages.
	sys_msg = {}; // Vector<String> | General use message container.
	tempStr = ""; // General use string.
}

// Purpose: Clear the terminal screen.
void Global_Functions::clearScreen() {
	system("cls");
}

/*
* Purpose: Takes in a system/error message + a list of menu options for the user to choose from.
* Prints out a standard header. Then, if 'msg' is not empty, print that. Then, print the menu options.
*/
void Global_Functions::displayHeader(vector<string> menu) {
	clearScreen();

	cout << "\n##############################################################################" << endl;
	cout << "####### Welcome to the EZTechMovie Database Administration Application #######" << endl;
	cout << "##############################################################################" << endl << endl;

	// Display sys/err messages if the array is not empty.
	if (Notifications.size() > 0) {
		for (auto& i : Notifications) {
			for (auto& j : i) {
				cout << j << endl;
			}
		}
		cout << endl;
	}

	// Display menu options.
	for (auto& i : menu) {
		cout << i << endl;
	}

	// Clear the last set of messages from the 'Notifications' list.
	// This is to ensure that old messages are automatically removed from the Header the next time it it generated.
	if (Notifications.size() > 0) {
		removeLastMsg();
	}
}

// Purpose: Adds a set of messages to the list 'Notifications'.
void Global_Functions::addMsg(vector<string> msg) {
	Notifications.push_back(msg);
}

// Purpose: Removes the oldest set of messages from the list 'Notifications'.
void Global_Functions::removeLastMsg() {
	Notifications.erase(Notifications.begin());
}

// Purpose: Clears the entire 'Notifications' list.
void Global_Functions::clearAllMsgs() {
	Notifications.clear();
}

// Purpose: Validate user input when navigating the menus.
bool Global_Functions::validate_UserOption(vector<int> list, int num) {

	for (auto& i : list) {
		if (num == i) {
			return true;
		}
	}
	tempStr = "ERROR: [" + to_string(num) + "] is not a valid entry!";
	sys_msg.push_back(tempStr);
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

