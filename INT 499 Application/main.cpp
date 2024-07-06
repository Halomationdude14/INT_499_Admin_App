
/*
* 
* Author: Paul M. Oram
* Date Started: 2024-04-22
* Last Updated: 2024-07-05
* Purpose: Sample terminal program to demonstrate how to use the <mysqlx/xdevapi.h> library which allows interaction with a MySQL server/database.
* 
*/

#include <iostream>
#include <vector>
#include <mysqlx/xdevapi.h>
using namespace std;

#include "EZTechMovie_Admin_App.h"


/*
* Admin App TO-DO List -->
* 
* 2. [Global_Functions.cpp] Provide search function for large tables (i.e., tables with 50+ entries).
	 Should be available in both "Display Tables" menu/UI and during "add new movie" process which is why this function exists in the 'Global_Functions.cpp' class.
* 3. Improve how tables are displayed.
* 4. [main.cpp] "char usrInput" -> Can only hold 1 value (0-9) (A-Z). What if UI has two digits (i.e., 10, 11, 12, etc...)? Change from char to int or string?
	- Also, need to have two default values for this var: one value for ERROR (i.e, 'X'), and one neutral value (i.e., '*').
* 5. Add functionality -> when user chooses to close app, close window and remove closing text from terminal.
* 6. In places where the user is NOT required to press the <ENTER> key to submit their input, remove the text "User Input: " to avoid confusion. Ensure that this text is kept in places where manual entry via <ENTER> key is required.
* 7. At the login screen, when user is entering password, DON'T display the password as they type. Instead, display an asterisk for each char typed (*).
* 8. For any user entry line that takes in a value automatically, if user presses <ENTER> without entering any other values, the error msg is displayed weird " ] is invalid!nput [ ".
* 
* 
* Admin App Considerations -->
* 
* 1. In places where the user is NOT required to press the <ENTER> key to submit their input, remove the text "User Input: " to avoid confusion.
Ensure that this text is kept in places where manual entry via <ENTER> key is required.
* 2. Instead of typing a single character to navigate through the menus, use arrow keys to select different menu options.
* 3. Add color/decoration to text to make app more vivid.
* 
* 
* Other TO-DO Items -->
* 
* 1. Need to add VIEWs to the MySQL database. These views would drastically improve the readability of all relational tables.
* 
*/

/*
* Online References/Sources that Aided in the Development of this Program -->
* 
* 1. MySQL Connector/C++ Official Documentation: https://dev.mysql.com/doc/dev/connector-cpp/latest/
* 2. MySQL Connector/C++ 9.0 Developer Guide: https://dev.mysql.com/doc/connector-cpp/9.0/en/
* 3. [xdevapi.h] File: https://github.com/mysql/mysql-connector-cpp/blob/trunk/include/mysqlx/xdevapi.h
* 4. DevApi Reference text file from author (code examples included in this repo): https://github.com/mysql/mysql-connector-cpp/blob/trunk/doc/devapi_ref.txt
* 5. Sample code demonstrating how to use the modern version of the <xdevapi> library: https://stackoverflow.com/questions/75135560/x-devapi-batch-insert-extremely-slow
* 
*/


Global_Functions fct;		// Object assists in generic processes throughout program. Simple, general-use functions.
Menus menu;					// Object assists in displaying information to the terminal screen.
DB_MovieData movie;			// Allows for manipulation of "tbl_moviedata".
DB_CustData cust;			// Allows for manipulation of "tbl_custdata".
vector<string> msgs = {};	// Stores all SYS/ERR notifications: to be displayed below the header.
char currUI = '1';			// Value corresponds to the current UI being displayed. Default is '1' to display the greeting screen.
char usrInput = 'X';		// Stores value entered by user. Used for navigating through the menus. Default is 'X' -> this value throws an error if returned.
bool running = true;		// Used by loops in main(): true = loop | false = don't loop.
bool conn = false;			// Indicates status of connection to MySQL Server/Database: true = connection | false = no connection.
bool edit_mode = false;		// Used in Admin_Actions menu when user is presented with INSERT/UPDATE/DELETE options. Set to FALSE immediately after those options are no longer displayed.
string User = "";
string Pass = "";
string currTbl = "NULL";	// Stores the name of the table that is either currently being displayed or will be displayed next.
vector<vector<string>> tableData = {}; // vector<vector<string>> var that stores converted table data from the database; can be sent to Menus object for display.




// Adds any messages in [message] to the end of [msgs].
void static addMsg(vector<string> message) {
	if (message.size() > 0) {
		msgs.insert(msgs.end(), message.begin(), message.end());
	}
}

