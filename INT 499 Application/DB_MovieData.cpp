
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <chrono> //handles date/time stuff
#include <mysqlx/xdevapi.h>
using namespace std;

#include "EZTechMovie_Admin_App.h"

/*
* To-Do -->
* 
* 1. Implement new function [validInput()] to the other functions.
* 2. Complete validation of date format.
* 3. In setGenre() UI...
*	- Genres Selected = outputs raw numerical format. need to output the name of each genre instead.
*	- No error message produced if user enters a number outside of [1-16].
*	- When user enters [G], it proceeds to display UI. Should redisplay same UI with TEST message instead.
*	- When user enters [C], program proceeds to next UI even if no genres have been selected.
*		- NOTE: Before UI change, I briefly saw that the UI had changed but I couldn't see how.
* 4. In validationSCRN() UI...
*	- Message "ERROR: User input [] is invalid!" generated whenever this UI is first displayed.
*	- When user enters [M], the modifyNewMovie() UI is successfully generated. In this UI, if the user enters [~] the whole process is aborted. Instead, this entry should return to the previous UI... not abort the whole process.
*/


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

// Takes in a string and verifies it is not empty, and contains no spaces prior to first char.
bool DB_MovieData::validInput() {
	if (input.empty()) {
		msgs.push_back("ERROR [validInput()]: User input is empty! Please enter a value this time...");
		return false;
	}
	else if (isspace(input[0])) {
		msgs.push_back("ERROR [validInput()]: User input [" + input + "] is invalid! Input cannot begin with a space.");
		return false;
	}
	else {
		return true;
	}
}

// Promots user for the title of the movie
void DB_MovieData::setTitle() {
	msgs.clear();
	input = "";
	bool notValid = true;

	while (notValid) {
		menu.displayMenu(msgs);
		msgs.clear();
		cout << "Movie Title: ";

		try {
			getline(cin, input);

			if (validInput()) {
				movieTitle = input;
				notValid = false;
			}
		}
		catch (exception& ex) {
			msgs.push_back("EXCEPTION [setTitle()]: " + string(ex.what()));
		}
	}
}

// Prompts user for the year the movie was published
void DB_MovieData::setYear() {
	msgs.clear();
	input = "";
	movieYear = -1;

	const chrono::system_clock::time_point now{ chrono::system_clock::now() }; //get current time
	time_t tt = chrono::system_clock::to_time_t(now); //convert to [time_t]
	tm local_tm = *localtime(&tt); //convert to [tm] with the user's relative timezone in mind

	/*
	* Manipulate [local_tm] via the following...
	* 
	* std::cout << local_tm.tm_year + 1900 << '\n';
	* std::cout << local_tm.tm_mon + 1 << '\n';
	* std::cout << local_tm.tm_mday << '\n';
	* 
	* Source = https://stackoverflow.com/questions/15957805/extract-year-month-day-etc-from-stdchronotime-point-in-c
	* 
	*/

	while (movieYear == -1) {
		menu.displayMenu(msgs);
		msgs.clear();
		cout << "NOTE: Year must be in format [YYYY] with range of [1888 - present]." << endl;
		cout << "Movie Year: ";

		try {
			getline(cin, input);

			if (validInput()) {
				if ( !(fct.strIsInt(input)) ) { //verify input is type int
					msgs.push_back("ERROR [setYear()]: User input [" + input + "] is invalid! Contains non-numerical characters.");
				}
				else if ( (1888 <= stoi(input)) && (stoi(input) <= 2024) ) { //verify date range
					movieYear = stoi(input);
				}
				else {
					msgs.push_back("ERROR [setYear()]: User input [" + input + "] is invalid! Year is not within allowed range.");
				}
			}
		}
		catch (exception& ex) {
			msgs.push_back("EXCEPTION [setYear()]: " + string(ex.what()));
		}
	}
}

// Prompts user for the rating of the movie
void DB_MovieData::setRating() {
	msgs.clear();
	input = "";
	movieRating = "";
	vector<string> ratings = { "G","PG","PG-13","R" };

	while (movieRating == "") {
		menu.displayMenu(msgs);
		msgs.clear();
		cout << "Movie Rating [G,PG,PG-13,R]: ";

		try {
			getline(cin, input);
			input = fct.strToUpperCase(input);

			if (input == "") { //user submits no input
				msgs.push_back("ERROR [setRating()]: User must enter a valid rating. Cannot be blank.");
			}
			else {
				for (auto& i : ratings) {
					if (input == i) {
						movieRating = input;
					}
				}

				if (movieRating == "") { //if user input not in vector "ratings"
					msgs.push_back("ERROR [setRating()]: User input [" + input + "] is not a valid rating!");
				}
			}
		}
		catch (exception& ex) {
			msgs.push_back("EXCEPTION [setRating()]: " + string(ex.what()));
		}
	}
}

