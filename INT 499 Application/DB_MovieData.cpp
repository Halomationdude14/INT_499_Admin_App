
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <mysqlx/xdevapi.h>
using namespace std;

#include "EZTechMovie_Admin_App.h"




DB_MovieData::DB_MovieData() {
	msgs = {}; // Vector to hold all sys/err messages.
	tableData = {}; // Holds table data in <std> format to be sent to Menus object for display.
	input = "";
	// Vars to be processed to DB -->
	movieTitle = "";
	movieYear = -1;
	movieRating = "";
	movieNumCast = -1;
	movieNumDir = -1;
	movieCastMembers = {};
	movieDirectors = {};
	movieGenres = {}; // Stores a list of integers (indicates the index of an existing genre in the database) to be associated with the newly added movie.
}


// Resets all globally accessible values to their defaults
void DB_MovieData::setDefaultValues() {
	msgs.clear(); 
	tableData.clear();
	input = "";
	movieTitle = "";
	movieYear = -1;
	movieRating = "";
	movieNumCast = -1;
	movieNumDir = -1;
	movieCastMembers.clear();
	movieDirectors.clear();
	movieGenres.clear();
}

// Promots user for the title of the movie
void DB_MovieData::setTitle() {
	menu.displayMenu({});
	cout << "\nMovie Title: ";
	getline(cin, movieTitle);
}

// Prompts user for the year the movie was published
void DB_MovieData::setYear() {
	msgs.clear();
	int year = -1;
	
	while (year == -1) {
		menu.displayMenu(msgs);
		msgs.clear();

		cout << "\nYear [YYYY]: ";
		getline(cin, input);

		//verify year ranges! [18xx-current]

		if (!(fct.strIsInt(input))) {
			msgs.push_back("ERROR: Not a valid year!");
		}
		else {
			year = stoi(input);
		}
	}

	movieYear = year;
}

// Prompts user for the rating of the movie
void DB_MovieData::setRating() {
	msgs.clear();
	vector<string> ratings = { "G","PG","PG-13","R" };
	bool running = true;

	while (running) {
		menu.displayMenu(msgs);
		msgs.clear();

		cout << "\nRating [G,PG,PG-13,R]: ";
		getline(cin, input);
		input = fct.strToUpperCase(input);

		for (auto& i : ratings) {
			if (input == i) {
				running = false;
				break;
			}
			else {
				msgs.push_back("ERROR: Not a valid rating!");
			}
		}
	}

	movieRating = input;
}

// Prompts user for the number of cast members in the movie
void DB_MovieData::setNumCast() {
	msgs.clear();
	int numCast = -1;

	while (numCast == -1) {
		menu.displayMenu(msgs);
		msgs.clear();

		cout << "\nHow many cast members? [1-5]: ";
		getline(cin, input);

		if ( !(fct.strIsInt(input)) ) { //if entry contains non-numerical data
			msgs.push_back("ERROR: User entry was not a number!");
		}
		else if ( !(0 < stoi(input) < 6) ) { //if not between 1-5
			msgs.push_back("ERROR: User entry was not a valid number! Please enter a number [1-5].");
		}
		else {
			numCast = stoi(input);
		}
	}

	movieNumCast = numCast;
}

// Prompts user to enter the names of each main cast member
void DB_MovieData::setCast(int numCast) {
	vector<vector<string>> castMembers = {};
	vector<string> person = {};

	for (int i = 0; i < numCast; i++) {
		menu.displayMenu({});
		person.clear();

		cout << "\nCast Member #" + to_string(i + 1) + " -->\n" << endl;

		cout << "\n  First Name: ";
		getline(cin, input);
		person.push_back(input);

		cout << "Enter [~] to skip middle name entry." << endl;
		cout << "\n  Middle Name: ";
		getline(cin, input);
		if (input == "~") {
			person.push_back("NULL");
		}
		else {
			person.push_back(input);
		}

		cout << "\n  Last Name: ";
		getline(cin, input);
		person.push_back(input);

		castMembers.push_back(person);
	}

	movieCastMembers = castMembers;
}

// Prompts user for number of directors of the movie
void DB_MovieData::setNumDir() {
	msgs.clear();
	int numDir = -1;

	while (numDir == -1) {
		menu.displayMenu(msgs);
		msgs.clear();

		cout << "\nHow many directors? [1-3]: ";
		getline(cin, input);

		if (!(fct.strIsInt(input))) {
			msgs.push_back("ERROR: User entry was not a number!");
			break;
		}
		else if ( !(0 < stoi(input) < 4) ) { //if not between 1-3
			msgs.push_back("ERROR: User entry was not a valid number! Please enter a number [1-3].");
			numDir = -1;
			break;
		}
		else {
			numDir = stoi(input);
		}
	}

	movieNumDir = numDir;
}

