
#ifdef _WIN32
#include <conio.h>
#endif

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

// Purpose: Obtain the user's input when selecting menu options. Validate's input too.
char Global_Functions::getUsrInput() {
	char c;
	std::cout << "\nUser Input: ";
#ifdef _WIN32
	c = _getch(); // Get a character without requiring ENTER
#else
	std::string input;
	std::getline(std::cin, input);
	if (!input.empty()) {
		c = input[0];
	}
	else {
		c = ' ';
	}
#endif
	return c;
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

