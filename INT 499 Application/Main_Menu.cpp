
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
	Global_Functions fct;
	runInstance = true;
	userInput = 0;
	user_options = {1,2,3,4};
	valid = false;
}

// Purpose: Displays the main menu.
void Main_Menu::run() {
	runInstance = true;
	while (runInstance) {
		cout << "\n##############################################################################" << endl;
		cout << "####### Welcome to the EZTechMovie Database Administration Application #######" << endl;
		cout << "##############################################################################" << endl << endl;
		cout << " [1] Display Data" << endl;
		cout << " [2] Modify Data" << endl;
		cout << " [3] Admin Account" << endl;
		cout << " [4] Sign Out" << endl << endl;

		valid = false;
		while (valid == false) {
			userInput = 0;

			try {
				cout << "User Input: ";
				cin >> userInput;

				if (fct.validate_UserOption(user_options, userInput) == false) {
					throw invalid_argument("ERROR: User input was not a valid option! Try again.");
				}
				else {
					valid = true;
				}
			}
			catch (exception& e) {
				cout << e.what() << endl;
				cin.clear(); // clears the error flags
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // this line discards all the input waiting in the stream
			}
		}

		if (userInput == 1) {
			cout << "Display Data" << endl;
			break;
		}
		if (userInput == 2) {
			cout << "Modify Data" << endl;
			break;
		}
		if (userInput == 3) {
			cout << "Admin Account" << endl;
			break;
		}
		if (userInput == 4) {
			cout << "Sign Out" << endl;
			runInstance = false;
		}
	}
}