// Adds a string to the end of [msgs].
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

		/*
		* Create a 'Session' object that attempts to establish a connection to a locally stored MySQL server.
		* NOTE: If user desires to connect to a cloud-based MySQL server, additional configuration options will need to be implemented.
		*		Currently, this program is designed to only connect to locally stored MySQL servers.
		*/
		mysqlx::Session sess = mysqlx::getSession("localhost", 33060, User, Pass);

		addMsg("SYS: Connection to MySQL server successful!");
		
		sess.close(); // Close the connection to avoid errors.

		return true;
	}

	catch (const mysqlx::Error& err) {
		addMsg("MYSQLX_ERROR [verifyLogin()]: " + string(err.what()));
		return false;
	}
	catch (exception& ex) {
		addMsg("EXCEPTION [verifyLogin()]: " + string(ex.what()));
		return false;
	}
}

// When in the 'Display Table' menus, this function assigns the name of the chosen table to [currTbl].
void static setTableName() {

	switch (usrInput) {
		case 'A':
			currTbl = "tbl_plans";
			break;
		case 'B':
			currTbl = "tbl_moviedata";
			break;
		case 'C':
			currTbl = "tbl_actors";
			break;
		case 'D':
			currTbl = "tbl_directors";
			break;
		case 'E':
			currTbl = "tbl_genredata";
			break;
		case 'F':
			currTbl = "tbl_moviecast";
			break;
		case 'G':
			currTbl = "tbl_moviedirectors";
			break;
		case 'H':
			currTbl = "tbl_moviegenres";
			break;
		case 'I':
			currTbl = "tbl_custdata";
			break;
		case 'J':
			currTbl = "tbl_paymentinfo";
			break;
		case 'K':
			currTbl = "tbl_custactivity_stream";
			break;
		case 'L':
			currTbl = "tbl_custactivity_dvd";
			break;
		case 'M':
			currTbl = "tbl_dvdrentalhistory";
			break;
		case '0':
			currTbl = "NULL";
			break;
		default:
			currTbl = "NULL";
			break;
	}
}

// Quick method to pick and choose which UI to display in the terminal.
void static callDisplayMethod() {
	usrInput = 'X';

	switch (currUI) {
		case '1': // Welcome screen
			menu.SCRN_start(msgs);
			msgs.clear();
			usrInput = fct.getUsrInput();
			break;
		case '2': // Login screen
			menu.SCRN_login(msgs);
			msgs.clear();
			conn = verifyLogin();
			if (conn == false) {
				addMsg("SYS: Could not establish connection to MySQL server!");
			}
			break;
		case '3': // Main Menu
			menu.SCRN_mainMenu(msgs);
			msgs.clear();
			usrInput = fct.getUsrInput();
			break;
		case '4': // Display Tables menu
			menu.SCRN_displayMenu(msgs);
			msgs.clear();
			usrInput = fct.getUsrInput();
			break;
		case '5': // Display Table
			// Verify that [tableData] is not empty before attempting to display it.
			if (tableData.empty()) {
				addMsg("SYS: Table [" + currTbl + "] is empty. No data to display.");
			}
			else {
				menu.SCRN_displayTable(msgs, tableData);
				msgs.clear();
				usrInput = fct.getUsrInput();
			}
			break;
		case '6': // Admin Actions
			menu.SCRN_adminActions(msgs);
			msgs.clear();
			usrInput = fct.getUsrInput();
			break;
		case '7': // Modify Movie Data menu
			menu.SCRN_modMovieMenu(msgs);
			msgs.clear();
			usrInput = fct.getUsrInput();
			break;
		case '8': // Modify Customer Data menu
			menu.SCRN_modCustMenu(msgs);
			msgs.clear();
			usrInput = fct.getUsrInput();
			break;
		default:
			string s(1, currUI);
			addMsg("CRITICAL ERROR: CODE MALFUNCTION! Program tried to call non-existent UI with ID = [" + s + "]. Displaying previous UI!");
			currUI = menu.getCurrMenu(); //may need to change this to menu.getPrevMenu() eventually...
			break;
	}
}

// Processes a char through [Menus.cpp] and updates the current UI based on the user's selection.
void static processUserInput() {
	char c = 'X';
	
	/*
	* Each case represents a specific UI.
	* Once the UI is determined, a call is made to process the user's input based on the available options for that UI.
	* The only exception for this is the login screen (case 2).
	* If the user's input was valid, [currUI] will be updated.
	*/
	switch (currUI) {
		case '1': // Welcome screen
			c = menu.SLCT_start(usrInput);
			break;
		case '2': // Login screen
			if (conn == true) {
				c = '3';
			}
			else {
				c = '1';
			}
			break;
		case '3': // Main Menu
			c = menu.SLCT_mainMenu(usrInput);
			break;
		case '4': // Display Tables menu
			c = menu.SLCT_displayMenu(usrInput);
			break;
		case '5': // Display Table
			// If [tableData] is empty, return to the previous UI.
			if (tableData.empty()) {
				c = '4';
			}
			else {
				c = menu.SLCT_displayTable(usrInput);
			}
			break;
		case '6': // Admin Actions
			c = menu.SLCT_adminActions(usrInput);
			break;
		case '7': // Modify Movie Data menu
			c = menu.SLCT_modMovieMenu(usrInput); // NOTE: Always sets [currUI] to '7'.
			break;
		case '8': // Modify Customer Data menu
			c = menu.SLCT_modCustMenu(usrInput); // NOTE: Always sets [currUI] to '8'.
			break;
		default:
			break;
	}

	// Error handling + data processing.
	if (c == 'X') {
		string s(1, usrInput);
		addMsg("ERROR [processUserInput()]: User input [" + s + "] is invalid!");
	}
	else {
		if (currUI == '4') {
			setTableName(); // When UI is at the Display menu, process the user's input to prep for displaying table data on the next UI.
		}
		currUI = c; // Update current UI reference as long as [c] is valid.
	}
}




