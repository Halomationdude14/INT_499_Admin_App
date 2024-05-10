
/*
INT 499 Capstone for Information Technology
Interactive Assignment
Date: 2024-04-22
Author: Paul Oram
NOTE: This is a modified version of the original code that has been reworked to integrate into the final project (MySQL DB).
*/

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
		void displayHeader(std::string, vector<std::string>);
		bool validate_UserOption(vector<int>, int);
		std::string strToUpperCase(std::string);
		std::string strToLowerCase(std::string);

	protected:
		std::string tempStr;
};

/*
* Establishes the connection to the locally stored MySQL database.
* Contains functions used to execute queries against the database.
*/
class MySQL_Conn {

	public:
		MySQL_Conn();
		bool startConn();
		void closeConn();

	protected:
		mysqlx::Session sess;
		mysqlx::Schema db;
		std::string hostname;
		int port;
		std::string dbName;
		std::string user;
		std::string pass;
		vector<std::string> dbTables;
		std::string query;
};

/*
* Links to all other classes.
* Responsible for displaying all possible options to admin user in list format.
*/
class Main_Menu {

	public:
		Main_Menu();
		void run();

	protected:
		Global_Functions fct;
		std::string sys_msg;
		bool runInstance;
		int userInput;
		vector<int> user_options;
		vector<std::string> menu_options;
		bool valid;
};

/*
* Handles...
*/
class Add_Movie {
	
	public:
		Add_Movie();
		std::string strToUpperCase(std::string);
		void SetAnswer();
		void SetMovieTitle();
		void SetCastSize();
		void SetCastMembers();
		void SetRating();
		void addMovie(Add_Movie movie);
		void displayMovies();
		void run();
		char answer;
		vector<Add_Movie> movieList; // Stores all movies that the user adds to the DB

	protected:
		std::string title;
		int castSize;
		vector<std::string> cast;
		std::string rating;
		std::string userInput;
		vector<std::string> movieRatings; // Stores all acceptable values for a movie's rating
};

/*
* Hanldes all opperations found within the "[1] Display Data" option in the Main Menu
*/
class Display_Mode {

	public:
		Display_Mode();
		void run();

	protected:
		Global_Functions fct;
};

/*
* Hanldes all opperations found within the "[2] Modify Data" option in the Main Menu
*/
class Edit_Mode {

	public:
		Edit_Mode();
		void run();

	protected:
		Global_Functions fct;
};

/*
* Handles user login and links to primary application.
*/
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
	MySQL_Conn db;
	Main_Menu menu;
	std::string sys_msg;
	bool runInstance;
	int userInput;
	vector<int> user_options;
	vector<std::string> menu_options;
	std::string Username;
	std::string Password;
	bool dbConn;
	bool validLogin;
};

/*
* Handles...
*/
/*
class a {

	public:
		void run();

	protected:

};
*/


