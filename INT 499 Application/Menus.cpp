
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
	
	// True = user may not swap from display-mode to edit-mode for a given table
	// False = user can swap from display-mode to edit-mode for a given table
	noEdit_Table = true;

	base_Menu = {" [0] Previous Menu"};
	start_Menu = {" [1] Sign In"," [0] Exit Application"};
	main_Menu = {" [1] Display Data"," [2] Modify Data"," [3] Admin Account"," [0] Sign Out"};
	display_Menu = {" [A] tbl_plans"," [B] tbl_actors"," [C] tbl_custdata"," [D] tbl_moviedata"," [E] tbl_paymentinfo",
		" [F] tbl_directors"," [G] tbl_genredata"," [H] tbl_moviedirectors"," [I] tbl_moviegenres"," [J] tbl_moviecast",
		" [K] tbl_custactivity_dvd"," [L] tbl_custactivity_stream"," [M] tbl_dvdrentalhistory"," [0] Main Menu"};
	displayTable_Menu = {" [1] Switch to \'Edit Mode\'"," [0] Return to Display Menu"};
	displayTable_Menu_NoEdit = {"[0] Return to Display Menu"};
	edit_Menu = {" [A] tbl_plans"," [B] tbl_actors"," [C] tbl_custdata"," [D] tbl_moviedata"," [E] tbl_paymentinfo",
		" [F] tbl_directors"," [G] tbl_genredata"," [0] Main Menu"};
	editTable_Menu = {" [1] Switch to \'Display Mode\'"," [2] Add Entry*"," [3] Update Entry*"," [4] Delete Entry*"," [0] Return to Edit Menu"};
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

	// Display table data
	for (const auto& row : tblData) {
		for (const auto& col : row) {
			cout << col << " ";
		}
		cout << endl;
	}
	cout << endl;

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
		return 'X';
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
			return 'X';
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
			return 'X';
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
	char c = 'X';
	if (isalpha(input) and islower(input)) {
		c = toupper(input);
	}
	c = input;

	switch (c) {
		case '0':
			return '3'; //main menu
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
			noEdit_Table = false; //Tables [A-G] may be edited
			return '7';
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
			noEdit_Table = true; //Tables [H-M] may NOT be edited
			return '7';
		default:
			return 'X';
	}
}

// SCREEN: Display table menu
void Menus::SCRN_displayTable(vector<string> msg, vector<vector<string>> tblData) {
	if (noEdit_Table == true) {
		displayTable(msg, displayTable_Menu_NoEdit, tblData);
	}
	else {
		displayTable(msg, displayTable_Menu, tblData);
	}
	
	if (!(currMenu == '7')) {
		prevMenu = currMenu;
		currMenu = '7';
	}
}

// SELECTION: Display table menu
char Menus::SLCT_displayTable(char input) {
	if (noEdit_Table == true) {
		switch (input) {
			case '0':
				return '4'; //display menu
			default:
				return 'X';
		}
	}
	else {
		switch (input) {
			case '0':
				return '4'; //display menu
			case '1':
				return '8'; // Switch to edit mode
			default:
				return 'X';
		}
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
	char c = 'X';
	if (isalpha(input) and islower(input)) {
		c = toupper(input);
	}
	c = input;
	
	switch (c) {
		case '0':
			return '3'; //main menu
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
			return '8';
		default:
			return 'X';
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
		case '1':
			return '7'; // Switch to display_table mode
		case '2': //add new entry
		case '3': //delete existing entry
		case '4': //update existing entry
			return '8'; //***add new UIs for add/delete/update entries***
		default:
			return 'X';
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
		return 'X';
	}
}



