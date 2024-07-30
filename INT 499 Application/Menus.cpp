
#ifdef _WIN32
#include <windows.h>
#endif

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
constexpr auto BG =		"\033[48;2;50;52;64m";
constexpr auto TEXT =	"\033[38;2;248;248;242m";
constexpr auto PURPLE = "\033[38;2;255;121;198m";
constexpr auto YELLOW = "\033[38;2;241;250;140m";


Menus::Menus() {
	currMenu = '1'; // Default value is '1' for the welcome screen.
	prevMenu = '1'; // Stores identifier of the last menu displayed for regression.

	pattern = "\x1B\[[;\\d]*m"; // Regular expression for ANSI escape codes.

	header_text = "Welcome to the EZTechMovie Database Administration Application";
	header = string(YELLOW) + "\n##############################################################################\n" +
			"####### " + TEXT + header_text + YELLOW + " #######\n" +
			"##############################################################################\n\n" + TEXT;

	nav_main = string(YELLOW) + "##### [ " + TEXT + "Main Menu" + YELLOW + " ] #####" + TEXT;
	nav_dispTbl = string(YELLOW) + "##### [ " + TEXT + "Main Menu > Display Tables" + YELLOW + " ] #####" + TEXT;
	nav_admAct = string(YELLOW) + "##### [ " + TEXT + "Main Menu > Admin Actions" + YELLOW + " ] #####" + TEXT;
	nav_modMovie = string(YELLOW) + "##### [ " + TEXT + "Main Menu > Admin Actions > Modify Movie Data" + YELLOW + " ] #####" + TEXT;
	nav_modCust = string(YELLOW) + "##### [ " + TEXT + "Main Menu > Admin Actions > Modify Customer Data" + YELLOW + " ] #####" + TEXT;

	base_Menu = { string(YELLOW) + " [0] " + TEXT + "Previous Menu" };
	start_Menu = { string(YELLOW) + " [1] " + TEXT + "Sign In",
		string(YELLOW) + " [0] " + TEXT + "Exit Application" };
	main_Menu = { string(YELLOW) + " [1] " + TEXT + "Display Tables",
		string(YELLOW) + " [2] " + TEXT + "Admin Actions",
		string(YELLOW) + " [0] " + TEXT + "Sign Out" };
	displayTables_Menu = { string(YELLOW) + " [A] " + TEXT + "tbl_plans",
		string(YELLOW) + " [B] " + TEXT + "tbl_moviedata",
		string(YELLOW) + " [C] " + TEXT + "tbl_actors",
		string(YELLOW) + " [D] " + TEXT + "tbl_directors",
		string(YELLOW) + " [E] " + TEXT + "tbl_genredata",
		string(YELLOW) + " [F] " + TEXT + "tbl_moviecast",
		string(YELLOW) + " [G] " + TEXT + "tbl_moviedirectors",
		string(YELLOW) + " [H] " + TEXT + "tbl_moviegenres",
		string(YELLOW) + " [I] " + TEXT + "tbl_custdata",
		string(YELLOW) + " [J] " + TEXT + "tbl_paymentinfo",
		string(YELLOW) + " [K] " + TEXT + "tbl_custactivity_stream",
		string(YELLOW) + " [L] " + TEXT + "tbl_custactivity_dvd",
		string(YELLOW) + " [M] " + TEXT + "tbl_dvdrentalhistory",
		string(YELLOW) + " [0] " + TEXT + "Previous Menu" };
	adminActions_Menu = { string(YELLOW) + " [1] " + TEXT + "Modify Movie Data",
		string(YELLOW) + " [2] " + TEXT + "Modify Customer Data",
		string(YELLOW) + " [0] " + TEXT + "Previous Menu" };
	modifyMovie_Menu = { string(YELLOW) + " [1] " + TEXT + "Add New Movie",
		string(YELLOW) + " [2] " + TEXT + "Update Movie Info*",
		string(YELLOW) + " [3] " + TEXT + "Delete Movie*",
		string(YELLOW) + " [0] " + TEXT + "Previous Menu" };
	modifyCust_Menu = { string(YELLOW) + " [1] " + TEXT + "Add New Customer*",
		string(YELLOW) + " [2] " + TEXT + "Update Customer Info*",
		string(YELLOW) + " [3] " + TEXT + "Delete Customer*",
		string(YELLOW) + " [0] " + TEXT + "Previous Menu" };
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


		cout << string(PURPLE) + encase + TEXT;

		// Display table data.
		for (int i = 0; i < tblData.size(); i++) {
			for (int k = 0; k < tblData[i].size(); k++) {
				cout << string(PURPLE) + "| " + TEXT << tblData[i][k];
				for (int j = tblData[i][k].size(); j < colSizes[k]; j++) {
					cout << " ";
				}

				if (k != tblData[i].size() - 1) {
					cout << " ";
				}
				else {
					cout << string(PURPLE) + " |" + TEXT << endl;
				}
			}
		}

		cout << string(PURPLE) + encase + TEXT << endl;
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