// Prompts user to enter the names of each director
void DB_MovieData::setDir(int numDir) {
	vector<vector<string>> directors = {};
	vector<string> person = {};

	for (int i = 0; i < numDir; i++) {
		menu.displayMenu({});
		person.clear();

		cout << "\nDirector #" + to_string(i + 1) + " -->\n" << endl;

		cout << "\n  First Name: ";
		getline(cin, input);
		person.push_back(input);

		cout << "Enter [~] to skip middle name entry." << endl;
		cout << "\n  Middle Name: ";
		getline(cin, input);
		if (input == "~") {
			person.push_back("NULL");
		}
		else {
			person.push_back(input);
		}

		cout << "\n  Last Name: ";
		getline(cin, input);
		person.push_back(input);

		directors.push_back(person);
	}

	movieDirectors = directors;
}

// Prompts user to select 1 or more genres that the movie falls into.
// Also allows the user to add a genre to the database if one is missing.
void DB_MovieData::setGenre() {
	msgs.clear();
	input = "";
	vector<int> genres = {};
	bool running = true;

	// Get genre data: which genres to link to new movie (optional to add a new genre to the db)
	while (running) {
		menu.displayTable(msgs, tableData); // Display list of available genres
		msgs.clear();

		cout << "\nEnter one or more genres by their index number -->" << endl
			<< "\n  Enter[G] to add a new genre to the database."
			<< "\n  Enter[C] to continue." << endl;

		cout << "\nGenres Selected = ";
		if (genres.size() == 0) {
			cout << "NONE";
		}
		else {
			for (auto& i : genres) {
				cout << i;
			}
		}
		cout << "\nUser Input: ";
		cin >> input;

		// Verify genre selection
		if (fct.strIsInt(input)) { //if input is int...
			for (auto& i : tableData) {
				int index = stoi(input);
				if (index == stoi(i[0])) {
					genres.push_back(index); //...add to vector<int> genres
				}
			}
		}
		else { //if input is NOT int...
			input = fct.strToUpperCase(input); //...convert to string

			// Error handling
			if (input == "G") {
				//addNewGenre();
				msgs.push_back("TEST: addNewGenre() function not implemented yet.");
				break;
			}
			else if (input == "C") {
				if (genres.size() == 0) {
					msgs.push_back("ERROR [setGenre()]: No genres selected! Please select at least 1 genre for the movie before continuing.");
				}
				else {
					running = false;
				}
				break;
			}
			else {
				msgs.push_back("ERROR [setGenre()]: User input [" + input + "] is invalid!");
			}
		}
	}

	movieGenres = genres;
}

// Displays all the data the user has entered for the new movie.
void DB_MovieData::displayNewMovie() {
	menu.displayMenu(msgs);
	msgs.clear();

	cout << "Title: " << movieTitle << endl;
	cout << "Year: " << movieYear << endl;
	cout << "Rating: " << movieRating << endl;

	cout << "Cast Member(s): " << movieNumCast << endl;
	for (int i = 0; i < movieCastMembers.size(); i++) {
		cout << "Cast Member #" << i << ": ";
		for (int j = 0; j < movieCastMembers.at(i).size(); j++) {
			cout << movieCastMembers.at(i).at(j) << " ";
		}
		cout << endl;
	}

	cout << "Director(s): " << movieNumDir << endl;
	for (int i = 0; i < movieDirectors.size(); i++) {
		cout << "Director #" << i << ": ";
		for (int j = 0; j < movieDirectors.at(i).size(); j++) {
			cout << movieDirectors.at(i).at(j) << " ";
		}
		cout << endl;
	}

	cout << "Genres: ";
	for (auto i : movieGenres) {
		string index = to_string(i);
		//compare indexes from "movieGenres" to the copied data from "tbl_genres" to visually display the names of each chosen genre.
		for (auto j : tableData) {
			if (index == j[0]) { //if the indexes line up...
				cout << j[1] << " "; // ...print the name of the genre.
			}
		}
	}
	cout << endl;
}

