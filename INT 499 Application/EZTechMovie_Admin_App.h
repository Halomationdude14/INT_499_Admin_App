
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

		void displayHeader(vector<std::string>);
		void addMsg(vector<std::string> msg);
		void removeLastMsg();
		void clearAllMsgs();

		vector<std::string> validate_UserOption(vector<std::string>, char);
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
// REWORK: Rename to "Server_Conn"
class MySQL_Connection {

	private:
		std::unique_ptr<mysqlx::Session> sess;
		std::unique_ptr<mysqlx::Schema> schema;
		std::unique_ptr<mysqlx::Table> table;

	public:
		MySQL_Connection();
		bool getConn();
		vector<std::string> login();
		bool startConn(std::string, std::string);
		vector<std::string> closeConn();

	protected:
		std::string str;
		vector<std::string> msgs;
		std::string dbUser;
		std::string dbPass;
		bool conn;
};

class Menus {

	public:
		Menus();
		void displayMenu(vector<std::string>);
		void displayMenu(vector<std::string>, vector<std::string>);
		char getCurrMenu() const;
		char getPrevMenu() const;
		void SCRN_BASE(vector<std::string>);
		char SLCT_BASE(char);
		void SCRN_start(vector<std::string>);
		char SLCT_start(char);
		void SCRN_login(vector<std::string>);
		void SCRN_mainMenu(vector<std::string>);
		char SLCT_mainMenu(char input);

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
};








/*
class Main_Menu {

	public:
		Main_Menu();
		void run();

	protected:
		Global_Functions fct;
		vector<std::string> sys_msg;
		bool runInstance;
		int userInput;
		vector<int> user_options;
		vector<std::string> menu_options;
		bool valid;
};


class Start_Program {

public:
	Start_Program();
	void run();
	void login();
	bool verifyLogin(std::string, std::string);
	bool verifyUsername();
	bool verifyPassword();

protected:
	Global_Functions fct;
	MySQL_Connection db;
	Main_Menu menu;
	vector<std::string> sys_msg;
	bool runInstance;
	int userInput;
	vector<int> user_options;
	vector<std::string> menu_options;
	std::string Username;
	std::string Password;
	bool dbConn;
	bool validLogin;
};
*/

