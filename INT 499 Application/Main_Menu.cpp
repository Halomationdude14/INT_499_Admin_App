
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
#include "EZTechMovie_Admin_App.h"
using namespace std;


// Default Constructor
Main_Menu::Main_Menu() {
	Global_Functions fct;
	sys_msg = "";
	runInstance = true;
	userInput = 0;
	user_options = {1,2,3,4};
	main_menu = {" [1] Display Data", " [2] Modify Data", " [3] Admin Account", " [4] Sign Out"};
	valid = false;
}

// Purpose: Displays the main menu.
void Main_Menu::run() {
	runInstance = true;
	while (runInstance) {

		valid = false;
		while (valid == false) {
			userInput = 0;
			fct.displayHeader(sys_msg, main_menu);

			try {
				cout << "\nUser Input: ";
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

