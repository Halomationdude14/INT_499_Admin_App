
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
Start_Program::Start_Program() {
	sys_msg = {};
	runInstance = true;
	userInput = 0;
	user_options = {1,2};
	menu_options = {" [1] Sign In"," [2] Exit Application"};
	Username = "";
	Password = "";
	dbConn = false;
	validLogin = false;
}

/*
* Purpose: Called from main.cpp to begin the program. Displays the initial greeting screen.
*/
void Start_Program::run() {
	while (runInstance) {
		userInput = 0;

		// Establish connection to MySQL database.
		//dbConn = db.startConnection();
		
		// While there exists a successful connection to the database...
		while (dbConn) {
			fct.addMsg(sys_msg);
			sys_msg.clear();
			fct.displayHeader(menu_options);

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
				sys_msg.push_back(e.what());
				cin.clear(); // clears the error flags
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // this line discards all the input waiting in the stream
			}
		}
		
		// Main Menu
		if (userInput == 1) {
			login();
			if (validLogin) {
				menu.run();
			}
		}
		// Close the app
		if (userInput == 2) {
			sys_msg.clear();
			Username = "";
			Password = "";
			runInstance = false;
		}
	}
}

// Purpose: Takes in user credentials and passes it through a validation method.
void Start_Program::login() {
	validLogin = false;
	Username = "";
	Password = "";

	while (validLogin == false) {
		fct.addMsg(sys_msg);
		sys_msg.clear();

		vector<string> empty = {};
		fct.displayHeader(empty);

		cout << "\nEnter Admin Credentials to Log Into the Console -->" << endl;

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
			sys_msg.push_back(e.what());
			cin.clear(); // clears the error flags
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // this line discards all the input waiting in the stream
		}
	}
	sys_msg.clear();
}

// Purpose: Verifies user login credentials against DB records.
bool Start_Program::verifyLogin(string user, string pass) {
	// Future implementation of user/pass verification requires additional setup in DB
	sys_msg.push_back("SYS: Login Successful!");
	fct.addMsg(sys_msg);
	return true; //change to "false" after implementation
}

// Purpose: Verifies that the username is valid/exists in the DB.
bool Start_Program::verifyUsername() {
	//a
	return true;
}

// Purpose: Verifies that the password matches the username.
bool Start_Program::verifyPassword() {
	//a
	return true;
}

