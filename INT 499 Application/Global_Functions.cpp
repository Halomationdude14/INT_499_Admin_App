
#ifdef _WIN32
#include <conio.h>
#endif

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <mysqlx/xdevapi.h>
using namespace std;

#include "EZTechMovie_Admin_App.h"


// Default Constructor
Global_Functions::Global_Functions() {
	tempStr = ""; // General use string.
	c = 'X';
}

// Purpose: Clear the terminal screen.
void Global_Functions::clearScreen() {
	system("cls");
}

// Purpose: Obtain the user's input when selecting menu options. Validate's input too.
char Global_Functions::getUsrInput() {
	tempStr = "";
	c = 'X';

	cout << "\nUser Input: ";
#ifdef _WIN32
	c = _getch(); // Get a character without requiring ENTER
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

// Converts <mysqlx::RowResult> to vector<vector<string>> format
vector<vector<string>> Global_Functions::getTableData(mysqlx::Table table) {
	vector<string> msgs = {}; // Vector to hold all sys/err messages.
	vector<vector<string>> tableData = {}; // Holds table data in <std> format to be sent to Menus object for display.

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
					strValue = val.get<string>();
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
		return tableData;
	}
	catch (const mysqlx::Error& err) {
		msgs.push_back("MYSQLX_ERROR [getTableData()]: " + string(err.what()));
	}
	catch (exception& ex) {
		msgs.push_back("ERROR [getTableData()]: " + string(ex.what()));
	}
}

// Purpose: Convert all chars in a string to UPPER case.
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

// Purpose: Convert all chars in a string to LOWER case.
string Global_Functions::strToLowerCase(string str) {
	tempStr = "";
	c = 'X';

	for (int i = 0; i < str.size(); ++i) {
		c = str.at(i);
		if (isalpha(c) and isupper(c)) {
			tempStr.push_back(tolower(c));
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