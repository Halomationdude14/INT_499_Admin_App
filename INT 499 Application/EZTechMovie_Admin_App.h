
#include <string>
#include <vector>
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

	public:
		MySQL_Connection();
		vector<std::string> login();
		bool startConnection();
		bool userLogin(std::string, std::string);
		bool closeConnection();

	protected:
		std::string tempStr;
		vector<std::string> sys_msg;
		std::string dbUser;
		std::string dbName;
};

class Menus {

	public:
		Menus();
		void displayMenu(vector<std::string>);
		void displayMenu(vector<std::string>, vector<std::string>);
		vector<std::string> getCurrMenu();
		char getCurrMenuNum();
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
		vector<std::string> start_Menu;
		vector<int> startMenu_Options;
		vector<std::string> main_Menu;
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