// Prompts user for the number of cast members in the movie
void DB_MovieData::setNumCast() {
	msgs.clear();
	input = "";
	movieNumCast = -1;

	while (movieNumCast == -1) {
		menu.displayMenu(msgs);
		msgs.clear();
		cout << "How many cast members? [1-5]: ";

		try {
			getline(cin, input);

			if (input == "") { //user submits no input
				msgs.push_back("ERROR [setNumCast()]: User must enter a valid number. Cannot be blank.");
			}
			else if ( !(fct.strIsInt(input)) ) { //if not a number
				msgs.push_back("ERROR [setNumCast()]: User input [" + input + "] is invalid! Please enter a number [1-5].");
			}
			else if (((stoi(input) - 1) | (5 - stoi(input))) >= 0) { //if between 1-5 (bit opperation)
				movieNumCast = stoi(input);
			}
			else {
				msgs.push_back("ERROR [setNumCast()]: User input [" + input + "] is invalid! Please enter a number [1-5].");
			}
		}
		catch (exception& ex) {
			msgs.push_back("EXCEPTION [setNumCast()]: " + string(ex.what()));
		}
	}
}

// Prompts user to enter the names of each main cast member
void DB_MovieData::setCast(int numCast) {
	msgs.clear();
	vector<vector<string>> castMembers = {};
	vector<string> person = {};
	bool notValid = true;

	for (int i = 0; i < numCast; i++) {
		person.clear();

		notValid = true;
		while (notValid) { //first name
			try {
				menu.displayMenu(msgs);
				msgs.clear();
				cout << "Cast Member #" + to_string(i + 1) + " -->\n" << endl;
				cout << "  First Name: ";
				getline(cin, input);

				if (input == "") { //user submits no input
					msgs.push_back("ERROR [setCast()]: User must enter a valid name. Cannot be blank.");
				}
				else {
					person.push_back(input);
					notValid = false;
				}
			}
			catch (exception& ex) {
				msgs.push_back("EXCEPTION [setCast()]: " + string(ex.what()));
			}
		}

		notValid = true;
		while (notValid) { //middle name
			try {
				menu.displayMenu(msgs);
				msgs.clear();
				cout << "Cast Member #" + to_string(i + 1) + " -->\n" << endl;
				cout << "  First Name: " << person[0] << endl;
				cout << "Enter [~] to skip middle name entry." << endl;
				cout << "  Middle Name: ";
				getline(cin, input);

				if (input == "") { //user submits no input
					msgs.push_back("ERROR [setCast()]: User must enter a valid name. Cannot be blank.");
				}
				else if (input == "~") {
					person.push_back("NULL");
					notValid = false;
				}
				else {
					person.push_back(input);
					notValid = false;
				}
			}
			catch (exception& ex) {
				msgs.push_back("EXCEPTION [setCast()]: " + string(ex.what()));
			}
		}

		notValid = true;
		while (notValid) { //last name
			try {
				menu.displayMenu(msgs);
				msgs.clear();
				cout << "Cast Member #" + to_string(i + 1) + " -->\n" << endl;
				cout << "  First Name: " << person[0] << endl;
				cout << "  Middle Name: " << person[1] << endl;
				cout << "  Last Name: ";
				getline(cin, input);

				if (input == "") { //user submits no input
					msgs.push_back("ERROR [setCast()]: User must enter a valid name. Cannot be blank.");
				}
				else {
					person.push_back(input);
					notValid = false;
				}
			}
			catch (exception& ex) {
				msgs.push_back("EXCEPTION [setCast()]: " + string(ex.what()));
			}
		}

		castMembers.push_back(person);
	}

	movieCastMembers = castMembers;
}

// Prompts user for number of directors of the movie
void DB_MovieData::setNumDir() {
	msgs.clear();
	input = "";
	movieNumDir = -1;

	while (movieNumDir == -1) {
		menu.displayMenu(msgs);
		msgs.clear();
		cout << "\nHow many directors? [1-3]: ";

		try {
			getline(cin, input);

			if (input == "") { //user submits no input
				msgs.push_back("ERROR [setNumDir()]: User must enter a valid number. Cannot be blank.");
			}
			else if (!(fct.strIsInt(input))) { //if not a number
				msgs.push_back("ERROR [setNumDir()]: User input [" + input + "] is invalid! Please enter a number [1-3].");
			}
			else if (((stoi(input) - 1) | (3 - stoi(input))) >= 0) { //if between 1-3 (bit opperation)
				movieNumDir = stoi(input);
			}
			else {
				msgs.push_back("ERROR [setNumDir()]: User input [" + input + "] is invalid! Please enter a number [1-3].");
			}
		}
		catch (exception& ex) {
			msgs.push_back("EXCEPTION [setNumDir()]: " + string(ex.what()));
		}
	}
}

