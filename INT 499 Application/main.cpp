
/*
INT 499 Capstone for Information Technology
Interactive Assignment
Date: 2024-04-22
Author: Paul Oram
NOTE: This is a modified version of the original code that has been reworked to integrate into the final project (MySQL DB).
*/

#include <iostream>
#include <vector>
#include <mysqlx/xdevapi.h>
using namespace std;

#include "EZTechMovie_Admin_App.h"


Global_Functions fct;
Menus menu;
vector<string> msgs = {}; // Vector to hold all sys/err messages.
char currUI = '1'; // Depicts the current UI being displayed. Default is '1' to display the greeting screen.
char usrInput = 'x';
bool running = true;
bool conn = false;
string User = "";
string Pass = "";
string currTbl = "";
vector<vector<string>> tableData = {}; // Holds table data in <std> format to be sent to Menus object for display.


// Adds a vector<string> to the end of 'msgs'
void static addMsg(vector<string> message) {
	if (message.size() > 0) {
		msgs.insert(msgs.end(), message.begin(), message.end());
	}
}

// Adds a string to the end of 'msgs'
void static addMsg(string message) {
	if (message.size() > 0) {
		msgs.push_back(message);
	}
}

// Performs a check to see if the username and password are valid for a connection to the MySQL server.
bool static verifyLogin() {
	try {
		cout << "Login to the EZTechMovie MySQL Server -->\n\n";
		cout << "Username: ";
		getline(cin, User);
		cout << "Password: ";
		getline(cin, Pass);

		mysqlx::Session sess = mysqlx::getSession("localhost", 33060, User, Pass);
		msgs.push_back("SYS [MySQL]: Connection to MySQL server successful!");
		sess.close();
		return true;
	}
	catch (const mysqlx::Error& err) {
		msgs.push_back("MYSQLX_ERROR [verifyLogin()]: " + std::string(err.what()));
		return false;
	}
	catch (std::exception& ex) {
		msgs.push_back("ERROR [verifyLogin()]: " + std::string(ex.what()));
		return false;
	}
}

// Assign the name of the chosen table to 'currTbl'
void static setTableName(char input) {

	switch (input) {
	case '1':
		currTbl = "tbl_plans";
		break;
	case '2':
		currTbl = "tbl_actors";
		break;
	case '3':
		currTbl = "tbl_custdata";
		break;
	case '4':
		currTbl = "tbl_moviedata";
		break;
	case '5':
		currTbl = "tbl_paymentinfo";
		break;
	case '6':
		currTbl = "tbl_directors";
		break;
	case '7':
		currTbl = "tbl_genredata";
		break;
	case '8':
		currTbl = "tbl_moviedirectors";
		break;
	case '9':
		currTbl = "tbl_moviegenres";
		break;
	case '10':
		currTbl = "tbl_moviecast";
		break;
	case '11':
		currTbl = "tbl_custactivity_dvd";
		break;
	case '12':
		currTbl = "tbl_custactivity_stream";
		break;
	case '13':
		currTbl = "tbl_dvdrentalhistory";
		break;
	default:
		currTbl = "";
		msgs.push_back("ERROR [MySQL|setTable()]: Table does not exist in the database!");
		break;
	}
}

// Converts <mysqlx::RowResult> to vector<vector<std::string>> format
static void getTableData(mysqlx::Table table) {
	try {
		mysqlx::RowResult result = table.select("*").execute();

		for (mysqlx::Row row : result) {
			vector<string> rowData;
			for (int i = 0; i < row.colCount(); ++i) {
				mysqlx::Value val = row[i];
				string strValue;

				switch (val.getType()) {
				case mysqlx::Value::Type::UINT64:
					strValue = to_string(val.get<uint64_t>());
					break;
				case mysqlx::Value::Type::INT64:
					strValue = to_string(val.get<int64_t>());
					break;
				case mysqlx::Value::Type::FLOAT:
					strValue = to_string(val.get<float>());
					break;
				case mysqlx::Value::Type::DOUBLE:
					strValue = to_string(val.get<double>());
					break;
				case mysqlx::Value::Type::BOOL:
					strValue = to_string(val.get<bool>());
					break;
				case mysqlx::Value::Type::STRING:
					strValue = val.get<std::string>();
					break;
				case mysqlx::Value::Type::VNULL:
					strValue = "<NULL>";
					break;
				default:
					strValue = "<ERR>";
					break;
				}

				rowData.push_back(strValue);
			}
			tableData.push_back(rowData);
		}
	}
	catch (const mysqlx::Error& err) {
		msgs.push_back("MYSQLX_ERROR [getTableData()]: " + std::string(err.what()));
	}
	catch (std::exception& ex) {
		msgs.push_back("ERROR [getTableData()]: " + std::string(ex.what()));
	}
}