// Called from [validationSCRN()]
// Allows the user to modify the movie data they've entered before sending it to the database.
void DB_MovieData::modifyNewMovie() {
	msgs.clear();
	input = "";
	bool notValid = true;

	while (notValid) {
		displayNewMovie();

		try {
			notValid = false; //close the loop (else reverts this for error handling)

			cout << "\nWhat would you like to change?"
				 << "\n  Enter [1] to change the Title."
				 << "\n  Enter [2] to change the Year."
				 << "\n  Enter [3] to change the Rating."
				 << "\n  Enter [4] to change the Cast Members."
				 << "\n  Enter [5] to change the Directors."
				 << "\n  Enter [6] to change the Genre(s)."
				 << "\n  Enter [~] to cancel this change request and return to the previous UI." << endl;

			cout << "\nWARNING: This process will delete all previously entered data for whichever field you choose to modify!"
				 << "\nYou will have to re-enter all data again!" << endl;

			cout << "\nUser Input: ";
			getline(cin, input);

			if (input == "1") {
				setTitle();
				break;
			}
			else if (input == "2") {
				setYear();
				break;
			}
			else if (input == "3") {
				setRating();
				break;
			}
			else if (input == "4") {
				setNumCast();
				setCast(movieNumCast);
				break;
			}
			else if (input == "5") {
				setNumDir();
				setDir(movieNumDir);
				break;
			}
			else if (input == "6") {
				setGenre();
				break;
			}
			else if (input == "~") { //abort change request
				break;
			}
			else {
				msgs.push_back("ERROR [modifyNewMovie()]: User input [" + input + "] is invalid!");
				notValid = true; //keep loop going
			}
		}
		catch (exception& ex) {
			msgs.push_back("ERROR [modifyNewMovie()]: " + string(ex.what()));
		}
	}
	
	input = ""; //reset input var before returning to validationSCRN()
}

// Final screen during the "add movie" process.
// Displays the user's entered data, asks them to confirm, allows them to modify, and asks to continue.
void DB_MovieData::validationSCRN() {
	msgs.clear();
	input = "";

	while ( !(input == "C") && !(input == "~") ) {
		
		try {
			cout << "Here's what you've entered for the new movie -->" << endl;

			displayNewMovie();

			cout << "\nAfter reviewing your entered data shown above, please choose one of the following options:"
				 << "\n  Enter [C] to confirm selection and add new movie to database."
				 << "\n  Enter [M] to modify your selection."
				 << "\n  Enter [~] to abort this process and return to the Admin Actions menu." << endl;
			cout << "\nUser Input: ";
			getline(cin, input);
			input = fct.strToUpperCase(input);

			if (input == "C") { //send to database
				//send data to DB*
				msgs.push_back("TEST: Functionality for sending data to database not implemented yet!");
				break;
			}
			else if (input == "M") { //modify
				modifyNewMovie();
				break;
			}
			else if (input == "~") { //abort
				break;
			}
			else {
				msgs.push_back("ERROR: User input [" + input + "] is invalid!");
			}

		}
		catch (const mysqlx::Error& err) {
			msgs.push_back("MYSQLX_ERROR [validationSCRN()]: " + string(err.what()));
		}
		catch (exception& ex) {
			msgs.push_back("ERROR [validationSCRN()]: " + string(ex.what()));
		}
	}
}


// Processes user requests to INSERT a new movie (and other associated info) to the database
vector<string> DB_MovieData::insertMovieData(mysqlx::Schema db) {
	setDefaultValues(); //reset global variables to default values
	mysqlx::Table genreTbl = db.getTable("tbl_genredata");
	tableData = fct.getTableData(genreTbl); //obtain data from table "tbl_genredata"

	/*
	mysqlx::Table movieTbl = db.getTable("tbl_moviedata");
	mysqlx::Table actorTbl = db.getTable("tbl_actors");
	mysqlx::Table genreTbl = db.getTable("tbl_moviecast"); //relational
	mysqlx::Table dirTbl = db.getTable("tbl_directors");
	mysqlx::Table movieDirTbl = db.getTable("tbl_moviedirectors"); //relational
	mysqlx::Table genreTbl = db.getTable("tbl_genredata");
	mysqlx::Table movieGenreTbl = db.getTable("tbl_moviegenres"); //relational
	*/

	// Obtain user input data for the new movie.
	setTitle();
	setYear();
	setRating();
	setNumCast();
	setCast(movieNumCast);
	setNumDir();
	setDir(movieNumDir);
	setGenre();

	// Display all of the user's entered data for confirmation.
	validationSCRN();

	if (input == "~") {
		msgs.clear();
		msgs.push_back("SYS: Process aborted! Movie not inserted into database.");
	}
	else {
		msgs.push_back("SYS: New movie successfully added to the database!");
	}

	return msgs;
}

// Processes user requests to UPDATE data on the database
vector<string> DB_MovieData::updateMovieData(mysqlx::Schema db) {
	setDefaultValues(); //reset global variables to default values
	// do something...

	return {};
}

// Processes user requests to DELETE data from the database
vector<string> DB_MovieData::deleteMovieData(mysqlx::Schema db) {
	setDefaultValues(); //reset global variables to default values
	// do something...

	return {};
}

