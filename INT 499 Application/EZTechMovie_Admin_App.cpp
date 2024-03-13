
/*
INT 499 Capstone for Information Technology
Week 2 - Interactive Assignment
Date: 2024-03-12
Author: Paul Oram
*/

#include <iostream>
#include <string>
#include <exception>
#include <vector>
using namespace std;

#include "EZTechMovie_Admin_App.h"


// Default constructor
EZTechMovie_Admin_App::EZTechMovie_Admin_App() {
	name = "none";
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
string EZTechMovie_Admin_App::strToUpperCase(string str) {
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
void EZTechMovie_Admin_App::SetAnswer() {
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
void EZTechMovie_Admin_App::SetMovieTitle() {
	cout << "\nMovie Title: ";
	cin.ignore();
	getline(cin, name);
}

// Purpose: Obtains user's input and sets the number of main cast members in the movie.
void EZTechMovie_Admin_App::SetCastSize() {
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
void EZTechMovie_Admin_App::SetCastMembers() {
	cast.resize(castSize);
	cout << "\nCast Members (First & Last Names):" << endl;
	cin.ignore(); // Closes previous getlin() to allow for more further inputs
	
	for (int i = 0; i < castSize; ++i) {
		cout << (i + 1) << ". ";
		getline(cin, cast[i]); // Gets user input until <ENTER> is pressed
	}
}

// Purpose: Obtains the user's input for the movie's rating.
void EZTechMovie_Admin_App::SetRating() {
	rating = "";
	bool isTrue = false;
	
	try {
		cout << "\nPlease select one of the following ratings: G, PG, PG-13, R, NC-17" << "\nEnter Movie Rating: ";
		cin >> rating;
		rating = strToUpperCase(rating); // This is done to ensure that all letters in the user's input are converted to CAPITALS to be compatible with the vector "movieRatings".

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

// Purpose: To display a movie's information in the terminal output.
void EZTechMovie_Admin_App::displayMovie() {
	castSize = cast.size();
	cout << "\n-----" << "\nYou entered..." << endl;
	cout << "\nMovie Title: " << name;
	cout << "\nMain Cast: " << castSize;
	cout << "\nCast Members: ";

	for (int i = 0; i < castSize; ++i) {
		cout << "\n\t" << (i + 1) << ". " << cast[i];
	}

	cout << "\nRating: " << rating << "\n-----" << endl;
}

// Purpose: Recursive main method used to run app. If user's input is "Y", program executes. If "N", program terminates.
void EZTechMovie_Admin_App::storeMovie() {
	SetAnswer();
	if (answer == 'Y') {
		SetMovieTitle();
		SetCastSize();
		SetCastMembers();
		SetRating();
		displayMovie();
		return storeMovie(); // Recalls this function to ask for user input again
	}
}
