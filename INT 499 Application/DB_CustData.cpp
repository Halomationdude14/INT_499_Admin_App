
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <mysqlx/xdevapi.h>
using namespace std;

#include "EZTechMovie_Admin_App.h"


DB_CustData::DB_CustData() {
	msgs = {}; // Vector to hold all sys/err messages.
	tableData = {}; // Holds table data in <std> format to be sent to Menus object for display.
	running = true;
	input = "";
}




// Processes user requests to INSERT data to the database
void DB_CustData::insertCustData() {
	// do something...
}

// Processes user requests to UPDATE data on the database
void DB_CustData::updateCustData() {
	// do something...
}

// Processes user requests to DELETE data from the database
void DB_CustData::deleteCustData() {
	// do something...
}

