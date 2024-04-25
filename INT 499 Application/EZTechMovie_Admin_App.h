
/*
INT 499 Capstone for Information Technology
Interactive Assignment
Date: 2024-04-22
Author: Paul Oram
NOTE: This is a modified version of the original code that has been reworked to integrate into the final project (MySQL DB).
*/

#include <string>
#include <vector>
#pragma once


/*
* Contains generic user defined methods/functions
*/
class Global_Functions {

	public:
		Global_Functions();
		string strToUpperCase(string);
		string strToLowerCase(string);
		bool validate_UserOption(vector<int>, int);

	private:
		string tempStr;
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
		bool runInstance;
		int userInput;
		vector<int> user_options;
		string Username;
		string Password;
		bool validLogin;
};

/*
* Links to all other classes.
* Responsible for displaying all possible options to admin user in list format.
* List -->
*	1. Display Data
*	2. Modify Data
*	3. Admin Account
*	4. Sign Out
*/
class Main_Menu {

	public:
		Main_Menu();
		bool validateInput(int);
		void run();

	protected:
		Global_Functions fct;
		bool runInstance;
		int userInput;
		vector<int> user_options;
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



