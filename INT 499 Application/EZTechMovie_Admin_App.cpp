
/*
INT 499 Capstone for Information Technology
Interactive Assignment
Date: 2024-04-22
Author: Paul Oram
NOTE: This is a modified version of the original code that has been reworked to integrate into the final project (MySQL DB).
*/

#include <iostream>
#include <string>
#include <exception>
#include <vector>
using namespace std;

#include "EZTechMovie_Admin_App.h"


// Default constructor
EZTechMovie_Admin_App::EZTechMovie_Admin_App() {
	// Add variables
}

// Purpose: Recursive main method used to run app. If user's input is "Y", program executes. If "N", program terminates.
void EZTechMovie_Admin_App::run() {
	EZTechMovie_Admin_App newMovie;
	newMovie.SetAnswer();
	while (newMovie.answer == 'Y') {
		newMovie.SetMovieTitle();
		newMovie.SetCastSize();
		newMovie.SetCastMembers();
		newMovie.SetRating();
		newMovie.SetAnswer();
		//return run(); // Recalls this function to ask for user input again
	}
	newMovie.displayMovies();
}
