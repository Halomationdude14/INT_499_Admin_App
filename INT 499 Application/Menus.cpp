
#include <iostream>
#include <string>
#include <exception>
#include <vector>
using namespace std;

#include "EZTechMovie_Admin_App.h"

/*
* B = base menu
* 0 = EXIT PROGRAM
* 1 = start menu
* 2 = login screen
* 3 = main menu
* 4 = display menu
* 5 = edit menu
* 6 = admin account
*/


Menus::Menus() {
	tempStr = "";
	msgSet = {}; // [vector<string>] Contains a single set of sys/err messages.
	msgSetList = {}; // [vector<vector<string>>] Container for multiple sets of sys/err messages.
	currMenu = '1'; // default value is '1' for start screen.
	prevMenu = '1'; // contains value of the last menu displayed for regression.
	base_Menu = {" [0] Previous Menu"};
	start_Menu = {" [1] Sign In"," [0] Exit Application"};
	main_Menu = {" [1] Display Data"," [2] Modify Data"," [3] Admin Account"," [0] Sign Out"};
}

// Displays partial UI: header + message (if not empty*)
void Menus::displayMenu(vector<string> msg) {
	fct.clearScreen();

	cout << "\n##############################################################################" << endl;
	cout << "####### Welcome to the EZTechMovie Database Administration Application #######" << endl;
	cout << "##############################################################################" << endl << endl;

	// Display sys/err messages if the array is not empty.
	// REWORK: May not need the "if" stmt.
	if (msg.size() > 0) {
		for (auto& i : msg) {
			cout << i << endl;
		}
		cout << endl;
	}
}

// Displays full UI: header + message (if not empty*) + menu
void Menus::displayMenu(vector<string> msg, vector<string> menu) {
	fct.clearScreen();

	cout << "\n##############################################################################" << endl;
	cout << "####### Welcome to the EZTechMovie Database Administration Application #######" << endl;
	cout << "##############################################################################" << endl << endl;

	// Display sys/err messages if the array is not empty.
	// REWORK: May not need the "if" stmt.
	if (msg.size() > 0) {
		for (auto& i : msg) {
			cout << i << endl;
		}
		cout << endl;
	}

	// Display menu options.
	for (auto& i : menu) {
		cout << i << endl;
	}
}

// Returns the number correspoding to the current menu being displayed in the terminal.
char Menus::getCurrMenu() const {
	return currMenu;
}

char Menus::getPrevMenu() const {
	return prevMenu;
}

// SCREEN: Base screen (used for testing purposes and dead end UIs)
void Menus::SCRN_BASE(vector<string> msg) {
	msg.push_back("TEST: Base Screen Displayed!");
	displayMenu(msg, base_Menu);

	if (!(currMenu == 'B')) {
		prevMenu = currMenu;
	}
	currMenu = 'B';
}

// SELECTION: Base screen
char Menus::SLCT_BASE(char input) {
	if (input == '0') {
		return prevMenu;
	}
	else {
		return 'x';
	}
}

// SCREEN: Start screen
void Menus::SCRN_start(vector<string> msg) {
	displayMenu(msg, start_Menu);
	if (!(currMenu == '1')) {
		prevMenu = currMenu;
	}
	currMenu = '1';
}

// SELECTION: Start screen
char Menus::SLCT_start(char input) {
	switch (input) {
		case '0':
			return '0'; //EXIT PROGRAM
		case '1':
			return '2'; //Login
		default:
			return 'x';
	}
}

// SCREEN: Login screen
void Menus::SCRN_login(vector<string> msg) {
	displayMenu(msg);
	if (!(currMenu == '2')) {
		prevMenu = currMenu;
	}
	currMenu = '2';
}

// SCREEN: Main Menu
void Menus::SCRN_mainMenu(vector<string> msg) {
	displayMenu(msg, main_Menu);
	if (!(currMenu == '3')) {
		prevMenu = currMenu;
	}
	currMenu = '3';
}

// SELECTION: Main Menu
char Menus::SLCT_mainMenu(char input) {
	switch (input) {
		case '0':
			return '1'; //Start
		case '1':
			return '4'; //Display
		case '2':
			return '5'; //Edit
		case '3':
			return '6'; //Admin Account
		default:
			return 'x';
	}
}

