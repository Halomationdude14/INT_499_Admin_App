
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


Global_Functions fct;
MySQL_Connection db;
Menus menu;
vector<string> msgs = {}; // Vector to hold all sys/err messages.
char currUI = '1'; // Depicts the current UI being displayed. Default is '1' to display the greeting screen.
char usrInput = 'a';


// Adds a vector<string> to the end of 'msgs'
void static addMsg(vector<string> message) {
	if (message.size() > 0) {
		msgs.insert(msgs.end(), message.begin(), message.end());
	}
}

// Adds a string to the end of 'msgs'
void static addMsg(string message) {
	if (message.size() > 0) {
		msgs.push_back(message);
	}
}

// Quick method to pick and choose which UI to display in the terminal.
void static callDisplayMethod() {
	vector<vector<string>> tblData = {};

	switch (currUI) {
		case 'B':
			menu.SCRN_BASE(msgs);
			break;
		case '0':
			msgs.clear();
			msgs.push_back("\n***** [ Closing Application ] *****\n");
			menu.displayMenu(msgs);
			break;
		case '1':
			if (db.getConn() == true) {
				addMsg(db.closeConn()); //Close the connection when the start screen is displayed
			}
			menu.SCRN_start(msgs);
			break;
		case '2':
			menu.SCRN_login(msgs);
			break;
		case '3':
			menu.SCRN_mainMenu(msgs);
			break;
		case '4':
			menu.SCRN_displayMenu(msgs);
			break;
		case '5':
			menu.SCRN_editMenu(msgs);
			break;
		case '6':
			menu.SCRN_adminAccount(msgs);
			break;
		case '7':
			db.setTable(usrInput);
			tblData = db.getTable();
			menu.SCRN_displayTable(msgs, tblData);
			break;
		case '8':
			db.setTable(usrInput);
			tblData = db.getTable();
			menu.SCRN_editTable(msgs, tblData);
			break;
		default:
			string s(1, currUI);
			string str = "CRITICAL ERROR: CODE MALFUNCTION! Program tried to call non-existent UI with ID = [" + s + "]. Displaying previous UI!";
			addMsg(str);
			currUI = menu.getCurrMenu(); //may need to change this to menu.getPrevMenu() eventually
			break;
	}
}

// Processes a char through Menus.cpp and updates the current UI based on the user's selection.
void static processUserInput(char input) {
	char c = 'x';
	
	/*
	* Each case represents a specific UI.
	* Once the UI is determined, a call is made to process the user's input based on the available options for that UI.
	* The only exception for this is the login screen (case 2).
	* If the user's input was valid, the currUI will be updated via the RETURN.
	*/
	switch (currUI) {
		case 'B': //base screen
			c = menu.SLCT_BASE(input);
			break;
		case '0': //EXIT PROGRAM
			break; //do nothing; main() will handle this
		case '1': //start screen
			c = menu.SLCT_start(input);
			break;
		case '2': //login screen
			addMsg(db.login());
			if (db.getConn() == true) {
				c = '3';
			}
			else {
				c = '1';
			}
			break;
		case '3': //main menu
			c = menu.SLCT_mainMenu(input);
			break;
		case '4': //display menu
			c = menu.SLCT_displayMenu(input);
			break;
		case '5': //edit menu
			c = menu.SLCT_editMenu(input);
			break;
		case '6': //admin account
			c = menu.SLCT_adminAccount(input);
			break;
		case '7':
			c = menu.SLCT_displayTable(input);
			break;
		case '8':
			c = menu.SLCT_editTable(input);
			break;
		default:
			break;
	}

	if (c == 'x') {
		string s(1, input);
		string str = "ERROR: User input [" + s + "] is invalid!";
		addMsg(str);
	}
	else {
		currUI = c;
	}
}

// Purpose: Main Function
int main() {
	bool running = true;

	// Start the application
	while (running) {
		// Stop program if currUI is ever set to 0.
		if (currUI == '0') {
			running = false;
		}

		callDisplayMethod();
		msgs.clear();

		// Don't call getUsrInput() if the login UI is displayed, or if the program is closing
		if (!(currUI == '0') && !(currUI == '2')) {
			usrInput = fct.getUsrInput();
		}

		processUserInput(usrInput);
	}
	return 0;
}

