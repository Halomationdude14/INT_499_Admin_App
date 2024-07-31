
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <mysqlx/xdevapi.h>
using namespace std;

#include "EZTechMovie_Admin_App.h"




DB_CustData::DB_CustData() {
	// Define ANSI color codes
	TEXT =		"\033[37m";
	YELLOW =	"\033[33m";
	GREEN =		"\033[32m";
	RED =		"\033[31m";
	PURPLE =	"\033[35m";
	CYAN =		"\033[36m";
	BLUE =		"\033[34m";
	BLACK =		"\033[40m";
	
	msgs = {}; // Vector to hold all sys/err messages.
	tableData = {}; // Holds table data in <std> format to be sent to Menus object for display.
	running = true;
	input = "";
}




// Processes user requests to INSERT data to the database.  [*NOT IMPLEMENTED*]
vector<string> DB_CustData::insertCustData(mysqlx::Schema db) {
	// do something...

	return { string(GREEN) + "SYS:" + TEXT + " Functionality not implemented yet! Will be added in a future release." };
}

// Processes user requests to UPDATE data on the database.  [*NOT IMPLEMENTED*]
vector<string> DB_CustData::updateCustData(mysqlx::Schema db) {
	// do something...

	return { string(GREEN) + "SYS:" + TEXT + " Functionality not implemented yet! Will be added in a future release." };
}

// Processes user requests to DELETE data from the database.  [*NOT IMPLEMENTED*]
vector<string> DB_CustData::deleteCustData(mysqlx::Schema db) {
	// do something...

	return { string(GREEN) + "SYS:" + TEXT + " Functionality not implemented yet! Will be added in a future release." };
}

