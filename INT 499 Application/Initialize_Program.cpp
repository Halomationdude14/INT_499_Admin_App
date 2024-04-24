
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
	string Username = "";
	string Password = "";
	bool valid = false;
}

/*
* Purpose: Called from main.cpp to begin the program.Displays the initial greeting screen.
* Takes in user credentials and passes it through a validation method.
*/
bool Initialize_Program::run() {
	cout << endl << "####################################################################" << endl;
	cout << "## Welcome to the EZTechMovie Database Administration Application ##" << endl;
	cout << "####################################################################" << endl << endl;
	cout << "\nEnter Admin Credentials to Log Into the Console -->" << endl;

	cout << "Username: ";
	cin >> Username;
	cout << "Password: ";
	cin >> Password;

	valid = verifyLogin(Username, Password);

	if (valid = true) {
		return true;
	}
	return false;
}

// Purpose: Verifies user login credentials against DB records.
bool Initialize_Program::verifyLogin(string user, string pass) {
	// Future implementation
	// Requires setup in DB
	// Error handling: ensure more than 1 char

	return true; //change to "false" after implementation
}
