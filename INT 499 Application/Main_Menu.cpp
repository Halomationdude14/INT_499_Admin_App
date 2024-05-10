
/*
INT 499 Capstone for Information Technology
Interactive Assignment
Date: 2024-04-22
Author: Paul Oram
NOTE: This is a modified version of the original code that has been reworked to integrate into the final project (MySQL DB).
*/

#include <iostream>
#include <string>
#include <exception>
#include <vector>
using namespace std;

#include "EZTechMovie_Admin_App.h"


// Default Constructor
Main_Menu::Main_Menu() {
	sys_msg = "";
	runInstance = true;
	userInput = 0;
	user_options = {1,2,3,4};
	valid = false;
}

// Purpose: Displays the main menu.
void Main_Menu::run() {
	runInstance = true;
	while (runInstance) {

		valid = false;
		while (valid == false) {
			userInput = 0;
			fct.clearScreen();
			displayMainMenu();

			try {
				cout << "User Input: ";
				cin >> userInput;

				if (fct.validate_UserOption(user_options, userInput) == false) {
					throw invalid_argument("ERROR: User input was not a valid option! Try again.");
				}
				else {
					sys_msg = "";
					valid = true;
				}
			}
			catch (exception& e) {
				sys_msg = e.what();
				cin.clear(); // clears the error flags
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // this line discards all the input waiting in the stream
			}
		}

		if (userInput == 1) {
			sys_msg = "INFO: Display Data";
		}
		if (userInput == 2) {
			sys_msg = "INFO: Modify Data";
		}
		if (userInput == 3) {
			sys_msg = "INFO: Admin Account";
		}
		if (userInput == 4) {
			runInstance = false;
		}
	}
}

void Main_Menu::displayMainMenu() {
	cout << "\n##############################################################################" << endl;
	cout << "####### Welcome to the EZTechMovie Database Administration Application #######" << endl;
	cout << "##############################################################################" << endl << endl;

	if (sys_msg.length() > 0) {
		cout << sys_msg << endl << endl;
	}

	cout << " [1] Display Data" << endl;
	cout << " [2] Modify Data" << endl;
	cout << " [3] Admin Account" << endl;
	cout << " [4] Sign Out" << endl << endl;
}

