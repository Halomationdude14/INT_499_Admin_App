
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <regex>
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


// Define ANSI color codes
constexpr auto RESET =		"\033[0m";
constexpr auto RED =		"\033[91m";
constexpr auto GREEN =		"\033[92m";
constexpr auto YELLOW =		"\033[93m";
constexpr auto MAGENTA =	"\033[95m";


Menus::Menus() {
	currMenu = '1'; // Default value is '1' for the welcome screen.
	prevMenu = '1'; // Stores identifier of the last menu displayed for regression.

	pattern = "\x1B\[[;\\d]*m"; // Regular expression for ANSI escape codes.

	header_text = "Welcome to the EZTechMovie Database Administration Application";
	header = string(YELLOW) + "\n##############################################################################\n" +
			"####### " + RESET + header_text + string(YELLOW) + " #######\n" +
			"##############################################################################\n\n" + RESET;

	nav_main = string(YELLOW) + "##### [ " + RESET + "Main Menu" + string(YELLOW) + " ] #####" + RESET;
	nav_dispTbl = string(YELLOW) + "##### [ " + RESET + "Main Menu > Display Tables" + string(YELLOW) + " ] #####" + RESET;
	nav_admAct = string(YELLOW) + "##### [ " + RESET + "Main Menu > Admin Actions" + string(YELLOW) + " ] #####" + RESET;
	nav_modMovie = string(YELLOW) + "##### [ " + RESET + "Main Menu > Admin Actions > Modify Movie Data" + string(YELLOW) + " ] #####" + RESET;
	nav_modCust = string(YELLOW) + "##### [ " + RESET + "Main Menu > Admin Actions > Modify Customer Data" + string(YELLOW) + " ] #####" + RESET;

	base_Menu = { string(YELLOW) + " [0] " + RESET + "Previous Menu" };
	start_Menu = { string(YELLOW) + " [1] " + RESET + "Sign In",
		string(YELLOW) + " [0] " + RESET + "Exit Application" };
	main_Menu = { string(YELLOW) + " [1] " + RESET + "Display Tables",
		string(YELLOW) + " [2] " + RESET + "Admin Actions",
		string(YELLOW) + " [0] " + RESET + "Sign Out" };
	displayTables_Menu = { string(YELLOW) + " [A] " + RESET + "tbl_plans",
		string(YELLOW) + " [B] " + RESET + "tbl_moviedata",
		string(YELLOW) + " [C] " + RESET + "tbl_actors",
		string(YELLOW) + " [D] " + RESET + "tbl_directors",
		string(YELLOW) + " [E] " + RESET + "tbl_genredata",
		string(YELLOW) + " [F] " + RESET + "tbl_moviecast",
		string(YELLOW) + " [G] " + RESET + "tbl_moviedirectors",
		string(YELLOW) + " [H] " + RESET + "tbl_moviegenres",
		string(YELLOW) + " [I] " + RESET + "tbl_custdata",
		string(YELLOW) + " [J] " + RESET + "tbl_paymentinfo",
		string(YELLOW) + " [K] " + RESET + "tbl_custactivity_stream",
		string(YELLOW) + " [L] " + RESET + "tbl_custactivity_dvd",
		string(YELLOW) + " [M] " + RESET + "tbl_dvdrentalhistory",
		string(YELLOW) + " [0] " + RESET + "Previous Menu" };
	adminActions_Menu = { string(YELLOW) + " [1] " + RESET + "Modify Movie Data",
		string(YELLOW) + " [2] " + RESET + "Modify Customer Data",
		string(YELLOW) + " [0] " + RESET + "Previous Menu" };
	modifyMovie_Menu = { string(YELLOW) + " [1] " + RESET + "Add New Movie",
		string(YELLOW) + " [2] " + RESET + "Update Movie Info*",
		string(YELLOW) + " [3] " + RESET + "Delete Movie*",
		string(YELLOW) + " [0] " + RESET + "Previous Menu" };
	modifyCust_Menu = { string(YELLOW) + " [1] " + RESET + "Add New Customer*",
		string(YELLOW) + " [2] " + RESET + "Update Customer Info*",
		string(YELLOW) + " [3] " + RESET + "Delete Customer*",
		string(YELLOW) + " [0] " + RESET + "Previous Menu" };
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
	if (!msg.empty()) {
		for (auto& i : msg) {
			cout << i << endl;
		}
		cout << endl;
	}
}

// Displays partial UI: header + message + nav
void Menus::displayMenu(vector<string> msg, string nav) {
	displayMenu();
	regex re(pattern);
	string strip_nav = regex_replace(nav, re, "");
	
	if (!nav.empty()) {
		int space = (78- strip_nav.size())/2;

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
	if (!msg.empty()) {
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


// Displays partial UI (header + message) + selected table from the database.
void Menus::displayTable(vector<string> msg, vector<vector<string>> tblData) {
	displayMenu();
	vector<int> colSizes = {};
	string encase = "";

	if (!tblData.empty()) {
		
		// Obtain length of largest variables per column.
		for (const auto& row : tblData) {

			// Initialize [colSizes] with first row.
			if (colSizes.empty()) {
				for (const auto& var : row) {
					colSizes.push_back(var.size());
				}
			}

			// Search for longer variables and update [colSizes] as needed.
			for (int i = 0; i < row.size(); i++) {
				if (row[i].size() > colSizes[i]) {
					colSizes[i] = row[i].size();
				}
			}
		}

		// Establish the upper+lower encasement for the display.
		for (int i = 0; i < colSizes.size(); i++) {
			encase.append("+-");
			for (int j = 0; j < colSizes[i]; j++) {
				encase.append("-");
			}

			if (i != colSizes.size() - 1) {
				encase.append("-");
			}
			else {
				encase.append("-+\n");
			}
		}

		cout << encase;

		// Display table data.
		for (int i = 0; i < tblData.size(); i++) {
			for (int k = 0; k < tblData[i].size(); k++) {
				cout << "| " << tblData[i][k];
				for (int j = tblData[i][k].size(); j < colSizes[k]; j++) {
					cout << " ";
				}

				if (k != tblData[i].size() - 1) {
					cout << " ";
				}
				else {
					cout << " |\n";
				}
			}
		}

		cout << encase << endl;
	}

	// Display sys/err messages if the vector is not empty.
	if (!msg.empty()) {
		for (const auto& i : msg) {
			cout << i << endl;
		}
		cout << endl;
	}
}

// Displays full UI + selected table from the database.
void Menus::displayTable(vector<string> msg, vector<string> menu, vector<vector<string>> tblData) {
	displayTable(msg, tblData);

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

