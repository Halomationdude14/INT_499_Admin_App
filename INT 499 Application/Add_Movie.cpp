
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
Add_Movie::Add_Movie() {
	title = "none";
	castSize = 0;
	rating = "";
	answer = 'a';
	userInput = "";
	movieRatings.push_back("G");
	movieRatings.push_back("PG");
	movieRatings.push_back("PG-13");
	movieRatings.push_back("R");
	movieRatings.push_back("NC-17");
}


// Purpose: Converts all letters in a given string "str" to uppercase letters and ignores all other chars.
string Add_Movie::strToUpperCase(string str) {
	string tempStr = "";
	char c;

	for (int i = 0; i < str.size(); ++i) {
		c = str.at(i);
		if (isalpha(c) and islower(c)) {
			tempStr.push_back(toupper(c));
		}
		else {
			tempStr.push_back(c);
		}
	}
	return tempStr;
}

// Purpose: Get's the user's input as to whether to add a movie or not. Shall be in a "Y" or "N" format.
void Add_Movie::SetAnswer() {
	answer = 'a';

	try {
		cout << "\nWould you like to store additional movies? [Y/N]";
		cout << "\nAnswer: ";
		cin >> answer;
		answer = toupper(answer);

		if (answer != 'Y' and answer != 'N') {
			throw exception();
		}
	}

	catch (exception& e) {
		cout << "\nERROR: User answer [" << answer << "] is invalid!\nPlease try again." << endl;
		cin.clear(); // clears the error flags
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // this line discards all the input waiting in the stream
		SetAnswer();
	}
}

// Purpose: Obtain's the user's input and sets the title of the movie.
void Add_Movie::SetMovieTitle() {
	cout << "\nMovie Title: ";
	cin.ignore();
	getline(cin, title);
}

// Purpose: Obtains user's input and sets the number of main cast members in the movie.
void Add_Movie::SetCastSize() {
	userInput = "";

	try {
		cout << "\nNumbers of Main-Cast Members: ";
		cin >> userInput;

		for (int i = 0; i < userInput.size(); ++i) {
			if (!isdigit(userInput.at(i))) {
				throw exception();
			}
		}
		castSize = stoi(userInput);
	}

	catch (exception& e) {
		cout << "\nERROR: User answer [" << userInput << "] is invalid!\nPlease try again." << endl;
		cin.clear(); // clears the error flags
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // this line discards all the input waiting in the stream
		SetCastSize();
	}
}

// Purpose: Obtains user's input(s) based on how many cast members there are. Input format = First Name + Last Name.
void Add_Movie::SetCastMembers() {
	cast.resize(castSize);
	cout << "\nCast Members (First & Last Names):" << endl;
	cin.ignore(); // Closes previous getlin() to allow for more further inputs

	for (int i = 0; i < castSize; ++i) {
		cout << (i + 1) << ". ";
		getline(cin, cast[i]); // Gets user input until <ENTER> is pressed
	}
}

// Purpose: Obtains the user's input for the movie's rating.
void Add_Movie::SetRating() {
	rating = "";
	bool isTrue = false;

	try {
		cout << "\nPlease select one of the following ratings: G, PG, PG-13, R, NC-17" << "\nEnter Movie Rating: ";
		cin >> rating;
		rating = strToUpperCase(rating); // This is done to ensure that all letters in the user's input are converted to CAPITALS to be compatible with the vector "movieRatings".

		// Can improve this segment of code. Something similar to "for (a in b)" which resolves to true/false.
		for (int i = 0; i < movieRatings.size(); ++i) {
			if (rating == movieRatings.at(i)) {
				isTrue = true;
			}
		}
		if (isTrue == false) {
			throw exception();
		}
	}

	catch (exception& e) {
		cout << "\nERROR: User answer [" << rating << "] is invalid!\nPlease try again." << endl;
		cin.clear(); // clears the error flags
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // this line discards all the input waiting in the stream
		SetRating();
	}
}

// Purpose: To add a movie to the vector of movie objects.
void Add_Movie::addMovie(Add_Movie movie) {
	movieList.push_back(movie);
}

// Purpose: To display a movie's information in the terminal output.
void Add_Movie::displayMovies() {
	for (int i = 0; i << movieList.size(); ++i) {
		cout << "\n-----" << "\nYou entered..." << endl;
		cout << "\nMovie Title: " << movieList[i].title;
		cout << "\nMain Cast: " << movieList[i].castSize;
		cout << "\nCast Members: ";

		for (int i = 0; i < movieList[i].castSize; ++i) {
			cout << "\n\t" << (i + 1) << ". " << movieList[i].cast[i];
		}
		cout << "\nRating: " << movieList[i].rating << "\n-----" << endl;
	}
}

// Purpose: Recursive main method used to run app. If user's input is "Y", program executes. If "N", program terminates.
/*
void Add_Movie::run() {
	SetAnswer();
	while (answer == 'Y') {
		SetMovieTitle();
		SetCastSize();
		SetCastMembers();
		SetRating();
		SetAnswer();
		//return run(); // Recalls this function to ask for user input again
	}
	displayMovies();
}
*/

// Purpose: Recursive main method used to run app. If user's input is "Y", program executes. If "N", program terminates.
void Add_Movie::run() {
	Add_Movie newMovie;
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
