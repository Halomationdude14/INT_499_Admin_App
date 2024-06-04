
#include <string>
#include <vector>
#include <mysqlx/xdevapi.h>
#pragma once


/*
* Contains generic user defined methods/functions to assist in basic actions
*/
class Global_Functions {

	public:
		Global_Functions();
		void clearScreen();
		char getUsrInput();
		vector<vector<string>> getTableData(mysqlx::Table);
		string strToUpperCase(string);
		string strToLowerCase(string); //delete??? (don't think this is used at all anymore)
		char charToUpperCase(char);
		bool strIsInt(string&);

	protected:
		string tempStr;
		char c;
};


/*
* Contains all menu data and functions to display that data
*/
class Menus {

	public:
		Menus();

		void displayMenu(vector<string>);
		void displayMenu(vector<string>, vector<string>);
		void displayTable(vector<string>, vector<vector<string>>);
		void displayTable(vector<string>, vector<string>, vector<vector<string>>);

		char getCurrMenu() const;
		char getPrevMenu() const; //dont think this is used at all... may still serve a purpose.

		//Are these even used anymore? If not, then delete!
		void SCRN_BASE(vector<string>);
		char SLCT_BASE(char);
		//###################################

		/*
		* [SCRN] = Functions that display a specific UI and update the currMenu variable.
		* [SLCT] = Functions that take in user input intended for navigating the menues. Returns char to indicate what the next UI shall be.
		*/

		// SCOPE: Basic functions to handle displaying the first 3 UIs and processing user input for each one.
		void SCRN_start(vector<string>);
		char SLCT_start(char);
		void SCRN_login(vector<string>);
		// NOTE: No [SLCT] function for the login screen; main() handles this due to required MySQLX library.
		void SCRN_mainMenu(vector<string>);
		char SLCT_mainMenu(char);
		//###################################

		// SCOPE: { Main Menu --> Display menu }
		void SCRN_displayMenu(vector<string>);
		char SLCT_displayMenu(char);
		void SCRN_displayTable(vector<string>, vector<vector<string>>);
		char SLCT_displayTable(char);
		//###################################

		// SCOPE: { Main Menu --> Admin Actions menu } (*Not including any UIs/processes past choosing to INSERT/UPDATE/DELETE a specific table*)
		void SCRN_adminActions(vector<string>);
		char SLCT_adminActions(char);
		void SCRN_modMovieMenu(vector<string>);
		char SLCT_modMovieMenu(char);
		void SCRN_modCustMenu(vector<string>);
		char SLCT_modCustMenu(char);
		//###################################

	private:
		Global_Functions fct;
		string tempStr;
		char currMenu;
		char prevMenu;
		bool noEdit_Table;

		// Each vector contains strings that list a number/letter + a description. These are what comprise the selectable options in each menu.
		vector<string> base_Menu;
		vector<string> start_Menu;
		vector<string> main_Menu;
		vector<string> displayTables_Menu;
		vector<string> editTable_Menu;
		vector<string> noEditTable_Menu;
		vector<string> adminActions_Menu;
		vector<string> modifyMovie_Menu;
		vector<string> modifyCust_Menu;
};


// Class to handle INSERT/UPDATE/DELETE opperations on the table "tbl_moviedata".
// Operations are found in Admin Actions menu.
class DB_MovieData {
	
	public:
		DB_MovieData();
		void setDefaultValues();
		void setTitle();
		void setYear();
		void setRating();
		void setNumCast();
		void setCast(int numCast);
		void setNumDir();
		void setDir(int numDir);
		void setGenre();
		void displayNewMovie();
		void modifyNewMovie();
		void validationSCRN();

		vector<string> insertMovieData(mysqlx::Schema);
		vector<string> updateMovieData(mysqlx::Schema);
		vector<string> deleteMovieData(mysqlx::Schema);

	protected:
		Global_Functions fct;
		Menus menu;
		vector<string> msgs;
		vector<vector<string>> tableData;
		string input;
		// Vars to be processed to DB -->
		string movieTitle;
		int movieYear;
		string movieRating;
		int movieNumCast;
		int movieNumDir;
		vector<vector<string>> movieCastMembers;
		vector<vector<string>> movieDirectors;
		vector<int> movieGenres;
};


// Class to handle INSERT/UPDATE/DELETE opperations on the table "tbl_custdata".
// Operations are found in Admin Actions menu.
class DB_CustData {

	public:
		DB_CustData();
		void insertCustData();
		void updateCustData();
		void deleteCustData();

	protected:
		Global_Functions fct;
		Menus menu;
		vector<string> msgs;
		vector<vector<string>> tableData;
		bool running = true;
		string input = "";
};

