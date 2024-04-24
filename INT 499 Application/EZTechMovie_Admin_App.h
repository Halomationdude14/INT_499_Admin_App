
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
		// void a();

	private:
		// enter here
};

/*
* Handles user login and links to primary application.
*/
class Initialize_Program {

	public:
		Initialize_Program();
		void run();
		void login(string, string);

	protected:
		// enter here
};

/*
* Links to all other classes.
* Responsible for displaying all possible options to admin user in list format.
* List -->
*	1. Movie Manager
*	2. 
*/
class Main_Menu {

	public:
		Main_Menu();
		void run();

	protected:
		// enter here
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
		// enter here
};

/*
* Hanldes all opperations found within the "[2] Modify Data" option in the Main Menu
*/
class Edit_Mode {

	public:
		Edit_Mode();
		void run();

	protected:
		// enter here
};

/*
* Handles...
*/
class a {

	public:
		void run();

	protected:

};



