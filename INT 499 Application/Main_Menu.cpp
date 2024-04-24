
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
	int userInput = 0;
	vector<int> menu_options{ 1,2,3,4 };
	bool valid = false;
}

// Purpose: Validate user input in main menu.
bool Main_Menu::validateInput(int num) {
	
	for (auto& i : menu_options) {
		if (num = i) {
			return true;
		}
	}
	return false;
}

// Purpose: Displays the main menu.
void Main_Menu::run() {
	userInput = 0;

	cout << endl << "####################################################################" << endl;
	cout << "## Welcome to the EZTechMovie Database Administration Application ##" << endl;
	cout << "####################################################################" << endl << endl;
	cout << "[1] Display Data" << endl;
	cout << "[2] Modify Data" << endl;
	cout << "[3] Admin Account" << endl;
	cout << "[4] Sign Out" << endl << endl;
	
	while (valid = false) {
		cout << "User Input: ";
		cin >> userInput; // rework into a try-catch
		valid = validateInput(userInput);

		if (valid = false) {
			cout << "ERROR: Invalid input! Try again." << endl;
		}
	}
	
	if (userInput = 1) {
		cout << "Display Data" << endl;
	}
	if (userInput = 2) {
		cout << "Modify Data" << endl;
	}
	if (userInput = 3) {
		cout << "Admin Account" << endl;
	}
	if (userInput = 4) {
		cout << "Sign Out" << endl;
	}
}
