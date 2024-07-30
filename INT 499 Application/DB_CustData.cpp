
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <mysqlx/xdevapi.h>
using namespace std;

#include "EZTechMovie_Admin_App.h"


// Define ANSI color codes based on Dracula theme
constexpr auto BOLD = "\033[1m";
constexpr auto TEXT = "\033[38;2;248;248;242m";
constexpr auto BLACK = "\033[38;2;33;34;44m";
constexpr auto BLUE = "\033[38;2;189;147;249m";
constexpr auto CYAN = "\033[38;2;139;233;253m";
constexpr auto GREEN = "\033[38;2;80;250;123m";
constexpr auto PURPLE = "\033[38;2;255;121;198m";
constexpr auto RED = "\033[38;2;255;85;85m";
constexpr auto YELLOW = "\033[38;2;241;250;140m";


DB_CustData::DB_CustData() {
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

