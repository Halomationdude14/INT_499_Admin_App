
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
*	4 = display tables menu
*		5 = display table
*			A = Add Entry
*			B = Update Entry
* 			C = Delete Entry
*	6 = admin actions
*		7 = Modify Movie Data
*			A = Add New Movie
* 			B = Update Movie Info
* 			C = Delete Movie
* 		8 = Modify Customer Data
* 			A = Add New Customer
* 			B = Update Customer Info
* 			C = Delete Customer
*/


Menus::Menus() {
	tempStr = "";
	currMenu = '1'; // default value is '1' for start screen.
	prevMenu = '1'; // contains value of the last menu displayed for regression.
	
	// True = user may not swap from display-mode to edit-mode for a given table
	// False = user can swap from display-mode to edit-mode for a given table
	noEdit_Table = true;

	base_Menu = {" [0] Previous Menu"};
	start_Menu = {" [1] Sign In"," [0] Exit Application"};
	main_Menu = {" [1] Display Tables", " [2] Admin Actions", " [0] Sign Out"};
	displayTables_Menu = {" [A] tbl_plans"," [B] tbl_actors"," [C] tbl_custdata"," [D] tbl_moviedata"," [E] tbl_paymentinfo",
		" [F] tbl_directors"," [G] tbl_genredata"," [H] tbl_moviedirectors"," [I] tbl_moviegenres"," [J] tbl_moviecast",
		" [K] tbl_custactivity_dvd"," [L] tbl_custactivity_stream"," [M] tbl_dvdrentalhistory"," [0] Return to Main Menu"};
	editTable_Menu = {" [1] Add Entry*"," [2] Update Entry*"," [3] Delete Entry*"," [0] Return to Previous Menu"};
	noEditTable_Menu = {"[0] Return to Previous Menu"};

	adminActions_Menu = {" [1] Add/Remove Movie"," [2] Modify Customer Data"," [0] Return to Main Menu"};
	modifyMovie_Menu = {" [1] Add New Movie"," [2] Update Movie Info"," [3] Delete Movie"," [0] Previous Menu"};
	modifyCust_Menu = {" [1] Add New Customer"," [2] Update Customer Info"," [3] Delete Customer"," [0] Previous Menu"};
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

// Displays partial UI: header + message + selected table from the database
void Menus::displayTable(vector<string> msg, vector<vector<string>> tblData) {
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
		case '0': //sign out
			return '1';
			break;
		case '1': //display tables
			return '4';
			break;
		case '2': //admin actions
			return '6';
			break;
		default:
			return 'X';
			break;
	}
}

// SCREEN: Display menu
void Menus::SCRN_displayMenu(vector<string> msg) {
	displayMenu(msg, displayTables_Menu);
	if (!(currMenu == '4')) {
		prevMenu = currMenu;
		currMenu = '4';
	}
}

// SELECTION: Display menu
char Menus::SLCT_displayMenu(char input) {

	switch (input) {
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
			return '5';
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
			noEdit_Table = true; //Tables [H-M] may NOT be edited
			return '5';
		default:
			return 'X';
	}
}

// SCREEN: Display table menu
void Menus::SCRN_displayTable(vector<string> msg, vector<vector<string>> tblData) {
	if (noEdit_Table == true) {
		displayTable(msg, noEditTable_Menu, tblData);
	}
	else {
		displayTable(msg, editTable_Menu, tblData);
	}
	
	if (!(currMenu == '5')) {
		prevMenu = currMenu;
		currMenu = '5';
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
			case '1': //add new entry
				return '5';
			case '2': //delete existing entry
				return '5';
			case '3': //update existing entry
				return '5'; //***add new UIs for add/delete/update entries***
			default:
				return 'X';
		}
	}
}

// SCREEN: Admin Actions menu
void Menus::SCRN_adminActions(vector<string> msg) {
	displayMenu(msg, adminActions_Menu);
	if (!(currMenu == '6')) {
		prevMenu = currMenu;
		currMenu = '6';
	}
}

// SELECTION: Admin Actions menu
char Menus::SLCT_adminActions(char input) {
	switch (input) {
		case '0':
			return '3'; //main menu
		case '1':
			return '7';
		case '2':
			return '8';
		default:
			return 'X';
	}
}

// SCREEN: Modify Movie menu
void Menus::SCRN_modMovieMenu(vector<string> msg) {
	displayMenu(msg, modifyMovie_Menu);
	if (!(currMenu == '7')) {
		prevMenu = currMenu;
		currMenu = '7';
	}
}

// SELECTION: Modify Movie menu
char Menus::SLCT_modMovieMenu(char input) {
	switch (input) {
		case '0':
			return '6'; //Previous menu
		case '1': //add
			return '7';
		case '2': //update
			return '7';
		case '3': //delete
			return '7';
		default:
			return 'X';
	}
}

// SCREEN: Modify Customer menu
void Menus::SCRN_modCustMenu(vector<string> msg) {
	displayMenu(msg, modifyCust_Menu);
	if (!(currMenu == '8')) {
		prevMenu = currMenu;
		currMenu = '8';
	}
}

// SELECTION: Modify Customer menu
char Menus::SLCT_modCustMenu(char input) {
	switch (input) {
		case '0':
			return '6'; //Previous menu
		case '1': //add
			return '8';
		case '2': //update
			return '8';
		case '3': //delete
			return '8';
		default:
			return 'X';
	}
}

