
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
Initialize_Program::Initialize_Program() {
	Global_Functions fct;
	MySQL_Conn db;
	Main_Menu menu;
	sys_msg = "";
	runInstance = true;
	userInput = 0;
	user_options = {1,2};
	Username = "";
	Password = "";
	validLogin = false;
}

/*
* Purpose: Called from main.cpp to begin the program. Displays the initial greeting screen.
*/
void Initialize_Program::run() {
	while (runInstance) {
		userInput = 0;

		db.startConn(); //establish connection to MySQL database.
		
		while (true) {
			fct.clearScreen();
			displayWelcomeScreen();

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
				//cout << e.what() << endl;
				sys_msg = e.what();
				cin.clear(); // clears the error flags
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // this line discards all the input waiting in the stream
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

void Initialize_Program::displayWelcomeScreen() {
	cout << "\n##############################################################################" << endl;
	cout << "####### Welcome to the EZTechMovie Database Administration Application #######" << endl;
	cout << "##############################################################################" << endl << endl;

	if (sys_msg.length() > 0) {
		cout << sys_msg << endl << endl;
	}

	cout << " [1] Sign In" << endl;
	cout << " [2] Exit Application" << endl;
}

// Purpose: Takes in user credentials and passes it through a validation method.
void Initialize_Program::login() {
	validLogin = false;
	Username = "";
	Password = "";

	while (validLogin == false) {
		fct.clearScreen();
		cout << "\nEnter Admin Credentials to Log Into the Console -->" << endl;

		if (sys_msg.length() > 0) {
			cout << endl << sys_msg << endl;
		}

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
			//cout << e.what() << endl;
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

