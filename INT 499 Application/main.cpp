
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
	Initialize_Program newInstance;

	// Admin credentials will be verified through the DB*
	auto User = ""; // Note that the user can login using either their Username or Email address.
	auto Pass = "";

	cout << endl << "####################################################################" << endl;
	cout << "## Welcome to the EZTechMovie Database Administration Application ##" << endl;
	cout << "####################################################################" << endl;
	cout << "\nEnter Admin Credentials to Log Into the Console -->" << endl;

	newInstance.login(User, Pass);

	return 0;
}
