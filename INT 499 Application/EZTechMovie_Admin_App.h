
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
* Handles user login and links to primary application.
*/
class EZTechMovie_Admin_App {

	public:
		void run();

	protected:

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
	void run();

protected:

};

/*
* 
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
* 
*/
class a {

	public:
		void run();

	protected:

};







