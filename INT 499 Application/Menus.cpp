
#include <iostream>
#include <string>
#include <exception>
using namespace std;

#include "EZTechMovie_Admin_App.h"


Menus::Menus() {
	tempStr = "";
	startMenu = {" [1] Sign In"," [2] Exit Application"};
	startMenu_Options = {1,2};
	mainMenu = {" [1] Display Data"," [2] Modify Data"," [3] Admin Account"," [4] Sign Out"};
	mainMenu_Options = {1,2,3,4};
}

void Menus::displayHeader(vector<string> msg, vector<string> menu) {
	fct.clearScreen();

	cout << "\n##############################################################################" << endl;
	cout << "####### Welcome to the EZTechMovie Database Administration Application #######" << endl;
	cout << "##############################################################################" << endl << endl;

	// Display sys/err messages if the array is not empty.
	if (msg.size() > 0) {
		for (auto& i : msg) {
			cout << i << endl;
		}
	}

	// Display menu options.
	for (auto& i : menu) {
		cout << i << endl;
	}
}

void Menus::startScreen(vector<string> msg) {
	displayHeader(msg, startMenu);
}

void Menus::loginScreen(vector<string> msg) {
	vector<string> empty = {};
	displayHeader(msg, empty);
}

void Menus::mainMenu(vector<string> msg) {
	displayHeader(msg, mainMenu);
}

