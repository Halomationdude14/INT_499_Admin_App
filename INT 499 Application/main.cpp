
/*
INT 499 Capstone for Information Technology
Interactive Assignment
Date: 2024-04-22
Author: Paul Oram
NOTE: This is a modified version of the original code that has been reworked to integrate into the final project (MySQL DB).
*/

#include <iostream>
#include <string>
using namespace std;

#include "EZTechMovie_Admin_App.h"


// Purpose: Main Function
int main() {
	Global_Functions fct;
	Initialize_Program newInstance;
	string userInput = "";
	bool validLogin = false;

	while (userInput != "exit") {
		userInput = "";
		validLogin = false;

		while (validLogin = false) {
			validLogin = newInstance.run();
		}

		// enter main menu.
	}

	return 0;
}
