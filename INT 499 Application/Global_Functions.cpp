
#ifdef _WIN32
#include <conio.h>
#endif

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <mysqlx/xdevapi.h>
using namespace std;

#include "EZTechMovie_Admin_App.h"


// Define ANSI color codes based on Dracula theme
constexpr auto TEXT =	"\033[38;2;248;248;242m";
constexpr auto RED =	"\033[38;2;255;85;85m";
constexpr auto PURPLE = "\033[38;2;255;121;198m";


// Default Constructor
Global_Functions::Global_Functions() {
	tempStr = "";
	c = 'X';
}


// Clear the terminal screen.
void Global_Functions::clearScreen() {
	system("cls");
}

// Obtains the current year
int Global_Functions::getCurrYear() {
	// Get the current time as a time_t object.
	time_t now = time(nullptr);

	// Create a tm structure to hold the local time.
	tm local_time;

	// Use localtime_s (safer version of localtime) to populate the tm structure.
	localtime_s(&local_time, &now);

	// Extract the year (tm_year is years since 1900, so we add 1900).
	int year = local_time.tm_year + 1900;

	return year;
}

// Obtain the user's input when selecting menu options. Validate's input too.
char Global_Functions::getUsrInput() {
	tempStr = "";
	c = 'X';

	cout << "\nUser Input: ";
#ifdef _WIN32
	c = _getch(); // Get a character without requiring <ENTER>.
#else
	getline(cin, tempStr);
	if (!tempStr.empty()) {
		c = tempStr[0];
	}
	else {
		c = 'X';
	}
#endif
	c = charToUpperCase(c);
	return c;
}

// NOTE: This function returns two vars using pointers!
void Global_Functions::getTableData(mysqlx::Table table, vector<vector<string>>* tableData, vector<string>* msgs) {
	vector<string> message = {}; // Vector to hold all sys/err messages.
	vector<vector<string>> tblData = {}; // Holds table data in <std> format to be sent to Menus object for display.

	try {
		mysqlx::RowResult result = table.select("*").execute();

		for (mysqlx::Row row : result) {
			vector<string> rowData;

			for (int i = 0; i < row.colCount(); ++i) {
				mysqlx::Value val = row[i];
				tempStr = "";

				switch (val.getType()) {
					case mysqlx::Value::Type::UINT64:
						tempStr = to_string(val.get<uint64_t>());
						break;
					case mysqlx::Value::Type::INT64:
						tempStr = to_string(val.get<int64_t>());
						break;
					case mysqlx::Value::Type::FLOAT:
						tempStr = to_string(val.get<float>());
						break;
					case mysqlx::Value::Type::DOUBLE:
						tempStr = to_string(val.get<double>());
						break;
					case mysqlx::Value::Type::BOOL:
						tempStr = to_string(val.get<bool>());
						break;
					case mysqlx::Value::Type::STRING:
						tempStr = val.get<string>();
						break;
					case mysqlx::Value::Type::VNULL:
						tempStr = "NULL";
						break;
					default:
						tempStr = "<ERROR>";
						break;
				}

				rowData.push_back(tempStr);
			}

			tblData.push_back(rowData);
		}
	}

	catch (const mysqlx::Error& err) {
		message.push_back(string(PURPLE) + "MYSQLX_ERROR [getTableData()]: " + TEXT + string(err.what()));
	}
	catch (exception& ex) {
		message.push_back(string(PURPLE) + "EXCEPTION [getTableData()]: " + TEXT + string(ex.what()));
	}

	tempStr.clear();
	*tableData = tblData;
	*msgs = message;
}

// Searches through a set of table data in <std::> format for a row with a specified ID.
// NOTE: This function returns two vars using pointers!
void Global_Functions::getRow(vector<vector<string>> tableData, int ID, vector<string>* rowData, vector<string>* msgs) {
	vector<string> message = {}; // Vector to hold all sys/err messages.
	vector<string> row = {}; // Vector to hold a single row from a table in <std::> format.

	try {
		if (tableData.empty()) {
			message.push_back(string(RED) + "ERROR [getRow()]:" + TEXT + " No table data to process! Cannot retrieve row data.");
		}
		else {
			for (auto& i : tableData) {
				if (strIsInt(i[0])) {
					if (stoi(i[0]) == ID) {
						row = i;
					}
				}
				else { // In case the wrong table is put through this function (i.e., tables with a first column that is not of type [int]).
					message.push_back(string(RED) + "ERROR [getRow()]:" + TEXT + " First column of table is not of type [int]! Aborting process.");
					break;
				}
			}
		}
	}

	catch (exception& ex) {
		message.push_back(string(PURPLE) + "EXCEPTION [getRow()]: " + TEXT + string(ex.what()));
	}

	*rowData = row;
	*msgs = message;
}

// Convert all chars in a string to UPPER case.
string Global_Functions::strToUpperCase(string str) {
	tempStr = "";
	c = 'X';

	for (int i = 0; i < str.size(); ++i) {
		c = str.at(i);
		if (isalpha(c) and islower(c)) {
			tempStr.push_back(toupper(c));
		}
		else {
			tempStr.push_back(c);
		}
	}

	return tempStr;
}

// Convert a given char to upper case if it is alphabetical.
char Global_Functions::charToUpperCase(char letter) {
	c = 'X';

	if (isalpha(letter) and islower(letter)) {
		c = toupper(letter);
	}
	else {
		c = letter;
	}

	return c;
}

// Takes in a string and verifies if it contains all integers or not.
bool Global_Functions::strIsInt(string& str) {
	return all_of(str.begin(), str.end(), ::isdigit);
}

