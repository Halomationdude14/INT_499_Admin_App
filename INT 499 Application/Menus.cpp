
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
* 7 = display table
* 8 = edit table
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
	display_Menu = {" [1] tbl_plans"," [2] tbl_actors"," [3] tbl_custdata"," [4] tbl_moviedata"," [5] tbl_paymentinfo"," [6] tbl_directors"," [7] tbl_genredata"," [8] tbl_moviedirectors"," [9] tbl_moviegenres"," [10] tbl_moviecast"," [11] tbl_custactivity_dvd"," [12] tbl_custactivity_stream"," [13] tbl_dvdrentalhistory"," [0] Main Menu"};
	displayTable_Menu = {" [1] Switch to \'Edit Mode\'"," [0] Return to Display Menu"};
	edit_Menu = {" [1] tbl_plans"," [2] tbl_actors"," [3] tbl_custdata"," [4] tbl_moviedata"," [5] tbl_paymentinfo"," [6] tbl_directors"," [7] tbl_genredata"," [0] Main Menu"};
	editTable_Menu = {" [1] Add Entry*"," [2] Update Entry*"," [3] Delete Entry*"," [4] Switch to \'Display Mode\'"," [0] Return to Edit Menu"};
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

// Displays full UI w/a selected table from the database
void Menus::displayTable(vector<string> msg, vector<string> menu, vector<vector<string>> tblData) {
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

	// Display table data
	for (const auto& row : tblData) {
		for (const auto& col : row) {
			cout << col << " ";
		}
		cout << endl;
	}
	cout << endl;

	// Display menu options.
	for (auto& i : menu) {
		cout << i << endl;
	}
}

// Displays full UI w/admin info
void Menus::displayAdmin(vector<string> msg, vector<string> menu, vector<vector<string>> tblData) {
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

	// Display Admin info

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
	displayMenu(msg, base_Menu);
	if (!(currMenu == 'B')) {
		prevMenu = currMenu;
		currMenu = 'B';
	}
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
		currMenu = '1';
	}
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
		currMenu = '2';
	}
}

// SCREEN: Main Menu
void Menus::SCRN_mainMenu(vector<string> msg) {
	displayMenu(msg, main_Menu);
	if (!(currMenu == '3')) {
		prevMenu = currMenu;
		currMenu = '3';
	}
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

// SCREEN: Display menu
void Menus::SCRN_displayMenu(vector<string> msg) {
	displayMenu(msg, display_Menu);
	if (!(currMenu == '4')) {
		prevMenu = currMenu;
		currMenu = '4';
	}
}

// SELECTION: display menu
char Menus::SLCT_displayMenu(char input) {
	switch (input) {
		case '0':
			return '3'; //main menu
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '10':
		case '11':
		case '12':
		case '13':
			return '7';
		default:
			return 'x';
	}
}

// SCREEN: Display table menu
void Menus::SCRN_displayTable(vector<string> msg, vector<vector<string>> tblData) {
	displayTable(msg, displayTable_Menu, tblData);
	if (!(currMenu == '7')) {
		prevMenu = currMenu;
		currMenu = '7';
	}
}

// SELECTION: Display table menu
char Menus::SLCT_displayTable(char input) {
	switch (input) {
		case '0':
			return '4'; //display menu
		case '1':
			return '8'; // Switch to edit mode
		default:
			return 'x';
	}
}

// SCREEN: Edit menu
void Menus::SCRN_editMenu(vector<string> msg) {
	displayMenu(msg, edit_Menu);
	if (!(currMenu == '5')) {
		prevMenu = currMenu;
		currMenu = '5';
	}
}

// SELECTION: Edit menu
char Menus::SLCT_editMenu(char input) {
	switch (input) {
	case '0':
		return '3'; //main menu
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
		return '8';
	default:
		return 'x';
	}
}

// SCREEN: Edit table menu
void Menus::SCRN_editTable(vector<string> msg, vector<vector<string>> tblData) {
	displayTable(msg, editTable_Menu, tblData);
	if (!(currMenu == '8')) {
		prevMenu = currMenu;
		currMenu = '8';
	}
}

// SELECTION: Edit table menu
char Menus::SLCT_editTable(char input) {
	switch (input) {
		case '0':
			return '5'; //edit menu
		case '1': //add new entry
		case '2': //delete existing entry
		case '3': //update existing entry
			return '8'; // Keep current UI the same. Let main() handle the user input
		case '4':
			return '7'; // Switch to display_table mode
		default:
			return 'x';
	}
}

// SCREEN: Admin Account
void Menus::SCRN_adminAccount(vector<string> msg) {
	// New method to display admin account info
	//displayAdmin(msg);
	if (!(currMenu == '6')) {
		prevMenu = currMenu;
		currMenu = '6';
	}
}

// SELECTION: Admin Account
char Menus::SLCT_adminAccount(char input) {
	if (input == '0') {
		return prevMenu;
	}
	else {
		return 'x';
	}
}



