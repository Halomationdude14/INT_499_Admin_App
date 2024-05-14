
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
	MySQL_Connection() db;
	Menus() menu;

	vector<vector<string>> Notifications = {};
	vector<string> sys_msg = {};
	string str = "";
	bool running = true;

	// Start the application
	while (running) {
		//menu.startScreen(sys_msg);
	}

	cout << "\n\n***** [ Closing Application ] *****\n\n";
	return 0;
}
