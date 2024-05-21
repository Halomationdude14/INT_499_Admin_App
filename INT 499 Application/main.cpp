
/*
INT 499 Capstone for Information Technology
Interactive Assignment
Date: 2024-04-22
Author: Paul Oram
NOTE: This is a modified version of the original code that has been reworked to integrate into the final project (MySQL DB).
*/

#include <iostream>
#include <vector>
using namespace std;

#include "EZTechMovie_Admin_App.h"

// Quick method to pick and choose which UI to display in the terminal.
void static callDisplayMethod(Menus m, vector<string> list, char UI) {
	//*delete when code-complete
	char c = 'x';
	c = m.getCurrMenuNum();
	string str = "";
	//*

	switch (UI) {
		case '0':
			break; //Send back to main() to exit program.
		case '1':
			m.SCRN_start(list);
			break;
		case '2':
			m.SCRN_login(list);
			break;
		case '3':
			m.SCRN_mainMenu(list);
			break;
		case '4':
			//m.SCRN.display(list);
			str = "TEST [main|callDispMeth()]: case '4' --> Displaying previous UI!; ";
			list.clear();
			list.push_back(str);
			callDisplayMethod(m, list, c);
			break;
		case '5':
			//m.SCRN.edit(list);
			str = "TEST [main|callDispMeth()]: case '5' --> Displaying previous UI!; ";
			list.clear();
			list.push_back(str);
			callDisplayMethod(m, list, c);
			break;
		case '6':
			//m.SCRN.adminAccount(list);
			str = "TEST [main|callDispMeth()]: case '6' --> Displaying previous UI!; ";
			list.clear();
			list.push_back(str);
			callDisplayMethod(m, list, c);
			break;
		default:
			string s(1, UI);
			str = "CRITICAL ERROR: CODE MALFUNCTION! Program tried to call non-existent UI with ID = [" + s + "]. Displaying previous UI!";
			list.clear();
			list.push_back(str);
			callDisplayMethod(m, list, c);
			break;
	}
}

// Processes the user's input based on the current UI being displayed.
/*
char static processUserSelection(Menus m, char UI, char input) {

	switch (UI) {
		case '0': //EXIT PROGRAM
			return '0';
			break;
		case '1': //start screen
			return m.SLCT_start(input);
			break;
		case '2': //login screen
			//currUI = db.login();
			//return a value. Set 'currUI' based on that value.
			break;
		case '3': //main menu
			return m.SLCT_mainMenu(input);
			break;
		case '4': //display
			//return ?
			break;
		case '5': //edit
			//return ?
			break;
		case '6': //admin account
			//return ?
			break;
		default:
			//return ?
			break;
	}
}
*/

// Purpose: Main Function
int main() {
	Global_Functions fct;
	MySQL_Connection db;
	Menus menu;
	vector<string> msgs = {}; // Vector to temporarily hold sys/err messages generated from other classes.
	string str;
	char currUI = '0'; // Depicts the current UI being displayed. Default is '0' to display the greeting screen.
	char usrInput = '0';
	bool running = true;
	

	// Start the application
	while (running) {
		str = "";

		callDisplayMethod(menu, msgs, currUI);
		msgs.clear();

		// Do not obtain user input the standard way if the login screen is displayed.
		if (!currUI == '2') {
			usrInput = fct.getUsrInput();
		}

		/*
		* Each case represents a specific UI.
		* Once the UI is determined, a call is made to process the user's input based on the available options for that UI.
		* The only exception for this is the login screen (case 2).
		* If the user's input was valid, the currUI will be updated via the RETURN.
		*/
		switch (currUI) {
			case '0': //EXIT PROGRAM
				running = false;
				break;
			case '1': //start screen
				if (db.getConn() == true) {
					msgs = db.closeConn(); //need to close the actual connection*
				}

				currUI = menu.SLCT_start(usrInput);
				break;
			case '2': //login screen
				msgs = db.login();

				if (db.getConn() == true) {
					currUI = '3';
				}
				break;
			case '3': //main menu
				currUI = menu.SLCT_mainMenu(usrInput);
				break;
			case '4': //display
				//currUI = menu.
				currUI = menu.getCurrMenuNum(); //delete*
				break;
			case '5': //edit
				//currUI = menu.
				currUI = menu.getCurrMenuNum(); //delete*
				break;
			case '6': //admin account
				//currUI = menu.
				currUI = menu.getCurrMenuNum(); //delete*
				break;
			default:
				//currUI = menu.
				currUI = menu.getCurrMenuNum(); //delete*
				break;
		}
	}

	msgs.push_back("\n***** [ Closing Application ] *****\n\n");
	menu.displayMenu(msgs);
	//cout << "\n***** [ Closing Application ] *****\n\n";
	return 0;
}

