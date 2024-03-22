
/*
INT 499 Capstone for Information Technology
Week 3 - Interactive Assignment
Date: 2024-03-22
Author: Paul Oram
*/

#include <string>
#include <vector>

#pragma once
class EZTechMovie_Admin_App {
	
	public:
		EZTechMovie_Admin_App();
		string strToUpperCase(string);
		void SetAnswer();
		void SetMovieTitle();
		void SetCastSize();
		void SetCastMembers();
		void SetRating();
		void addMovie(EZTechMovie_Admin_App movie);
		void displayMovies();
		void run();
		char answer;
		vector<EZTechMovie_Admin_App> movieList; // Stores all movies that the user adds to the DB

	protected:
		string title;
		int castSize;
		vector<string> cast;
		string rating;
		string userInput;
		vector<string> movieRatings; // Stores all acceptable values for a movie's rating
};

