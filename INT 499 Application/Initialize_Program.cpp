
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
Initialize_Program::Initialize_Program() {
	Global_Functions fct;
	sys_msg = "";
	runInstance = true;
	userInput = 0;
	user_options = {1,2};
	initial_menu = {" [1] Sign In", " [2] Exit Application"};
	login_menu = {"Enter Admin Credentials to Log Into the Console -->"};
	Username = "";
	Password = "";
	validLogin = false;
}

/*
* Purpose: Called from main.cpp to begin the program. Displays the initial greeting screen.
*/
void Initialize_Program::run() {
	Main_Menu menu;
	
	while (runInstance) {
		userInput = 0;
		
		while (true) {
			fct.displayHeader(sys_msg, initial_menu);

			try {
				cout << "\nUser Input: ";
				cin >> userInput;

				if (fct.validate_UserOption(user_options, userInput) == false) {
					throw invalid_argument("ERROR: User input was not a valid option! Try again.");
				}
				else {
					break;
				}
			}
			catch (exception& e) {
				sys_msg = e.what();
				cin.clear(); // clears the error flags
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // this line discards all the input waiting in the stream
			}
		}
		
		if (userInput == 1) {
			sys_msg = "";
			login();
			if (validLogin) {
				menu.run();
			}
		}
		if (userInput == 2) {
			runInstance = false;
		}
	}
}

// Purpose: Takes in user credentials and passes it through a validation method.
void Initialize_Program::login() {
	validLogin = false;
	Username = "";
	Password = "";

	while (validLogin == false) {
		fct.displayHeader(sys_msg, login_menu);

		// Rework: Verify username first, and then password after implementation.
		try {
			cout << "  Username: ";
			cin >> Username;
			if (Username.length() == 0) {
				throw invalid_argument("ERROR: Username cannot be <BLANK>!"); //NOT WORKING!
			}

			cout << "  Password: ";
			cin >> Password;
			if (Password.length() == 0) {
				throw invalid_argument("ERROR: Password cannot be <BLANK>!"); //NOT WORKING!
			}

			validLogin = verifyLogin(Username, Password);
		}
		catch (exception& e) {
			sys_msg = e.what();
			cin.clear(); // clears the error flags
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // this line discards all the input waiting in the stream
		}
	}
}

// Purpose: Verifies user login credentials against DB records.
bool Initialize_Program::verifyLogin(string user, string pass) {
	// Future implementation of user/pass verification requires additional setup in DB
	// cout << "Login Successful!" << endl;
	
	return true; //change to "false" after implementation
}

// Purpose: Verifies that the username is valid/exists in the DB.
bool Initialize_Program::verifyUsername() {
	//a
	return true;
}

// Purpose: Verifies that the password matches the username.
bool Initialize_Program::verifyPassword() {
	//a
	return true;
}

