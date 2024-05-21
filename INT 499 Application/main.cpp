
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

// Method to quickly add any sys/err message from "message" to "list" if there are any.
vector<string> static addMsg(vector<string> list, vector<string> message) {
	if (message.size() > 0) {
		list.insert(list.end(), message.begin(), message.end());
	}

	return list;
}

// Quick method to pick and choose which UI to display in the terminal.
vector<string> static callDisplayMethod(Menus m, vector<string> list, char UI) {
	vector<string> msg = {};

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
			msg.push_back("TEST [callDisplayMethod()]: case 4 = display");
			break;
		case '5':
			//m.SCRN.edit(list);
			msg.push_back("TEST [callDisplayMethod()]: case 5 = edit");
			break;
		case '6':
			//m.SCRN.adminAccount(list);
			msg.push_back("TEST [callDisplayMethod()]: case 6 = Admin Account");
			break;
		default:
			string s(1, UI);
			string str = "CRITICAL ERROR: CODE MALFUNCTION! Program tried to call non-existent UI with ID = [" + s + "]. Displaying previous UI!";
			msg.push_back(str);
			break;
	}
	return msg;
}

// Purpose: Main Function
int main() {
	Global_Functions fct;
	MySQL_Connection db;
	Menus menu;
	vector<string> msgs = {}; // Vector to hold all sys/err messages.
	vector<string> temp_msg = {}; // Messages from other classes are temporarily stored in this vector before being transfered to the end of "msgs".
	char currUI = '1'; // Depicts the current UI being displayed. Default is '1' to display the greeting screen.
	char usrInput = 'a';
	bool running = true;
	

	// Start the application
	while (running) {
		temp_msg = callDisplayMethod(menu, msgs, currUI);
		msgs.clear();
		msgs = addMsg(msgs, temp_msg);

		// Do not obtain user input the standard way if the login screen is displayed.
		if (!(currUI == '0') && !(currUI == '2')) {
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
					temp_msg = db.closeConn();
				}
				currUI = menu.SLCT_start(usrInput);
				break;
			case '2': //login screen
				temp_msg = db.login();
				if (db.getConn() == true) {
					currUI = '3';
				}
				break;
			case '3': //main menu
				currUI = menu.SLCT_mainMenu(usrInput);
				break;
			case '4': //display
				//currUI = menu
				currUI = '3'; //delete*
				break;
			case '5': //edit
				//currUI = menu
				currUI = '3'; //delete*
				break;
			case '6': //admin account
				//currUI = menu
				currUI = '3'; //delete*
				break;
			default:
				//currUI = menu?
				//currUI = menu.getCurrMenuNum(); //delete*
				break;
		}

		msgs = addMsg(msgs, temp_msg);
	}

	msgs.push_back("\n***** [ Closing Application ] *****\n");
	menu.displayMenu(msgs);
	return 0;
}

