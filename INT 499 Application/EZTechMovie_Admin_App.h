
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
#include <mysql.h>
/*
#include <cppconn/driver.h> 
#include <cppconn/exception.h> 
#include <cppconn/statement.h> 
#include <mysql_connection.h> 
#include <mysql_driver.h> 
*/
#pragma once


/*
* Contains generic user defined methods/functions
*/
class Global_Functions {

	public:
		Global_Functions();
		void clearScreen();
		string strToUpperCase(string);
		string strToLowerCase(string);
		void displayHeader(string, vector<string>);
		bool validate_UserOption(vector<int>, int);

	protected:
		string tempStr;
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
		MYSQL* conn;
		MYSQL_ROW row;
		MYSQL_RES* res;
		string query;
};

/*
* Handles user login and links to primary application.
*/
class Initialize_Program {

	public:
		Initialize_Program();
		void run();
		void login();
		bool verifyLogin(string, string);
		bool verifyUsername();
		bool verifyPassword();

	protected:
		Global_Functions fct;
		MySQL_Conn db;
		Main_Menu menu;
		string sys_msg;
		bool runInstance;
		int userInput;
		vector<int> user_options;
		vector<string> initial_menu;
		vector<string> login_menu;
		string Username;
		string Password;
		bool validLogin;
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
		string sys_msg;
		bool runInstance;
		int userInput;
		vector<int> user_options;
		vector<string> main_menu;
		bool valid;
};

/*
* Handles...
*/
class Add_Movie {
	
	public:
		Add_Movie();
		string strToUpperCase(string);
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
		string title;
		int castSize;
		vector<string> cast;
		string rating;
		string userInput;
		vector<string> movieRatings; // Stores all acceptable values for a movie's rating
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
* Handles...
*/
/*
class a {

	public:
		void run();

	protected:

};
*/

