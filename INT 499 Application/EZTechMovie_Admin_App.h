
#include <string>
#include <vector>
#include <mysqlx/xdevapi.h>
#pragma once


/*
* Contains generic user defined methods/functions
*/
// REWORK: Rename class/file to "Glb_Fct"!
class Global_Functions {

	public:
		Global_Functions();
		void clearScreen();
		char getUsrInput();
		std::string strToUpperCase(std::string);
		std::string strToLowerCase(std::string);

	protected:
		vector<vector<std::string>> Notifications;
		vector<std::string> sys_msg;
		std::string tempStr;
};

/*
* Establishes the connection to the locally stored MySQL database.
* Contains functions used to execute queries against the database.
*/
class MySQL_Connection {

	private:
		std::unique_ptr<mysqlx::Session> sess;
		std::unique_ptr<mysqlx::Schema> scm;
		std::unique_ptr<mysqlx::Table> tbl;

		//Session sess2;
		//Schema scm2;
		//Table tbl2;

	public:
		MySQL_Connection();
		MySQL_Connection(std::string, std::string);
		bool getConn();
		vector<std::string> login();
		vector<std::string> setTable(char);
		vector<vector<std::string>> getTable();
		bool startConn(std::string, std::string);
		vector<std::string> closeConn();

	protected:
		std::string str;
		vector<std::string> msgs;
		std::string dbUser;
		std::string dbPass;
		bool conn;
		std::string currTbl;
};

class Menus {

	public:
		Menus();
		void displayMenu(vector<std::string>);
		void displayMenu(vector<std::string>, vector<std::string>);
		void displayTable(vector<std::string>, vector<std::string>, vector<vector<std::string>>);
		void displayAdmin(vector<std::string>, vector<std::string>, vector<vector<std::string>>);

		char getCurrMenu() const;
		char getPrevMenu() const;
		void SCRN_BASE(vector<std::string>);
		char SLCT_BASE(char);
		void SCRN_start(vector<std::string>);
		char SLCT_start(char);
		void SCRN_login(vector<std::string>);
		void SCRN_mainMenu(vector<std::string>);
		char SLCT_mainMenu(char input);

		void SCRN_displayMenu(vector<std::string>);
		char SLCT_displayMenu(char input);
		void SCRN_displayTable(vector<std::string>, vector<vector<std::string>>);
		char SLCT_displayTable(char input);

		void SCRN_editMenu(vector<std::string>);
		char SLCT_editMenu(char input);
		void SCRN_editTable(vector<std::string>, vector<vector<std::string>>);
		char SLCT_editTable(char input);

		void SCRN_adminAccount(vector<std::string>);
		char SLCT_adminAccount(char input);


	private:
		Global_Functions fct;
		std::string tempStr;
		vector<std::string> msgSet;
		vector<vector<std::string>> msgSetList;
		char currMenu;
		char prevMenu;
		vector<std::string> base_Menu;
		vector<std::string> start_Menu;
		vector<std::string> main_Menu;
		vector<std::string> display_Menu;
		vector<std::string> edit_Menu;
};


