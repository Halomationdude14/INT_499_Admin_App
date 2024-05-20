
#include <iostream>
#include <string>
#include <exception>
#include <vector>
using namespace std;

#include "EZTechMovie_Admin_App.h"


Menus::Menus() {
	tempStr = "";
	msgSet = {}; // [vector<string>] Contains a single set of sys/err messages.
	msgSetList = {}; // [vector<vector<string>>] Container for multiple sets of sys/err messages.
	currMenu = {};
	currOptions = {};
	start_Menu = {" [1] Sign In"," [2] Exit Application"};
	startMenu_Options = {1,2};
	main_Menu = {" [1] Display Data"," [2] Modify Data"," [3] Admin Account"," [4] Sign Out"};
	mainMenu_Options = {1,2,3,4};
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
	}

	// Display menu options.
	for (auto& i : menu) {
		cout << i << endl;
	}
}

// Returns the name of the variable which corresponds to the menu currently being displayed.
vector<string> Menus::getCurrMenu() {
	return currMenu;
}

// SCREEN: Start screen
void Menus::SCRN_start(vector<string> msg) {
	displayMenu(msg, start_Menu);
	currMenu = start_Menu;
}

// SCREEN: Login screen
void Menus::SCRN_login(vector<string> msg) {
	displayMenu(msg);
	currMenu.clear();
}

// SCREEN: Main Menu
void Menus::SCRN_mainMenu(vector<string> msg) {
	displayMenu(msg, main_Menu);
	currMenu = main_Menu;
}

