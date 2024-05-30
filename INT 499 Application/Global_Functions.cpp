
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
	tempStr = ""; // General use string.
	c = 'X';
}

// Purpose: Clear the terminal screen.
void Global_Functions::clearScreen() {
	system("cls");
}

// Purpose: Obtain the user's input when selecting menu options. Validate's input too.
char Global_Functions::getUsrInput() {
	tempStr = "";
	c = 'X';

	cout << "\nUser Input: ";
#ifdef _WIN32
	c = _getch(); // Get a character without requiring ENTER
#else
	getline(cin, tempStr);
	if (!tempStr.empty()) {
		c = tempStr[0];
	}
	else {
		c = 'X';
	}
#endif
	c = charToUpperCase(c);
	return c;
}

// Purpose: Convert all chars in a string to UPPER case.
string Global_Functions::strToUpperCase(string str) {
	tempStr = "";
	c = 'X';

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
	c = 'X';

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

// Convert a given char to upper case if it is alphabetical.
char Global_Functions::charToUpperCase(char letter) {
	c = 'X';

	if (isalpha(letter) and islower(letter)) {
		c = toupper(letter);
	}
	else {
		c = letter;
	}

	return c;
}

