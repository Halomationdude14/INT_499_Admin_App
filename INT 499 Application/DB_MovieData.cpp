
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <mysqlx/xdevapi.h>
using namespace std;

#include "EZTechMovie_Admin_App.h"

/*
* TO-DO -->
* 
* When entering actor/director names, check the DB to see if they already exist.
*	- When taking in user input for names
* 
* At the GenreSelection UI, if user enters [G] the current genre list is cleared. Keep or modify functionality?
* 
* Need to ensure the user is not capable of entering duplicate information to the database.
* For example, if "Pacific Rim" exists in the DB, then stop the user at setTitle() if they enter the same title.
* 
* Results of first test of sending info to DB -->
*	Program is capable of entering data into the proper table, but current algorithm inserts anomalous entries.
	First test involved 2 actors and 2 directors: 3 actors added (first 2 were duplicates); no directors were added.
	In tbl_moviecast, only 1 entry (27, 74) [movieID, actorID]. No entries in tbl_moviedirectors or tbl_moviegenres.
* 
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
	maxGenres = 0; //indicates the number of genres currently in the database
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

			//error handling
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
	int currYear = fct.getCurrYear(); //get the current year

	while (movieYear == -1) {
		menu.displayMenu(msgs);
		msgs.clear();
		cout << "NOTE: Year must be in format [YYYY] with range of [1888 - present]." << endl;
		cout << "\nMovie Year: ";

		try {
			getline(cin, input);

			//error handling
			if (validInput()) {
				if ( !(fct.strIsInt(input)) ) { //verify input is type int
					msgs.push_back("ERROR [setYear()]: User input [" + input + "] is invalid! Contains non-numerical characters.");
				}
				else if ( (1888 <= stoi(input)) && (stoi(input) <= currYear) ) { //verify date range
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

			//error handling
			if (validInput()) {
				input = fct.strToUpperCase(input);

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

			//error handling
			if (validInput()) {
				if (!(fct.strIsInt(input))) { //if not a number
					msgs.push_back("ERROR [setNumCast()]: User input [" + input + "] is invalid! Please enter a number [1-5].");
				}
				else if (((stoi(input) - 1) | (5 - stoi(input))) >= 0) { //if between 1-5 (bit opperation)
					movieNumCast = stoi(input);
				}
				else {
					msgs.push_back("ERROR [setNumCast()]: User input [" + input + "] is invalid! Please enter a number [1-5].");
				}
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

				//error handling
				if (validInput()) {
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

				//error handling
				if (validInput()) {
					if (input == "~") {
						person.push_back("");
						notValid = false;
					}
					else {
						person.push_back(input);
						notValid = false;
					}
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

				//error handling
				if (validInput()) {
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
		cout << "How many directors? [1-3]: ";

		try {
			getline(cin, input);

			//error handling
			if (validInput()) {
				if (!(fct.strIsInt(input))) { //if not a number
					msgs.push_back("ERROR [setNumDir()]: User input [" + input + "] is invalid! Please enter a number [1-3].");
				}
				else if (((stoi(input) - 1) | (3 - stoi(input))) >= 0) { //if between 1-3 (bit opperation)
					movieNumDir = stoi(input);
				}
				else {
					msgs.push_back("ERROR [setNumDir()]: User input [" + input + "] is invalid! Please enter a number [1-3].");
				}
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

				//error handling
				if (validInput()) {
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

				//error handling
				if (validInput()) {
					if (input == "~") {
						person.push_back("");
						notValid = false;
					}
					else {
						person.push_back(input);
						notValid = false;
					}
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

				//error handling
				if (validInput()) {
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

	if (input == "G") { //DELETE THIS AFTER IMPLEMENTATION!!!
		msgs.push_back("TEST: addNewGenre() function not implemented yet.");
	}

	input = "";
	vector<int> genres = {};
	bool running = true;
	

	// Get genre data: which genres to link to new movie (optional to add a new genre to the db)
	while (running) {
		menu.displayTable(msgs, tableData); // Display list of available genres
		msgs.clear();

		cout << "Select one or more genres for the new movie -->" << endl
			 << "  Enter [#] to add a genre (# corresponds to index of genre)." << endl
			 << "  Enter [G] to add a new genre to the database." << endl
			 << "  Enter [C] to continue." << endl;

		cout << "\nGenres Selected = ";
		if (genres.size() == 0) {
			cout << "NONE";
		}
		else {
			for (auto& i : genres) { //displays each selected genre by its name
				string index = to_string(i);
				string lastIndex = to_string(genres.back());
				
				// Compare indexes from "genres" to the copied data from "tbl_genres" to
				// visually display the names of each chosen genre.
				for (auto& j : tableData) {
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
		}

		cout << "\nUser Input: ";
		getline(cin, input);

		// Error handling + data processing
		if (validInput()) {

			// Verify genre selection
			if (fct.strIsInt(input)) { //if input is int
				//if ( (1 <= stoi(input)) && (stoi(input) <= maxGenres) ) { //input is between 1 and the max number of genres currently in the database
				if ( ((stoi(input) - 1) | (maxGenres - stoi(input))) >= 0 ) { //input is between 1 and the max number of genres currently in the database
					for (auto& i : tableData) {
						if (input == i[0]) {
							int counter = 0;

							for (auto& j : genres) { //verify that user input has not been entered already
								if (stoi(input) == j) {
									msgs.push_back("ERROR [setGenre()]: Genre with index [" + input + "] has already been selected! Cannot be added twice.");
									counter++;
								}
							}

							if (counter == 0) {
								genres.push_back(stoi(input)); //add user selection if no duplicates exist
							}
						}
					}
				}
				else {
					msgs.push_back("ERROR [setGenre()]: User input [" + input + "] is invalid! Input does not correlate to a genre in the database.");
				}
			}

			else { //if input is NOT int
				input = fct.strToUpperCase(input);

				if (input == "G") {
					//addNewGenre();
					running = false; //send back to insertMovieData() to refresh tableData with newly added genre
				}
				else if (input == "C") {
					if (genres.size() == 0) {
						msgs.push_back("ERROR [setGenre()]: No genres selected! Please select at least 1 genre for the movie before continuing.");
					}
					else {
						running = false;
					}
				}
				else {
					msgs.push_back("ERROR [setGenre()]: User input [" + input + "] is invalid!");
				}
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
		if (!(movieCastMembers.at(i).at(1) == "")) { //if middle name is empty, don't print
			cout << movieCastMembers.at(i).at(1) << " ";
		}
		cout << movieCastMembers.at(i).at(2) << endl;
	}

	cout << "Director(s): " << movieNumDir << endl;
	for (int i = 0; i < movieNumDir; i++) {
		cout << "  [#" << (i + 1) << "]: ";
		cout << movieDirectors.at(i).at(0) << " ";
		if (!(movieDirectors.at(i).at(1) == "")) { //if middle name is empty, don't print
			cout << movieDirectors.at(i).at(1) << " ";
		}
		cout << movieDirectors.at(i).at(2) << endl;
	}

	cout << "Genres: ";
	for (auto& i : movieGenres) {
		string index = to_string(i);
		string lastIndex = to_string(movieGenres.back());
		// Compare indexes from "movieGenres" to the copied data from "tbl_genres" to
		// visually display the names of each chosen genre.
		for (auto& j : tableData) {

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

			//error handling + data processing
			if (validInput()) {
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
			}
			else { //if input is invalid...
				notValid = true; //...keep loop going
			}
		}
		catch (exception& ex) {
			msgs.push_back("EXCEPTION [modifyNewMovie()]: " + string(ex.what()));
		}
	}
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

			//error handling
			if (validInput()) {
				input = fct.strToUpperCase(input);

				if (input == "M") { //send to database
					modifyNewMovie();
					input = ""; //reset input
				}
				else if (input == "C" || input == "~") { //modify OR abort
					break;
				}
				else {
					msgs.push_back("ERROR [validationSCRN()]: User input [" + input + "] is invalid!");
				}
			}
		}
		catch (exception& ex) {
			msgs.push_back("EXCEPTION [validationSCRN()]: " + string(ex.what()));
		}
	}
}

// After all data is obtained for a new movie, that data is sent to the database.
void DB_MovieData::sendMovieToDB(mysqlx::Schema db) {
	try {
		mysqlx::Table movieTbl = db.getTable("tbl_moviedata");
		mysqlx::Table actorTbl = db.getTable("tbl_actors");
		mysqlx::Table movieActorTbl = db.getTable("tbl_moviecast"); //relational
		mysqlx::Table dirTbl = db.getTable("tbl_directors");
		mysqlx::Table movieDirTbl = db.getTable("tbl_moviedirectors"); //relational
		mysqlx::Table movieGenreTbl = db.getTable("tbl_moviegenres"); //relational
		mysqlx::Table genreTbl = db.getTable("tbl_genredata");

		// Source URL: https://stackoverflow.com/questions/75135560/x-devapi-batch-insert-extremely-slow

		// Link [TableInsert] object to [Table] object and specify which columns are targets of the INSERT statment.
		mysqlx::TableInsert tblInsertStmt = movieTbl.insert("movieTitle", "movieYear", "numCast", "movieRating");
		// Specify the values being inserted in the columns specified above.
		tblInsertStmt.values(movieTitle, movieYear, movieNumCast, movieRating);
		// Execute the [TableInsert] object (i.e., send data to database)
		tblInsertStmt.execute();

		movieTbl = db.getTable("tbl_moviedata"); //refresh Table object with newly added data
		tableData = fct.getTableData(movieTbl);
		int movieID = stoi(tableData.back().at(0)); //get movieID of most recently added movie

		//repeat process for remaining tables...
		tblInsertStmt = actorTbl.insert("actor_Fname", "actor_Mname", "actor_Lname");
		for (auto& i : movieCastMembers) {
			tblInsertStmt.values(i[0], i[1], i[2]);
			tblInsertStmt.execute();
		}

		actorTbl = db.getTable("tbl_actors"); //refresh Table object with newly added data
		tableData = fct.getTableData(actorTbl);
		vector<int> actorIDs = {};
		for (auto& i : movieCastMembers) { //get actor IDs for each newly added actor
			for (auto& j : tableData) {
				if ( (i[0] == j[1]) && (i[1] == j[2]) && (i[2] == j[3]) ) { //if first, middle, and last names match...
					actorIDs.push_back(stoi(j[0])); //...record actor ID
				}
				else {
					msgs.push_back("ERROR [sendMovieToDB()]: Cannot find this person in the database: " + i[0] + " " + i[1] + " " + i[2]
						+ "\n                          Association between new movie and this actor cannot be established!");
				}
			}
		}

		tblInsertStmt = movieActorTbl.insert("movieID", "actorID");
		for (auto& i : actorIDs) {
			tblInsertStmt.values(movieID, i);
			tblInsertStmt.execute();
		}

		tblInsertStmt = dirTbl.insert("director_Fname", "director_Mname", "director_Lname");
		for (auto& i : movieDirectors) {
			tblInsertStmt.values(i[0], i[1], i[2]);
			tblInsertStmt.execute();
		}

		dirTbl = db.getTable("tbl_directors"); //refresh Table object with newly added data
		tableData = fct.getTableData(dirTbl);
		vector<int> directorIDs = {};
		for (auto& i : movieDirectors) { //get director IDs for each newly added director
			for (auto& j : tableData) {
				if ((i[0] == j[1]) && (i[1] == j[2]) && (i[2] == j[3])) { //if first, middle, and last names match...
					directorIDs.push_back(stoi(j[0])); //...record actor ID
				}
				else {
					msgs.push_back("ERROR [sendMovieToDB()]: Cannot find this person in the database: " + i[0] + " " + i[1] + " " + i[2]
						+ "\n                          Association between new movie and this director cannot be established!");
				}
			}
		}

		tblInsertStmt = movieDirTbl.insert("movieID", "directorID");
		for (auto& i : directorIDs) {
			tblInsertStmt.values(movieID, i);
			tblInsertStmt.execute();
		}

		tblInsertStmt = movieGenreTbl.insert("movieID", "genreID");
		for (auto& i : movieGenres) {
			tblInsertStmt.values(movieID, i);
			tblInsertStmt.execute();
		}
	}
	catch (const mysqlx::Error& err) {
		msgs.push_back("MYSQLX_ERROR [sendMovieToDB()]: " + string(err.what()));
	}
	catch (exception& ex) {
		msgs.push_back("EXCEPTION [sendMovieToDB()]: " + string(ex.what()));
	}
}

// Processes user requests to INSERT a new movie (and other associated info) to the database
vector<string> DB_MovieData::insertMovieData(mysqlx::Schema db) {
	setDefaultValues(); //reset global variables to default values
	
	// Obtain user input data for the new movie.
	setTitle();
	setYear();
	setRating();
	setNumCast();
	setCast(movieNumCast);
	setNumDir();
	setDir(movieNumDir);
	
	input = ""; //reset input
	while ( !(input == "C") ) { //loop required due to 'add genre' feature
		mysqlx::Table genreTbl = db.getTable("tbl_genredata");
		tableData = fct.getTableData(genreTbl); //obtain data from table "tbl_genredata"
		maxGenres = tableData.size();
		setGenre();
	}

	// Display all of the user's entered data for confirmation.
	validationSCRN();

	if (input == "~") { // Abort process and return to Admin Actions UI
		msgs.clear();
		msgs.push_back("SYS: Process aborted! Movie not inserted into database.");
	}
	else {
		sendMovieToDB(db); // Send all movie data to database.
		msgs.clear();
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

