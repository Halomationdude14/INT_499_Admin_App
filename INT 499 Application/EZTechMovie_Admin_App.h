
#include <string>
#include <vector>
#pragma once


/*
* Contains generic user defined methods/functions
*/
class Global_Functions {

	public:
		Global_Functions();
		void clearScreen();
		char getUsrInput();
		string strToUpperCase(string);
		string strToLowerCase(string);
		char charToUpperCase(char);

	protected:
		string tempStr;
		char c;
};

/*
* Contains all menu data and methods to display that data
*/
class Menus {

	public:
		Menus();
		void displayMenu(vector<string>);
		void displayMenu(vector<string>, vector<string>);
		void displayTable(vector<string>, vector<string>, vector<vector<string>>);
		
		void displayAdmin(vector<string>, vector<string>, vector<vector<string>>);
		
		char getCurrMenu() const;
		char getPrevMenu() const;
		void SCRN_BASE(vector<string>);
		char SLCT_BASE(char);
		void SCRN_start(vector<string>);
		char SLCT_start(char);
		void SCRN_login(vector<string>);
		void SCRN_mainMenu(vector<string>);
		char SLCT_mainMenu(char input);
		void SCRN_displayMenu(vector<string>);
		char SLCT_displayMenu(char input);
		void SCRN_displayTable(vector<string>, vector<vector<string>>);
		char SLCT_displayTable(char input);
		void SCRN_editMenu(vector<string>);
		char SLCT_editMenu(char input);
		void SCRN_editTable(vector<string>, vector<vector<string>>);
		char SLCT_editTable(char input);
		void SCRN_adminAccount(vector<string>);
		char SLCT_adminAccount(char input);


	private:
		Global_Functions fct;
		string tempStr;
		vector<string> msgSet;
		vector<vector<string>> msgSetList;
		char currMenu;
		char prevMenu;
		bool noEdit_Table;
		vector<string> base_Menu;
		vector<string> start_Menu;
		vector<string> main_Menu;
		vector<string> display_Menu;
		vector<string> displayTable_Menu;
		vector<string> displayTable_Menu_NoEdit;
		vector<string> edit_Menu;
		vector<string> editTable_Menu;
};