// Quick method to pick and choose which UI to display in the terminal.
void static callDisplayMethod() {

	switch (currUI) {
		case 'B': //base menu
			menu.SCRN_BASE(msgs);
			break;
		case '0': //EXIT PROGRAM
			msgs.clear();
			msgs.push_back("\n***** [ Closing Application ] *****\n");
			menu.displayMenu(msgs);
			break;
		case '1': //start menu
			menu.SCRN_start(msgs);
			break;
		case '2': //login screen
			menu.SCRN_login(msgs);
			break;
		case '3': //main menu
			menu.SCRN_mainMenu(msgs);
			break;
		case '4': //display menu
			menu.SCRN_displayMenu(msgs);
			break;
		case '5': //edit menu
			menu.SCRN_editMenu(msgs);
			break;
		case '6': //admin account
			menu.SCRN_adminAccount(msgs);
			break;
		case '7': //display table
			menu.SCRN_displayTable(msgs, tableData);
			break;
		case '8': //edit table
			menu.SCRN_editTable(msgs, tableData);
			break;
		default:
			string s(1, currUI);
			string str = "CRITICAL ERROR: CODE MALFUNCTION! Program tried to call non-existent UI with ID = [" + s + "]. Displaying previous UI!";
			addMsg(str);
			currUI = menu.getCurrMenu(); //may need to change this to menu.getPrevMenu() eventually
			break;
	}
	msgs.clear();
}

// Processes a char through Menus.cpp and updates the current UI based on the user's selection.
void static processUserInput(char input) {
	char c = 'x';
	
	/*
	* Each case represents a specific UI.
	* Once the UI is determined, a call is made to process the user's input based on the available options for that UI.
	* The only exception for this is the login screen (case 2).
	* If the user's input was valid, the currUI will be updated via the RETURN.
	*/
	switch (currUI) {
		case 'B': //base screen
			c = menu.SLCT_BASE(input);
			break;
		case '0': //EXIT PROGRAM
			break; //do nothing; main() will handle this
		case '1': //start screen
			c = menu.SLCT_start(input);
			break;
		case '2': //login screen
			if (conn == true) {
				c = '3';
			}
			else {
				c = '1';
			}
			break;
		case '3': //main menu
			c = menu.SLCT_mainMenu(input);
			break;
		case '4': //display menu
			c = menu.SLCT_displayMenu(input);
			break;
		case '5': //edit menu
			c = menu.SLCT_editMenu(input);
			break;
		case '6': //admin account
			c = menu.SLCT_adminAccount(input);
			break;
		case '7': //display table
			c = menu.SLCT_displayTable(input);
			break;
		case '8': //edit table
			c = menu.SLCT_editTable(input);
			break;
		default:
			break;
	}

	if (c == 'x') {
		string s(1, input);
		string str = "ERROR: User input [" + s + "] is invalid!";
		addMsg(str);
	}
	else {
		if (currUI == '4' || currUI == '5') {
			setTableName(input);
		}
		currUI = c;
	}
}




// Purpose: Main Function
int main() {

	// Start the application
	while (running) {
		usrInput = 'x'; //reset user input to avoid possible mis-inputs.
		

		callDisplayMethod();

		if (currUI == '0') { //stop program
			running = false;
		}
		else if (currUI == '2') { //perform login
			conn = verifyLogin();
			if (conn == false) {
				msgs.push_back("SYS [MySQL]: Could not establish connection to MySQL server!");
			}
		}
		else {
			usrInput = fct.getUsrInput();
		}

		processUserInput(usrInput);

		// Create connection to MySQL server
		while (conn) {
			usrInput = 'x'; //reset user input to avoid possible mis-inputs.
			tableData.clear(); //clear variable to avoid displaying a table previously displayed.

			try {
				mysqlx::Session sess = mysqlx::getSession("localhost", 33060, User, Pass);
				mysqlx::Schema db = sess.getSchema("eztechmoviedb");
				//vector<mysqlx::Table> tblList = db.getTables(); //stores all tables in the database in this single vector
				
				if (currUI == '1') { //stop program
					msgs.push_back("SYS [MySQL]: Connection to MySQL server closed.");
					User = "";
					Pass = "";
					currTbl = "";
					conn = false;
				}
				
				if (currUI == '7' || currUI == '8') { //If UI is in "edit/display mode"
					mysqlx::Table tbl = db.getTable(currTbl);
					getTableData(tbl);
				}

				callDisplayMethod();
				usrInput = fct.getUsrInput();
				processUserInput(usrInput); //table name set if [UI == 4 OR 5] AND user input was valid

				sess.close(); //close the Session object to avoid errors
			}
			catch (const mysqlx::Error& err) {
				msgs.push_back("MYSQLX_ERROR [main()]: " + std::string(err.what()));
			}
			catch (std::exception& ex) {
				msgs.push_back("ERROR [main()]: " + std::string(ex.what()));
			}
		}
	}
	return 0;
}

