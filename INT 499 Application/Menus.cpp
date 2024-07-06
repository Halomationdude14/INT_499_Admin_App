
#include <iostream>
#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "EZTechMovie_Admin_App.h"


/*
* Program UI Outline --> (~ indicates an active process; no unique UI ID)
* 
* 0 = STOP PROGRAM
* 1 = Welcome Screen
* 2 = Login Screen
* 3 = Main Menu
*	4 = Display Tables Menu
*		5 = Display table
*			~ = Add Entry
*			~ = Update Entry
* 			~ = Delete Entry
*	6 = Admin Actions Menu
*		7 = Modify Movie Data Menu
*			~ = Add New Movie
* 			~ = Update Movie Info
* 			~ = Delete Movie
* 		8 = Modify Customer Data Menu
* 			~ = Add New Customer
* 			~ = Update Customer Info
* 			~ = Delete Customer
* 
*		? = Modify Actors
*			~ = Add New Actor
* 			~ = Update Actor Info
* 			~ = Delete Actor
* 		? = Modify Directors
* 			~ = Add New Director
* 			~ = Update Director Info
* 			~ = Delete Director
* 		? = Modify Genres
* 			~ = Add New Genre
* 			~ = Update Genre Info
* 			~ = Delete Genre
*/


Menus::Menus() {
	currMenu = '1'; // Default value is '1' for the welcome screen.
	prevMenu = '1'; // Stores identifier of the last menu displayed for regression.

	header = "\n##############################################################################\n"
			   "####### Welcome to the EZTechMovie Database Administration Application #######\n"
			   "##############################################################################\n\n";

	nav_main = "##### [ Main Menu ] #####";
	nav_dispTbl = "##### [ Main Menu > Display Tables ] #####";
	nav_admAct = "##### [ Main Menu > Admin Actions ] #####";
	nav_modMovie = "##### [ Main Menu > Admin Actions > Modify Movie Data ] #####";
	nav_modCust = "##### [ Main Menu > Admin Actions > Modify Customer Data ] #####";

	base_Menu = {" [0] Previous Menu"};
	start_Menu = {" [1] Sign In"," [0] Exit Application"};
	main_Menu = {" [1] Display Tables", " [2] Admin Actions", " [0] Sign Out"};
	displayTables_Menu = {" [A] tbl_plans"," [B] tbl_moviedata"," [C] tbl_actors"," [D] tbl_directors"," [E] tbl_genredata",
		" [F] tbl_moviecast"," [G] tbl_moviedirectors"," [H] tbl_moviegenres"," [I] tbl_custdata"," [J] tbl_paymentinfo",
		" [K] tbl_custactivity_stream"," [L] tbl_custactivity_dvd"," [M] tbl_dvdrentalhistory"," [0] Previous Menu"};
	adminActions_Menu = {" [1] Modify Movie Data"," [2] Modify Customer Data"," [0] Previous Menu"};
	modifyMovie_Menu = {" [1] Add New Movie"," [2] Update Movie Info*"," [3] Delete Movie*"," [0] Previous Menu"};
	modifyCust_Menu = {" [1] Add New Customer*"," [2] Update Customer Info*"," [3] Delete Customer*"," [0] Previous Menu"};
}

// Displays base UI: header
void Menus::displayMenu() {
	fct.clearScreen();
	cout << header;
}

// Displays partial UI: header + message
void Menus::displayMenu(vector<string> msg) {
	displayMenu();

	// Display sys/err messages if the vector is not empty.
	if (!(msg.empty())) {
		for (auto& i : msg) {
			cout << i << endl;
		}
		cout << endl;
	}
}