int main() {

	// MAIN PROGRAM LOOP!
	while (currUI != '0') {
		usrInput = 'X'; // Reset user input to avoid possible mis-inputs/errors.
		callDisplayMethod();
		processUserInput();

		// This loop handles all opperations beyond the Login screen once a connection has been successfully established with the MySQL server.
		while (conn) {
			usrInput = 'X'; // Reset user input to avoid possible mis-inputs/errors.

			try {
				mysqlx::Session sess = mysqlx::getSession("localhost", 33060, User, Pass);
				mysqlx::Schema db = sess.getSchema("eztechmoviedb");
				
				/*
				* Under normal circumstances, I would create the containers for my variables at the beginning of a loop (as is common practice).
				* The issue posed by the <mysqlx::xdevapi> library is that most class objects do NOT have a default constructor. Such is the case with the <mysqlx::Table> class.
				* 
				*		Table getTable(const string &name, bool check_exists = false);
				* 
				* By default, the param [check_exists] is set to 'false' making it unnecessary to specify 'false' when initializing Table objects.
				* However, if I wanted to perform a check on the database, I would need to specify 'true' for [check_exists].
				* 
				* Because I cannot create a mysqlx::Table object without initializing it, I've initialized [tbl] with a non-existing table.
				* Since [check_exists] is set to 'false', the Table object [tbl] is created with name "NULL".
				*	NOTE: Any attempt to use a non-existing table in a database operation throws an error.
				* It is VERY IMPORTANT that this 'false' table object is NOT used to perform ANY operation on the database until it has been properly initialized with an existing table!!!
				* 
				* Now that [tbl] has been created and initialized, I can reference this object from anywhere in this try-catch block.
				*/
				mysqlx::Table tbl = db.getTable("NULL");

				switch (currUI) {
					// Close the connection the the MySQL server.
					case '1':
						addMsg("SYS: Connection to MySQL server closed.");
						User = "";
						Pass = "";
						currTbl = "NULL";
						conn = false;
						break;
					// If UI is to display a table, get table data in <std::> format first.
					case '5':
						/*
						* The statement below sets [check_exists] to 'true'.
						* This forces a 'check' on the database to ensure that a table exists with a name that matches the value stored in [currTbl].
						*	NOTE: This action requires communication with the server (implies that the Schema object must point to an existing database).
						* If the table exists, the object [tbl] is updated; if the table does NOT exist, the object [tbl] is NOT updated.
						* 
						* The statement below will check the database for [currTbl] first.
						* If it exists, then [tbl] is updated. If not, then [tbl] is NOT updated and an error is thrown.
						*/
						tbl = db.getTable(currTbl, true);
						fct.getTableData(tbl, &tableData, &msgs);
						break;
					default:
						break;
				}

				callDisplayMethod();
				processUserInput();

				if (edit_mode == true) { // When user is presented with options to INSERT/UPDATE/DELETE...
					switch (currUI) { 
						case '7': // Admin_Actions::Modify Movie Data
							switch (usrInput) {
								case '1':
									addMsg(movie.insertMovieData(db));
									break;
								case '2':
									addMsg(movie.updateMovieData(db));
									break;
								case '3':
									addMsg(movie.deleteMovieData(db));
									break;
								default:
									break;
							}
							break;
						case '8': // Admin_Actions::Modify Customer Data
							switch (usrInput) {
								case '1':
									addMsg(cust.insertCustData(db));
									break;
								case '2':
									addMsg(cust.updateCustData(db));
									break;
								case '3':
									addMsg(cust.deleteCustData(db));
									break;
								default:
									break;
							}
							break;
						default:
							break;
					}
				}
				
				// Update the status of [edit_mode] based on which UI is to be displayed next.
				if (currUI == '7' || currUI == '8') {
					edit_mode = true;
				}
				else {
					edit_mode = false;
				}

				sess.close(); // Close the Session object to avoid errors.
			}

			catch (const mysqlx::Error& err) {
				addMsg("MYSQLX_ERROR [main()]: " + string(err.what()));
				break;
			}
			catch (exception& ex) {
				addMsg("EXCEPTION [main()]: " + string(ex.what()));
				break;
			}
		}
	}
	
	if (currUI == '0') {
		menu.displayMenu();
	}

	return 0;
}

