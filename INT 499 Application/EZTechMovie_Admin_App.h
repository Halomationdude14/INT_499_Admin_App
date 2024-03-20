
/*
INT 499 Capstone for Information Technology
Week 3 - Interactive Assignment
Date: 2024-03-21
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
		void displayMovie();
		void storeMovie();

	protected:
		string name;
		int castSize;
		vector<string> cast;
		string rating;
		char answer;
		string userInput;
		vector<string> movieRatings;
};

