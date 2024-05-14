
#include <string>
#include <vector>
#include <mysqlx/xdevapi.h>
#pragma once


/*
* Contains generic user defined methods/functions
*/
class Global_Functions {

	public:
		Global_Functions();
		void clearScreen();
		void displayHeader(vector<std::string>);
		void addMsg(vector<std::string> msg);
		void removeLastMsg();
		void clearAllMsgs();
		bool validate_UserOption(vector<int>, int);
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

	public:
		MySQL_Connection();
		bool startConnection();
		void userLogin(std::string, std::string);
		void closeConnection();

	protected:
		//mysqlx::Session sess;
		//mysqlx::Schema db;
		vector<std::string> sys_msg;
		std::string hostname;
		int port;
		std::string dbName;
		std::string dbUser;
		std::string dbPass;
		vector<std::string> dbTables;
		std::string tempStr;
};

class Menus {

	public:
		Menus();
		void displayHeader(vector<std::string>, vector<std::string>);
		void startScreen(vector<std::string>);
		void loginScreen(vector<std::string>);
		void mainMenu(vector<std::string>);

	private:
		Global_Functions fct;
		std::string tempStr;
		vector<std::string> startMenu;
		vector<int> startMenu_Options;
		vector<std::string> mainMenu;
		vector<int> mainMenu_Options;
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
