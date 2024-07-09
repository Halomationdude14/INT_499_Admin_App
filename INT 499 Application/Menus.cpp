
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


// Define ANSI color codes
constexpr auto RESET =		"\033[0m";
constexpr auto RED =		"\033[91m";
constexpr auto GREEN =		"\033[92m";
constexpr auto YELLOW =		"\033[93m";
constexpr auto DarkYELLOW = "\033[33m";
constexpr auto BLUE =		"\033[94m";
constexpr auto MAGENTA =	"\033[95m";
constexpr auto CYAN =		"\033[96m";
constexpr auto WHITE =		"\033[97m";
constexpr auto GREY =		"\033[37m";

// Background colors
constexpr auto bRED =		"\033[41m";
constexpr auto bGREEN =		"\033[42m";
constexpr auto bYELLOW =	"\033[43m";
constexpr auto bBLUE =		"\033[44m";
constexpr auto bMAGENTA =	"\033[45m";
constexpr auto bCYAN =		"\033[46m";
constexpr auto bWHITE =		"\033[47m";


Menus::Menus() {
	currMenu = '1'; // Default value is '1' for the welcome screen.
	prevMenu = '1'; // Stores identifier of the last menu displayed for regression.

	header_text = string(GREY) + "Welcome to the EZTechMovie Database Administration Application" + RESET;
	header = string(BLUE) + "\n##############################################################################\n" +
			string(BLUE) + "####### " + header_text + string(BLUE) + " #######\n" +
			string(BLUE) + "##############################################################################\n\n" + RESET;

	nav_main = string(BLUE) + "##### [ " + string(WHITE) + "Main Menu" + string(BLUE) + " ] #####" + RESET;
	nav_dispTbl = string(BLUE) + "##### [ Main Menu > Display Tables ] #####" + RESET;
	nav_admAct = string(BLUE) + "##### [ Main Menu > Admin Actions ] #####" + RESET;
	nav_modMovie = string(BLUE) + "##### [ Main Menu > Admin Actions > Modify Movie Data ] #####" + RESET;
	nav_modCust = string(BLUE) + "##### [ Main Menu > Admin Actions > Modify Customer Data ] #####" + RESET;

	/*
	base_Menu = { string(DarkYELLOW) + " [0] Previous Menu" + RESET };
	start_Menu = { string(DarkYELLOW) + " [1] Sign In",
		string(DarkYELLOW) + " [0] Exit Application" + RESET };
	main_Menu = { string(DarkYELLOW) + " [1] Display Tables",
		string(DarkYELLOW) + " [2] Admin Actions",
		string(DarkYELLOW) + " [0] Sign Out" + RESET };
	displayTables_Menu = { string(DarkYELLOW) + " [A] tbl_plans",
		string(DarkYELLOW) + " [B] tbl_moviedata",
		string(DarkYELLOW) + " [C] tbl_actors",
		string(DarkYELLOW) + " [D] tbl_directors",
		string(DarkYELLOW) + " [E] tbl_genredata",
		string(DarkYELLOW) + " [F] tbl_moviecast",
		string(DarkYELLOW) + " [G] tbl_moviedirectors",
		string(DarkYELLOW) + " [H] tbl_moviegenres",
		string(DarkYELLOW) + " [I] tbl_custdata",
		string(DarkYELLOW) + " [J] tbl_paymentinfo",
		string(DarkYELLOW) + " [K] tbl_custactivity_stream",
		string(DarkYELLOW) + " [L] tbl_custactivity_dvd",
		string(DarkYELLOW) + " [M] tbl_dvdrentalhistory",
		string(DarkYELLOW) + " [0] Previous Menu" + RESET };
	adminActions_Menu = { string(DarkYELLOW) + " [1] Modify Movie Data",
		string(DarkYELLOW) + " [2] Modify Customer Data",
		string(DarkYELLOW) + " [0] Previous Menu" + RESET };
	modifyMovie_Menu = { string(DarkYELLOW) + " [1] Add New Movie",
		string(DarkYELLOW) + " [2] Update Movie Info*",
		string(DarkYELLOW) + " [3] Delete Movie*",
		string(DarkYELLOW) + " [0] Previous Menu" + RESET };
	modifyCust_Menu = { string(DarkYELLOW) + " [1] Add New Customer*",
		string(DarkYELLOW) + " [2] Update Customer Info*",
		string(DarkYELLOW) + " [3] Delete Customer*",
		string(DarkYELLOW) + " [0] Previous Menu" + RESET };
	*/

	base_Menu = { string(YELLOW) + " [0] Previous Menu" + RESET };
	start_Menu = { string(YELLOW) + " [1] Sign In",
		string(YELLOW) + " [0] Exit Application" + RESET };
	main_Menu = { string(YELLOW) + " [1] Display Tables",
		string(YELLOW) + " [2] Admin Actions",
		string(YELLOW) + " [0] Sign Out" + RESET };
	displayTables_Menu = { string(YELLOW) + " [A] tbl_plans",
		string(YELLOW) + " [B] tbl_moviedata",
		string(YELLOW) + " [C] tbl_actors",
		string(YELLOW) + " [D] tbl_directors",
		string(YELLOW) + " [E] tbl_genredata",
		string(YELLOW) + " [F] tbl_moviecast",
		string(YELLOW) + " [G] tbl_moviedirectors",
		string(YELLOW) + " [H] tbl_moviegenres",
		string(YELLOW) + " [I] tbl_custdata",
		string(YELLOW) + " [J] tbl_paymentinfo",
		string(YELLOW) + " [K] tbl_custactivity_stream",
		string(YELLOW) + " [L] tbl_custactivity_dvd",
		string(YELLOW) + " [M] tbl_dvdrentalhistory",
		string(YELLOW) + " [0] Previous Menu" + RESET };
	adminActions_Menu = { string(YELLOW) + " [1] Modify Movie Data",
		string(YELLOW) + " [2] Modify Customer Data",
		string(YELLOW) + " [0] Previous Menu" + RESET };
	modifyMovie_Menu = { string(YELLOW) + " [1] Add New Movie",
		string(YELLOW) + " [2] Update Movie Info*",
		string(YELLOW) + " [3] Delete Movie*",
		string(YELLOW) + " [0] Previous Menu" + RESET };
	modifyCust_Menu = { string(YELLOW) + " [1] Add New Customer*",
		string(YELLOW) + " [2] Update Customer Info*",
		string(YELLOW) + " [3] Delete Customer*",
		string(YELLOW) + " [0] Previous Menu" + RESET };
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

