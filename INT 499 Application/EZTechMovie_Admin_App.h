
#include <string>
#include <vector>
#include <mysqlx/xdevapi.h>
#pragma once


// Contains generic user defined functions to assist in data capture and processing.
class Global_Functions {

	public:
		Global_Functions();
		void clearScreen();
		int getCurrYear();
		char getUsrInput();
		void getTableData(mysqlx::Table, vector<vector<string>>*, vector<string>*);
		void getRow(vector<vector<string>>, int, vector<string>*, vector<string>*);
		string strToUpperCase(string);
		char charToUpperCase(char);
		bool strIsInt(string&);

	protected:
		string tempStr;
		char c;
};


// Contains all menu data and functions to display that data.
class Menus {

	public:
		Menus();
		void displayMenu();
		void displayMenu(vector<string>);
		void displayMenu(vector<string>, string);
		void displayMenu(vector<string>, string, vector<string>);
		void displayTable(vector<string>, vector<vector<string>>);
		void displayTable(vector<string>, vector<string>, vector<vector<string>>);
		char getCurrMenu() const;
		char getPrevMenu() const;

		/*
		* [SCRN] = Functions that display a specific UI and update the currMenu variable.
		* [SLCT] = Functions that take in user input intended for navigating the menues. Returns char to indicate what the next UI shall be.
		*/

		// SCOPE: Basic functions to handle displaying the first 3 UIs and processing user input for each one.
		void SCRN_start(vector<string>);
		char SLCT_start(char);
		void SCRN_login(vector<string>);
		void SCRN_mainMenu(vector<string>);
		char SLCT_mainMenu(char);
		// SCOPE: { Main Menu > Display menu }
		void SCRN_displayMenu(vector<string>);
		char SLCT_displayMenu(char);
		void SCRN_displayTable(vector<string>, vector<vector<string>>);
		char SLCT_displayTable(char);
		// SCOPE: { Main Menu > Admin Actions } (*Not including any UIs/processes beyond choosing to INSERT/UPDATE/DELETE a specific table*)
		void SCRN_adminActions(vector<string>);
		char SLCT_adminActions(char);
		void SCRN_modMovieMenu(vector<string>);
		char SLCT_modMovieMenu(char);
		void SCRN_modCustMenu(vector<string>);
		char SLCT_modCustMenu(char);

	private:
		Global_Functions fct;
		char currMenu;
		char prevMenu;
		string header;
		string nav_main;
		string nav_dispTbl;
		string nav_admAct;
		string nav_modMovie;
		string nav_modCust;
		vector<string> base_Menu;
		vector<string> start_Menu;
		vector<string> main_Menu;
		vector<string> displayTables_Menu;
		vector<string> adminActions_Menu;
		vector<string> modifyMovie_Menu;
		vector<string> modifyCust_Menu;
};


/*
* Class to handle INSERT/UPDATE/DELETE opperations on the table {tbl_moviedata}.
* Operations are found in Admin Actions menu.
*/
class DB_MovieData {
	
	public:
		DB_MovieData();
		void setDefaultValues();
		void addMsg(vector<string>);
		void addMsg(string);
		bool validInput();
		vector<string> newPerson();

		void setTitle(mysqlx::Schema);
		void setYear();
		void setRating();
		void setNumCast();
		void addNewCast(mysqlx::Table);
		void setCast(mysqlx::Schema);
		void setNumDir();
		void addNewDir(mysqlx::Table);
		void setDir(mysqlx::Schema);
		void addNewGenre(mysqlx::Table);
		void setGenre(mysqlx::Schema);
		void displayNewMovie();
		void modifyNewMovie(mysqlx::Schema);
		void validationSCRN(mysqlx::Schema);
		void sendMovieToDB(mysqlx::Schema);

		vector<string> insertMovieData(mysqlx::Schema);
		vector<string> updateMovieData(mysqlx::Schema);
		vector<string> deleteMovieData(mysqlx::Schema);

	protected:
		Global_Functions fct;
		Menus menu;
		vector<string> msgs;
		vector<vector<string>> tableData;
		vector<string> tblIndexes;
		string input;
		string movieTitle;
		int movieYear;
		string movieRating;
		int movieNumCast;
		int movieNumDir;
		vector<vector<string>> movieCastMembers;
		vector<vector<string>> movieDirectors;
		vector<int> movieGenreIDs;
		vector<string> movieGenreNames;
};


/*
* Class to handle INSERT/UPDATE/DELETE opperations on the table {tbl_custdata}.
* Operations are found in Admin Actions menu.
*/
class DB_CustData {

	public:
		DB_CustData();

		vector<string> insertCustData(mysqlx::Schema);
		vector<string> updateCustData(mysqlx::Schema);
		vector<string> deleteCustData(mysqlx::Schema);

	protected:
		Global_Functions fct;
		Menus menu;
		vector<string> msgs;
		vector<vector<string>> tableData;
		bool running = true;
		string input = "";
};