// Displays partial UI: header + message + nav
void Menus::displayMenu(vector<string> msg, string nav) {
	displayMenu();
	
	if (!nav.empty()) {
		int space = (78-nav.size())/2;
		for (int i = 0; i < space; i++) {
			cout << " ";
		}
		cout << nav;
		for (int i = 0; i < space; i++) {
			cout << " ";
		}
		cout << endl << endl;
	}

	// Display sys/err messages if the vector is not empty.
	if (!(msg.empty())) {
		for (auto& i : msg) {
			cout << i << endl;
		}
		cout << endl;
	}
}

// Displays full UI: header + nav + message + menu
void Menus::displayMenu(vector<string> msg, string nav, vector<string> menu) {
	displayMenu(msg, nav);

	// Display menu options.
	for (auto& i : menu) {
		cout << i << endl;
	}
}

// Displays partial UI: header + message + selected table from the database
void Menus::displayTable(vector<string> msg, vector<vector<string>> tblData) {
	displayMenu();

	// Display table data
	for (const auto& row : tblData) {
		for (const auto& col : row) {
			cout << col << " ";
		}
		cout << endl;
	}
	cout << endl;

	// Display sys/err messages if the vector is not empty.
	if (!(msg.empty())) {
		for (auto& i : msg) {
			cout << i << endl;
		}
		cout << endl;
	}
}

// Displays full UI w/a selected table from the database
void Menus::displayTable(vector<string> msg, vector<string> menu, vector<vector<string>> tblData) {
	displayMenu();

	// Display table data
	for (const auto& row : tblData) {
		for (const auto& col : row) {
			cout << col << " ";
		}
		cout << endl;
	}
	cout << endl;

	// Display sys/err messages if the vector is not empty.
	if (!(msg.empty())) {
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

// Returns the number correspoding to the previous menu that was displayed in the terminal.
char Menus::getPrevMenu() const {
	return prevMenu;
}

// SCREEN: Welcome screen
void Menus::SCRN_start(vector<string> msg) {
	displayMenu(msg, "", start_Menu);
	if (!(currMenu == '1')) {
		prevMenu = currMenu;
		currMenu = '1';
	}
}

// SELECTION: Welcome screen
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
	displayMenu(msg, nav_main, main_Menu);
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

// SCREEN: Display Tables menu
void Menus::SCRN_displayMenu(vector<string> msg) {
	displayMenu(msg, nav_dispTbl, displayTables_Menu);
	if (!(currMenu == '4')) {
		prevMenu = currMenu;
		currMenu = '4';
	}
}

// SELECTION: Display Tables menu
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
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
			return '5';
		default:
			return 'X';
	}
}

// SCREEN: Display Table screen
void Menus::SCRN_displayTable(vector<string> msg, vector<vector<string>> tblData) {
	displayTable(msg, base_Menu, tblData);
	if (!(currMenu == '5')) {
		prevMenu = currMenu;
		currMenu = '5';
	}
}

// SELECTION: Display Table screen
char Menus::SLCT_displayTable(char input) {
	switch (input) {
		case '0':
			return '4'; //display tables menu
		default:
			return 'X';
	}
}

// SCREEN: Admin Actions menu
void Menus::SCRN_adminActions(vector<string> msg) {
	displayMenu(msg, nav_admAct, adminActions_Menu);
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
			return '7'; //Modify Movie Data menu
		case '2':
			return '8'; //Modify Customer Data menu
		default:
			return 'X';
	}
}

// SCREEN: Modify Movie menu
void Menus::SCRN_modMovieMenu(vector<string> msg) {
	displayMenu(msg, nav_modMovie, modifyMovie_Menu);
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
		case '1': //insert
		case '2': //update
		case '3': //delete
			return '7'; //NOTE: Must set to value other than '7' due to UI processing
		default:
			return 'X';
	}
}

// SCREEN: Modify Customer menu
void Menus::SCRN_modCustMenu(vector<string> msg) {
	displayMenu(msg, nav_modCust, modifyCust_Menu);
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
		case '1': //insert
		case '2': //update
		case '3': //delete
			return '8'; //return same UI ref num; main() will handle these options
		default:
			return 'X';
	}
}