// Prompts user to enter the names of each director
void DB_MovieData::setDir(int numDir) {
	msgs.clear();
	vector<vector<string>> directors = {};
	vector<string> person = {};
	bool notValid = true;

	for (int i = 0; i < numDir; i++) {
		person.clear();

		notValid = true;
		while (notValid) { //first name
			try {
				menu.displayMenu(msgs);
				msgs.clear();
				cout << "Director #" + to_string(i + 1) + " -->\n" << endl;
				cout << "  First Name: ";
				getline(cin, input);

				if (input == "") { //user submits no input
					msgs.push_back("ERROR [setDir()]: User must enter a valid name. Cannot be blank.");
				}
				else {
					person.push_back(input);
					notValid = false;
				}
			}
			catch (exception& ex) {
				msgs.push_back("EXCEPTION [setDir()]: " + string(ex.what()));
			}
		}

		notValid = true;
		while (notValid) { //middle name
			try {
				menu.displayMenu(msgs);
				msgs.clear();
				cout << "Director #" + to_string(i + 1) + " -->\n" << endl;
				cout << "  First Name: " << person[0] << endl;
				cout << "Enter [~] to skip middle name entry." << endl;
				cout << "  Middle Name: ";
				getline(cin, input);

				if (input == "") { //user submits no input
					msgs.push_back("ERROR [setDir()]: User must enter a valid name. Cannot be blank.");
				}
				else if (input == "~") {
					person.push_back("NULL");
					notValid = false;
				}
				else {
					person.push_back(input);
					notValid = false;
				}
			}
			catch (exception& ex) {
				msgs.push_back("EXCEPTION [setDir()]: " + string(ex.what()));
			}
		}

		notValid = true;
		while (notValid) { //last name
			try {
				menu.displayMenu(msgs);
				msgs.clear();
				cout << "Director #" + to_string(i + 1) + " -->\n" << endl;
				cout << "  First Name: " << person[0] << endl;
				cout << "  Middle Name: " << person[1] << endl;
				cout << "  Last Name: ";
				getline(cin, input);

				if (input == "") { //user submits no input
					msgs.push_back("ERROR [setDir()]: User must enter a valid name. Cannot be blank.");
				}
				else {
					person.push_back(input);
					notValid = false;
				}
			}
			catch (exception& ex) {
				msgs.push_back("EXCEPTION [setDir()]: " + string(ex.what()));
			}
		}

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
			for (auto& i : genres) { //FIX!!!
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
	for (int i = 0; i < movieNumCast; i++) {
		cout << "  [#" << (i + 1) << "]: ";
		cout << movieCastMembers.at(i).at(0) << " ";
		if (!(movieCastMembers.at(i).at(1) == "NULL")) { //if middle name is "NULL", don't print
			cout << movieCastMembers.at(i).at(1) << " ";
		}
		cout << movieCastMembers.at(i).at(2) << endl;
	}

	cout << "Director(s): " << movieNumDir << endl;
	for (int i = 0; i < movieNumDir; i++) {
		cout << "  [#" << (i + 1) << "]: ";
		cout << movieDirectors.at(i).at(0) << " ";
		if (!(movieDirectors.at(i).at(1) == "NULL")) { //if middle name is "NULL", don't print
			cout << movieDirectors.at(i).at(1) << " ";
		}
		cout << movieDirectors.at(i).at(2) << endl;
	}

	cout << "Genres: ";
	for (auto i : movieGenres) {
		string index = to_string(i);
		string lastIndex = to_string(movieGenres.back());
		// Compare indexes from "movieGenres" to the copied data from "tbl_genres" to
		// visually display the names of each chosen genre.
		for (auto j : tableData) {

			if (index == lastIndex) { //print index WITHOUT a comma
				if (index == j[0]) { //if the indexes line up...
					cout << j[1]; //...print the name of the genre.
				}
			}
			else { //print index WITH a comma
				if (index == j[0]) { //if the indexes line up...
					cout << j[1] << ", "; //...print the name of the genre.
				}
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
			msgs.push_back("EXCEPTION [modifyNewMovie()]: " + string(ex.what()));
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

			displayNewMovie(); //display all data entered by user

			cout << "\nAfter reviewing your entered data shown above, please choose one of the following options:"
				 << "\n  Enter [M] to modify your selection."
				 << "\n  Enter [C] to confirm selection and add new movie to database."
				 << "\n  Enter [~] to abort this process and return to the Admin Actions menu." << endl;
			cout << "\nUser Input: ";
			getline(cin, input);
			input = fct.strToUpperCase(input);

			if (input == "M") { //send to database
				modifyNewMovie();
				break;
			}
			else if (input == "C") { //modify
				//send data to DB*
				msgs.push_back("TEST: Functionality for sending data to database not implemented yet!");
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
			msgs.push_back("EXCEPTION [validationSCRN()]: " + string(ex.what()));
		}
	}
	msgs.clear();
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

