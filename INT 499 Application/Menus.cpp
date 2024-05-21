
#include <iostream>
#include <string>
#include <exception>
#include <vector>
using namespace std;

#include "EZTechMovie_Admin_App.h"

/*
* 0 = EXIT PROGRAM
* 1 = start screen
* 2 = login screen
* 3 = main menu
* 4 = 'display' menu
* 5 = 'edit' menu
* 6 = admin account
*/


Menus::Menus() {
	tempStr = "";
	msgSet = {}; // [vector<string>] Contains a single set of sys/err messages.
	msgSetList = {}; // [vector<vector<string>>] Container for multiple sets of sys/err messages.
	currMenu = '1'; //default value is '1' for start screen.
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

// Returns the full menu being displayed [type vector<string>].
vector<string> Menus::getCurrMenu() {
	// No need for this code for now.
	// If need later, use a switch.
	vector<string> empty = {};
	return empty;
}

// Returns the number correspoding to the current menu being displayed in the terminal.
char Menus::getCurrMenuNum() {
	return currMenu;
}

// SCREEN: Start screen
void Menus::SCRN_start(vector<string> msg) {
	displayMenu(msg, start_Menu);
	currMenu = '1';
}

// SELECTION: Start screen
char Menus::SLCT_start(char input) {
	//char c = 'a';

	switch (input) {
		case '0':
			return '0'; //EXIT PROGRAM
			//break;
		case '1':
			return '2'; //Login
			//break;
	}
}

// SCREEN: Login screen
void Menus::SCRN_login(vector<string> msg) {
	displayMenu(msg);
	currMenu = '2';
}

// SCREEN: Main Menu
void Menus::SCRN_mainMenu(vector<string> msg) {
	displayMenu(msg, main_Menu);
	currMenu = '3';
}

// SELECTION: Main Menu
char Menus::SLCT_mainMenu(char input) {
	//char c = 'a';

	switch (input) {
		case '0':
			return '1'; //Start
			//break;
		case '1':
			return '4'; //Display
			//break;
		case '2':
			return '5'; //Edit
			//break;
		case '3':
			return '6'; //Admin Account
			//break;
	}
}

