
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

// Purpose: Main Function
int main() {
	Global_Functions fct;
	MySQL_Connection db;
	Menus menu;

	//vector<vector<string>> msgList = {};
	vector<string> msgs = {};
	string str;
	char usrInput;
	bool running = true;

	// Start the application
	while (running) {
		str = "";
		usrInput = 'x';

		menu.SCRN_start(msgs);
		msgs.clear();
		usrInput = fct.getUsrInput();
		msgs = fct.validate_UserOption(menu.getCurrMenu(), usrInput);

		if (msgs.size() > 0) {
			break;
		}
		else {
			//Put a switch here!
		}
	}

	cout << "\n\n***** [ Closing Application ] *****\n\n";
	return 0;
}
