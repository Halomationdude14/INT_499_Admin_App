
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>
#include <mysqlx/xdevapi.h>
using namespace std;

#include "EZTechMovie_Admin_App.h"

/*
* TO-DO -->
* 
* 1. Update how program sets actors/directors. If this was a real database, those tables would be VERY large! It would be unreasonable to have the user scroll through hundreds/thousands of people to select.
*    A better approach would be to implement a search feature -->
*		1. User may search by first, middle, and/or last names.
*		2. Special formatting is required since user entry is obtained from a single line.
*			[2.1] Use a SPACE to separate each name for the search.
				  For example, entering "John Wayne Patrick" would search for a first name of "John", middle name of "Wayne", and last name of "Patrick".
				  NOTE: User may skip searching for either first/middle/last name by simply pressing SPACE twice. For example, entering "John  " would only search for people with the first name of "John".
*			[2.2] Use an UNDERSCORE to indicate that there is a space in a single name for special cases where a person may have 2+ words as their first/middle/last name.
				  For example, entering "John_Vann D. Goh" searches for any first names that match "John Vann".
*			[2.3] User may enter a short name to get a list of people with those characters in their name.
				  For example, entering "Mar D B" would display a list of people who's first names start with "Mar", who's middle names start with "D", and who's last names start with "B".
*		3. Program must ignore possible input errors: entering more than 3 names for one person, entering too many spaces, entering too many underscores, etc.
* 
* 2. Add a title to the header indicating that the user in in the process of "adding a new movie" to the database.
* 3. When adding new genres to the database, program does NOT check for duplicate entries first.
* 4. When selecting genres to link to the new movie, add an option to CLEAR the user selection and start over (in case user makes a mistake).
* 5. Apply similar changes to [validationSCRN()] function which were done to [setTitle()] and [setGenre()]. Incorporate Schema object to reduce on code.
* 
*/



DB_MovieData::DB_MovieData() {
	msgs = {};				// Stores all sys/err messages.
	tableData = {};			// vector<vector<string>> var that stores converted table data from the database; can be sent to Menus object for display.
	tblIndexes = {};		// Stores list of indexes (i.e. 1, 2, 3, etc...) from a given table.
	input = "";				// Generic string var used to store user input.

	// ##### Data to be Processed to the Database #####
	movieTitle = "";
	movieYear = -1;
	movieRating = "";
	movieNumCast = -1;
	movieNumDir = -1;

	// These 2 vector store actors/directors in the following format.
	// Format =  [index, firstName, middleName, lastName]
	movieCastMembers = {};
	movieDirectors = {};

	movieGenreIDs = {};		// Vector of integers to be linked to the new movie: ints correspond to the index of an existing genre in the database.
	movieGenreNames = {};	// Stores a list of genre names in <std::string> format. Each name corresponds to each index stored in [movieGenreIDs] respectively.
	// ################################################
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
	movieGenreIDs.clear();
	movieGenreNames.clear();
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

// Prompts user to enter first, middle, and last names for a single person.
vector<string> DB_MovieData::newPerson() {
	vector<string> person = {};
	bool notValid = true;

	// First name
	while (notValid) {
		try {
			menu.displayMenu(msgs);
			msgs.clear();
			cout << "  First Name: ";
			getline(cin, input);

			// Error handling
			if (validInput()) {
				person.push_back(input);
				notValid = false;
			}
		}
		catch (exception& ex) {
			msgs.push_back("EXCEPTION [newPerson()]: " + string(ex.what()));
		}
	}

	notValid = true;
	// Middle name
	while (notValid) { 
		try {
			menu.displayMenu(msgs);
			msgs.clear();
			cout << "  First Name: " << person[0] << endl
				 << "NOTE: Enter [~] to skip middle name entry." << endl
				 << "  Middle Name: ";
			getline(cin, input);

			// Error handling
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
			msgs.push_back("EXCEPTION [newPerson()]: " + string(ex.what()));
		}
	}

	notValid = true;
	// Last name
	while (notValid) {
		try {
			menu.displayMenu(msgs);
			msgs.clear();
			cout << "  First Name: " << person[0] << endl;

			// If user chose not to enter middle name, display "N/A".
			if (person[1].empty()) {
				cout << "  Middle Name: N/A" << endl;
			}
			else {
				cout << "  Middle Name: " << person[1] << endl;
			}

			cout << "  Last Name: ";
			getline(cin, input);

			// Error handling
			if (validInput()) {
				person.push_back(input);
				notValid = false;
			}
		}
		catch (exception& ex) {
			msgs.push_back("EXCEPTION [newPerson()]: " + string(ex.what()));
		}
	}

	return person;
}

// Promots user for the title of the movie.
void DB_MovieData::setTitle(mysqlx::Schema db) {
	msgs.clear();
	tblIndexes.clear();
	input = "";
	movieTitle = "";
	bool notValid = true;
	bool duplicate = false;


	while (notValid) {
		mysqlx::Table movieTbl = db.getTable("tbl_moviedata");
		tableData = fct.getTableData(movieTbl); // Obtain data from table {tbl_moviedata}.

		// Record existing movie titles from table {tbl_moviedata}.
		for (auto& i : tableData) {
			tblIndexes.push_back(i[1]); // NOTE: Reusing this variable to store titles instead of indexes.
		}

		menu.displayMenu(msgs);
		msgs.clear();

		cout << "Movie Title: ";

		try {
			getline(cin, input);

			// Error handling + data processing
			if (validInput()) {

				for (auto& i : tblIndexes) { // Verify that user entry doesn't exist in database.
					string newTitle = fct.strToLowerCase(input);
					string oldTitle = fct.strToLowerCase(i);
					if (newTitle == oldTitle) {
						duplicate = true;
					}
				}

				if (!(duplicate == true)) { // If no duplicate...
					movieTitle = input;
					notValid = false;
				}

				while (duplicate == true) { // If duplicate...
					msgs.push_back("WARNING: Duplicate found! A movie title [" + input + "] already exists in the database.");
					menu.displayMenu(msgs);
					msgs.clear();

					string title = input; // Record user input as title for new movie.

					cout << "Would you like to keep this title or enter a new one?" << endl
						<< "  [1] Keep duplicate title." << endl
						<< "  [2] Enter new title." << endl;

					cout << "\nUser Input: ";
					getline(cin, input);

					if (validInput()) {
						if (input == "1") {
							duplicate = false;
							movieTitle = title;
							notValid = false;
						}
						else if (input == "2") {
							duplicate = false; // Send back to [insertMovieData()] to reprompt the user for a different movie title.
						}
						else {
							msgs.push_back("ERROR [setTitle()]: User input [" + input + "] is invalid!");
						}
					}
				}
				
			}
		}

		catch (exception& ex) {
			msgs.push_back("EXCEPTION [setTitle()]: " + string(ex.what()));
		}
		catch (const mysqlx::Error& err) {
			msgs.push_back("MYSQLX_ERROR [setTitle()]: " + string(err.what()));
		}
	}
}

// Prompts user for the year the movie was published.
void DB_MovieData::setYear() {
	msgs.clear();
	input = "";
	movieYear = -1;
	int currYear = fct.getCurrYear(); // Get the current year.

	while (movieYear == -1) {
		menu.displayMenu(msgs);
		msgs.clear();
		cout << "NOTE: Year must be in format [YYYY] with range of [1888 - present]." << endl;
		cout << "\nMovie Year: ";

		try {
			getline(cin, input);

			// Error handling + data processing
			if (validInput()) {
				if ( !(fct.strIsInt(input)) ) { // Verify input is type int.
					msgs.push_back("ERROR [setYear()]: User input [" + input + "] is invalid! Contains non-numerical characters.");
				}
				else if ( (1888 <= stoi(input)) && (stoi(input) <= currYear) ) { // Verify date range.
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

// Prompts user for the rating of the movie.
void DB_MovieData::setRating() {
	msgs.clear();
	input = "";
	movieRating = "";
	vector<string> ratings = { "G","PG","PG-13","PG13","NC-17","NC17","R" };

	while (movieRating.empty()) {
		menu.displayMenu(msgs);
		msgs.clear();
		cout << "Movie Rating [G,PG,PG-13,NC-17,R]: ";

		try {
			getline(cin, input);

			// Error handling + data processing
			if (validInput()) {
				input = fct.strToUpperCase(input);

				for (auto& i : ratings) {
					if (input == i) {
						if (input == "PG13") {
							movieRating = "PG-13";
						}
						else if (input == "NC17") {
							movieRating = "NC-17";
						}
						else {
							movieRating = input;
						}
					}
				}

				if (movieRating.empty()) { // If user input not in vector [ratings].
					msgs.push_back("ERROR [setRating()]: User input [" + input + "] is not a valid rating!");
				}
			}
		}

		catch (exception& ex) {
			msgs.push_back("EXCEPTION [setRating()]: " + string(ex.what()));
		}
	}
}

// Prompts user for the number of cast members in the movie.
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

			// Error handling + data processing
			if (validInput()) {
				if ( !(fct.strIsInt(input)) ) { // If not a number...
					msgs.push_back("ERROR [setNumCast()]: User input [" + input + "] is not a number! Please enter a number [1-5].");
				}
				else {
					if (((stoi(input) - 1) | (5 - stoi(input))) >= 0) { // If number is between 1-5 (bit opperation).
						movieNumCast = stoi(input);
					}
					else {
						msgs.push_back("ERROR [setNumCast()]: User input [" + input + "] is not within the allowed numerical range! Please enter a number [1-5].");
					}
				}
			}
		}

		catch (exception& ex) {
			msgs.push_back("EXCEPTION [setNumCast()]: " + string(ex.what()));
		}
	}
}

// Allows the user to add a new actor to the database.
void DB_MovieData::addNewCast(mysqlx::Table tbl) {
	vector<string> newActor = newPerson();
	vector<string> lowercase = { fct.strToLowerCase(newActor[0]), fct.strToLowerCase(newActor[1]), fct.strToLowerCase(newActor[2]) };
	vector<string> oldActor = {}; // Stores a single actor from the database (used for comparison).
	bool duplicate = false;

	// Compare new actor to existing actors: verify no duplicates.
	for (auto& i : tableData) {
		oldActor = { fct.strToLowerCase(i[1]), fct.strToLowerCase(i[2]), fct.strToLowerCase(i[3]) };
		if (lowercase == oldActor) {
			duplicate = true;

			string name = newActor[0];
			if (!(newActor[1].empty())) {
				name.append(" " + newActor[1]);
			}
			name.append(" " + newActor[2]);

			msgs.push_back("ERROR [addNewCast()]: Duplication error! The actor [" + name + "] already exists in the database.");
		}
	}

	// If no duplicates are found, add new actor to database and break the loop.
	if (duplicate == false) {
		try {
			mysqlx::TableInsert tblInsertStmt = tbl.insert("actor_Fname", "actor_Mname", "actor_Lname");
			tblInsertStmt.values(newActor[0], newActor[1], newActor[2]).execute();
			msgs.push_back("SYS: Actor successfully added to the database!");
		}
		catch (const mysqlx::Error& err) {
			msgs.push_back("MYSQLX_ERROR [addNewCast()]: " + string(err.what()));
		}
	}
}

// Prompts user to enter the names of each main cast member.
void DB_MovieData::setCast(mysqlx::Schema db) {
	msgs.clear();
	int counter = movieCastMembers.size() + 1;
	bool running = true;


	while (running) {
		mysqlx::Table actorTbl = db.getTable("tbl_actors");
		tableData = fct.getTableData(actorTbl); // Obtain data from table {tbl_actors}.

		// Record indexes from table {tbl_actors}.
		for (auto& j : tableData) {
			tblIndexes.push_back(j[0]);
		}

		menu.displayTable(msgs, tableData); // Display list of available indexes for table {tbl_actors}.
		msgs.clear();

		cout << "Actor (" << counter << "/" << movieNumCast << ") -->" << endl
				<< "  [#] Select an actor (# corresponds to actor ID)." << endl
				<< "  [N] Add a new actor to the database." << endl
				<< "\nUser Input: ";
		getline(cin, input);

		// Error handling + data processing
		if (validInput()) {

			if (fct.strIsInt(input)) { // If input is int...

				if ( find(tblIndexes.begin(), tblIndexes.end(), input) != tblIndexes.end() ) { // If user input == existing index in table...

					vector<string> person = tableData.at(stoi(input)-1); // This action creates a person with format [index, firstName, middleName, lastName].

					// Verify that the chosen actor has not already been selected previously by the user.
					if ( find(movieCastMembers.begin(), movieCastMembers.end(), person) != movieCastMembers.end() ) {
						msgs.push_back("ERROR [setCast()]: Actor with ID [" + input + "] has already been selected! Cannot be added twice.");
					}
					else {
						movieCastMembers.push_back(person); // Add user selection if no duplicates exist.
						running = false;
					}
				}
				else {
					msgs.push_back("ERROR [setCast()]: User input [" + input + "] is invalid! Input does not correlate to any Actor IDs in the database.");
				}
			}

			else { // If input is NOT int...
				input = fct.strToUpperCase(input);

				if (input == "N") { // Obtain name for new actor, and verify that they don't exist in table {tbl_actors}
					addNewCast(actorTbl);
				}
				else {
					msgs.push_back("ERROR [setCast()]: User input [" + input + "] is invalid!");
				}
			}
		}
	}
}

// Prompts user for number of directors of the movie.
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

			// Error handling + data processing
			if (validInput()) {
				if (!(fct.strIsInt(input))) { // If not a number...
					msgs.push_back("ERROR [setNumDir()]: User input [" + input + "] is not a number! Please enter a number [1-3].");
				}
				else {
					if (((stoi(input) - 1) | (3 - stoi(input))) >= 0) { // If number is between 1-3 (bit opperation).
						movieNumDir = stoi(input);
					}
					else {
						msgs.push_back("ERROR [setNumDir()]: User input [" + input + "] is not within the allowed numberical range! Please enter a number [1-3].");
					}
				}
			}
		}

		catch (exception& ex) {
			msgs.push_back("EXCEPTION [setNumDir()]: " + string(ex.what()));
		}
	}
}

// Allows the user to add a new director to the database.
void DB_MovieData::addNewDir(mysqlx::Table tbl) {
	vector<string> newDir = newPerson();
	vector<string> lowercase = { fct.strToLowerCase(newDir[0]), fct.strToLowerCase(newDir[1]), fct.strToLowerCase(newDir[2]) };
	vector<string> oldDir = {}; // Stores a single director from the database (used for comparison).
	bool duplicate = false;

	// Compare new director to existing directors: verify no duplicates.
	for (auto& i : tableData) {
		oldDir = { fct.strToLowerCase(i[1]), fct.strToLowerCase(i[2]), fct.strToLowerCase(i[3]) };
		if (lowercase == oldDir) {
			duplicate = true;

			string name = newDir[0];
			if ( !(newDir[1].empty()) ) {
				name.append(" " + newDir[1]);
			}
			name.append(" " + newDir[2]);

			msgs.push_back("ERROR [addNewDir()]: Duplication error! The director [" + name + "] already exists in the database.");
		}
	}

	// If no duplicates are found, add new director to database and break the loop.
	if (duplicate == false) {
		try {
			mysqlx::TableInsert tblInsertStmt = tbl.insert("director_Fname", "director_Mname", "director_Lname");
			tblInsertStmt.values(newDir[0], newDir[1], newDir[2]).execute();
			msgs.push_back("SYS: Director successfully added to the database!");
		}
		catch (const mysqlx::Error& err) {
			msgs.push_back("MYSQLX_ERROR [addNewDir()]: " + string(err.what()));
		}
	}
}

// Prompts user to enter the names of each director.
void DB_MovieData::setDir(mysqlx::Schema db) {
	msgs.clear();
	int counter = movieDirectors.size() + 1;
	bool running = true;


	while (running) {
		mysqlx::Table directorTbl = db.getTable("tbl_directors");
		tableData = fct.getTableData(directorTbl); // Obtain data from table {tbl_directors}.

		// Record indexes from table {tbl_directors}.
		for (auto& j : tableData) {
			tblIndexes.push_back(j[0]);
		}

		menu.displayTable(msgs, tableData); // Display list of available indexes for table {tbl_directors}.
		msgs.clear();

		cout << "Director (" << counter << "/" << movieNumDir << ") -->" << endl
			<< "  [#] Select a director (# corresponds to director ID)." << endl
			<< "  [N] Add a new director to the database." << endl
			<< "\nUser Input: ";
		getline(cin, input);

		// Error handling + data processing
		if (validInput()) {

			if (fct.strIsInt(input)) { // If input is int...

				if (find(tblIndexes.begin(), tblIndexes.end(), input) != tblIndexes.end()) { // If user input == existing index in table...

					vector<string> person = tableData.at(stoi(input) - 1); // This action creates a person with format [index, firstName, middleName, lastName].

					// Verify that the chosen director has not already been selected previously by the user.
					if (find(movieDirectors.begin(), movieDirectors.end(), person) != movieDirectors.end()) {
						msgs.push_back("ERROR [setDir()]: Director with ID [" + input + "] has already been selected! Cannot be added twice.");
					}
					else {
						movieDirectors.push_back(person); // Add user selection if no duplicates exist.
						running = false;
					}
				}
				else {
					msgs.push_back("ERROR [setDir()]: User input [" + input + "] is invalid! Input does not correlate to any director IDs in the database.");
				}
			}

			else { // If input is NOT int...
				input = fct.strToUpperCase(input);

				if (input == "N") { // Obtain name for new director, and verify that they don't exist in table {tbl_directors}
					addNewDir(directorTbl);
				}
				else {
					msgs.push_back("ERROR [setDir()]: User input [" + input + "] is invalid!");
				}
			}
		}
	}
}

// Allows the user to add a new genre to the database.
void DB_MovieData::addNewGenre(mysqlx::Table tbl) {
	msgs.clear();
	bool running = true;
	string genre = "";

	// Obtain user input.
	while (running) {
		try {
			menu.displayMenu(msgs);
			msgs.clear();
			input = "";

			cout << "\nEnter the genre you would like to add to the database -->" << endl;

			cout << "\nUser Input: ";
			getline(cin, input);

			// Error handling + data processing.
			if (validInput()) {
				genre = input;
				running = false;
			}
		}

		catch (exception& ex) {
			msgs.push_back("EXCEPTION [addNewGenre()]: " + string(ex.what()));
		}
	}

	// Send new genre to the table {tbl_genredata}.
	try {
		mysqlx::TableInsert tblInsertStmt = tbl.insert("genreTitle").values(genre);
		tblInsertStmt.execute();
	}
	catch (const mysqlx::Error& err) {
		msgs.push_back("MYSQLX_ERROR [addNewGenre()]: " + string(err.what()));
	}
	
}

// Prompts user to select 1 or more genres that the movie falls into.
// Also allows the user to add a genre to the database if one is missing.
void DB_MovieData::setGenre(mysqlx::Schema db) {
	msgs.clear();
	input = "";
	vector<int> genreIDs = {};
	vector<string> genreNames = {};
	bool running = true;


	// Get genre data: which genres to link to new movie (optional to add a new genre to the db).
	while (running) {
		
		try {
			mysqlx::Table genreTbl = db.getTable("tbl_genredata");
			tableData = fct.getTableData(genreTbl); // Obtain data from table {tbl_genredata}.
			menu.displayTable(msgs, tableData); // Display list of available genres.
			msgs.clear();

			cout << "Select one or more genres for the new movie -->" << endl
				<< "  [#] Select a genre (# corresponds to index of genre)." << endl
				<< "  [G] Add a new genre to the database." << endl
				<< "  [C] Confirm selection and continue." << endl;

			cout << "\nGenres Selected = ";
			if (genreIDs.size() == 0 && movieGenreIDs.size() == 0) { // If no genres have been selected...
				cout << "NONE";
			}
			else {
				for (auto& i : movieGenreNames) { // Displays each genre (by name) that the user has selected previously.
					string last = movieGenreNames.back();

					if (i == last && genreNames.empty()) { // Print WITHOUT comma.
						cout << i;
					}
					else { // Print WITH comma.
						cout << i << ", ";
					}
				}

				for (auto& i : genreNames) { // Displays each genre (by name) that the user has selected recently.
					string last = genreNames.back();

					if (i == last) { // Print WITHOUT comma.
						cout << i;
					}
					else { // Print WITH comma.
						cout << i << ", ";
					}
				}
			}

			cout << "\nUser Input: ";
			getline(cin, input);

			// Error handling + data processing.
			if (validInput()) {

				// Verify genre selection.
				if (fct.strIsInt(input)) { // If input is int...
					bool validIndex = false;

					for (auto& i : tableData) { // Verify that user input corresponds to an existing index in the table {tbl_genredata}.
						if (input == i[0]) { // If input == index...
							validIndex = true;

							// This statement searches through [movieGenreIDs] and [genreIDs] to see if the user has already selected the genre associated with the user's last input.
							if (find(movieGenreIDs.begin(), movieGenreIDs.end(), stoi(input)) != movieGenreIDs.end() ||
								find(genreIDs.begin(), genreIDs.end(), stoi(input)) != genreIDs.end()) {
								msgs.push_back("ERROR [setGenre()]: Genre with index [" + input + "] has already been selected! Cannot be added twice.");
							}
							else {
								genreIDs.push_back(stoi(input));
								genreNames.push_back(i[1]);
							}
						}
					}

					if (validIndex == false) { // If input is NOT in the table {tbl_genredata}...
						msgs.push_back("ERROR [setGenre()]: User input [" + input + "] is not within the allowed numerical range! Please enter a number between[1-" + to_string(tableData.size()) + "].");
					}
				}

				else { // If input is NOT int...
					input = fct.strToUpperCase(input);

					if (input == "G") {
						addNewGenre(genreTbl); // Add new genre to the database.
					}
					else if (input == "C") {
						if (genreIDs.size() == 0 && movieGenreIDs.size() == 0) {
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

		catch (const mysqlx::Error& err) {
			msgs.push_back("MYSQLX_ERROR [setGenre()]: " + string(err.what()));
		}
		catch (exception& ex) {
			msgs.push_back("EXCEPTION [setGenre()]: " + string(ex.what()));
		}
	}

	for (auto& i : genreIDs) {
		movieGenreIDs.push_back(i);
	}
	for (auto& i : genreNames) {
		movieGenreNames.push_back(i);
	}
}

// Displays all the data the user has entered for the new movie.
void DB_MovieData::displayNewMovie() {
	menu.displayMenu(msgs);
	msgs.clear();

	cout << "Here's what you've entered for the new movie -->" << endl << endl;
	cout << "  Title: " << movieTitle << endl;
	cout << "  Year: " << movieYear << endl;
	cout << "  Rating: " << movieRating << endl;

	cout << "  Cast Member(s): " << movieNumCast << endl;
	for (int i = 0; i < movieNumCast; i++) {
		cout << "    [#" << (i + 1) << "]: ";
		cout << movieCastMembers.at(i).at(1) << " ";
		if ( !(movieCastMembers.at(i).at(2).empty()) ) { // If middle name is empty, don't print.
			cout << movieCastMembers.at(i).at(2) << " ";
		}
		cout << movieCastMembers.at(i).at(3) << endl;
	}

	cout << "  Director(s): " << movieNumDir << endl;
	for (int i = 0; i < movieNumDir; i++) {
		cout << "    [#" << (i + 1) << "]: ";
		cout << movieDirectors.at(i).at(1) << " ";
		if ( !(movieDirectors.at(i).at(2).empty()) ) { // If middle name is empty, don't print.
			cout << movieDirectors.at(i).at(1) << " ";
		}
		cout << movieDirectors.at(i).at(3) << endl;
	}

	cout << "  Genre(s): ";
	for (auto& i : movieGenreNames) {
		string curr = i;
		string lastItem = movieGenreNames.back();

		if (curr == lastItem) { // Print WITHOUT comma.
			cout << i;
		}
		else { // Print WITH comma.
			cout << i << ", ";
		}
	}

	cout << endl;
}

// Called from [validationSCRN()].
// Allows the user to modify the movie data they've entered before sending it to the database.
void DB_MovieData::modifyNewMovie(mysqlx::Schema db) {
	msgs.clear();
	input = "";
	bool notValid = true;

	while (notValid) {
		try {
			displayNewMovie();
			notValid = false; // Close the loop (if an error is caught, this value is set to TRUE).

			cout << "\nWhat would you like to change?"
				<< "\n  [1] Title"
				<< "\n  [2] Year"
				<< "\n  [3] Rating"
				<< "\n  [4] Cast Member(s)"
				<< "\n  [5] Director(s)"
				<< "\n  [6] Genre(s)"
				<< "\n  [~] Cancel this change request and return to the previous UI." << endl;

			cout << "\nWARNING: This process will delete all previously entered data for whichever field you choose to modify!"
				 << "\nYou will have to re-enter all data for any chosen field again!" << endl;

			cout << "\nUser Input: ";
			getline(cin, input);

			// Error handling + data processing
			if (validInput()) {
				input = fct.strToUpperCase(input);

				if (input == "1") {
					movieTitle = "";
					while (movieTitle == "") {
						setTitle(db);
					}
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
					movieCastMembers.clear();
					setNumCast();
					while (movieCastMembers.size() < movieNumCast) {
						setCast(db);
					}
					break;
				}
				else if (input == "5") {
					movieDirectors.clear();
					setNumDir();
					while (movieDirectors.size() < movieNumDir) {
						setDir(db);
					}
					break;
				}
				else if (input == "6") {
					movieGenreIDs.clear();
					movieGenreNames.clear();
					input = "";
					while ( !(input == "C") ) {
						setGenre(db);
					}
					break;
				}
				else if (input == "~") { // Abort change request.
					break;
				}
				else { // If input is invalid (contains chars but not valid ones) keep loop going.
					notValid = true;
					if (fct.strIsInt(input)) { // [Input] contains invalid number(s).
						msgs.push_back("ERROR [modifyNewMovie()]: User input [" + input + "] is not within the allowed numerical range!");
					}
					else { // [Input] contains invalid alphanumerical character(s).
						msgs.push_back("ERROR [modifyNewMovie()]: User input [" + input + "] is invalid!");
					}
					
				}
			}
			else { // If input is invalid (has <SPACE> or is empty) keep loop going.
				notValid = true;
				// NOTE: Error message handled by [validInput()].
			}
		}

		catch (exception& ex) {
			msgs.push_back("EXCEPTION [modifyNewMovie()]: " + string(ex.what()));
		}
		catch (const mysqlx::Error& err) {
			msgs.push_back("MYSQLX_ERROR [modifyNewMovie()]: " + string(err.what()));
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
			displayNewMovie(); // Display all data entered by user.

			cout << "\nReview the information shown above and select one of the following options:"
				 << "\n  [M] Modify information."
				 << "\n  [C] Confirm information and add new movie to database."
				 << "\n  [~] Abort process and return to the Admin Actions menu." << endl
				 << "\nUser Input: ";
			getline(cin, input);

			// Error handling + data processing
			if (validInput()) {
				input = fct.strToUpperCase(input);
				
				if (input == "M" || input == "C" || input == "~") { // Modify OR Continue OR Abort.
					break; // Send back to [insertMovieData()] for processing.
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

// Once user enters all requires data into the terminal for a new movie, this function processes that data to the database.
void DB_MovieData::sendMovieToDB(mysqlx::Schema db) {

	/*
	* Reference: https://stackoverflow.com/questions/75135560/x-devapi-batch-insert-extremely-slow
	* 
	* HOW TO SEND DATA TO DB USING [xdevapi.h] -->
	*
	* 1. Create [Table] object.
	*
	*		NOTE: Schema object required! Assume user has already created the following object --> mysqlx::Schema db
	*
	*		mysqlx::Table tbl = db.getTable("table_name"); { Replace "table_name" with the exact name of the table you wish to interact with from the database }
	*
	* 2. Create [TableInsert] object using [Table] object.
	*
	*		mysqlx::TableInsert tblInsert = tbl.insert();
	*
	*		NOTE: The example above will insert all values for all available columns in the table.
					An error is thrown is there are more/less values being inserted than there are columns in the table.
					This is the equivalence of { INSERT INTO tbl_actors VALUES(1, 'FirstName', 'MiddleName', 'LastName') } in SQL.
	*
	*									##### OR #####
	*
	*		mysqlx::TableInsert tblInsert = tbl.insert("column1", "column2", "column3");
	*
	*		NOTE: The example above will only accept values for the 3 specified columns.
					An error is thrown if there are more/less values being inserted than the number of columns specified in ".insert()".
					This is the equivalence of { INSERT INTO tbl_actors("column1", "column2", "column3") VALUES('FirstName', 'MiddleName', 'LastName') } in SQL.
	*
	* 3. Populate [TableInsert] object with data to be inserted into database.
	*
	*		tblInsert.values(val1, val2, val3, val4);
	*
	*		NOTE: The example above adds 4 different values to "tblInsert". These are the values we want to add to the database.
					Assume that either the corresponding table in the database has 4 columns, or the previous C++ statement from step 2 specifies 4 unique columns.
	*
	* 4. Process the [TableInsert] object to the database and record the change in a [Result] object.
	*
	*		mysqlx::Result res = tblInsert.execute();
	*
	*		NOTE: It is not required that you store the results in a [Result] object every time.
					This is for your ease of convenience if you need to review the latest change to the database.
	*
	* 5. FULL EXAMPLES -->
	*		mysqlx::Schema db; (assume 'db' is configured beforehand*)
	*		mysqlx::Table tbl = db.getTable("table_name");
	*
	*
	*		##### Example 001 #####
	*
	*		mysqlx::TableInsert tblInsert = tbl.insert(); (assume the mysql table has 4 columns*)
	*		tblInsert.values(val1, val2, val3, val4);
	*		mysqlx::Result res = tblInsert.execute();
	*
	* 		##### Example 002 #####
	*
	*		mysqlx::TableInsert tblInsert = tbl.insert("column2", "column3", "column4");
	*		tblInsert.values(val1, val2, val3);
	*		mysqlx::Result res = tblInsert.execute();
	*
	* 		##### Example 003 #####
	*
	*		mysqlx::TableInsert tblInsert = tbl.insert().values(val1, val2, val3, val4).execute();
	*
	*/

	int movieID = -1;
	vector<int> actorIDs = {};
	vector<int> directorIDs = {};

	try {
		mysqlx::Table movieTbl = db.getTable("tbl_moviedata");
		mysqlx::Table actorTbl = db.getTable("tbl_actors");
		mysqlx::Table movieActorTbl = db.getTable("tbl_moviecast");
		mysqlx::Table dirTbl = db.getTable("tbl_directors");
		mysqlx::Table movieDirTbl = db.getTable("tbl_moviedirectors");
		mysqlx::Table movieGenreTbl = db.getTable("tbl_moviegenres");


		// Link [TableInsert] object to [Table] object and specify which columns are targets of the INSERT statment.
		mysqlx::TableInsert tblInsertStmt = movieTbl.insert("movieTitle", "movieYear", "numCast", "movieRating");
		// Specify the values being inserted in the columns specified above, and send them to the DB using the "execute()" command.
		tblInsertStmt.values(movieTitle, movieYear, movieNumCast, movieRating);
		// Execute the TableInsert object and send data to database. Store results of INSERT query in Result object "res".
		mysqlx::Result res = tblInsertStmt.execute();
		movieID = res.getAutoIncrementValue();
		

		// Link all actors to the new movie via their IDs.
		for (auto& i : movieCastMembers) {
			//actorIDs.push_back(stoi(i[0]));
			tblInsertStmt = movieActorTbl.insert("movieID", "actorID");
			tblInsertStmt.values(movieID, stoi(i[0])).execute();
		}


		// Add directors to the database. (rework*)
		for (auto& i : movieDirectors) {
			tblInsertStmt = dirTbl.insert("director_Fname", "director_Mname", "director_Lname");
			tblInsertStmt.values(i[0], i[1], i[2]);
			res = tblInsertStmt.execute();
			directorIDs.push_back(res.getAutoIncrementValue());
		}
		
		// Link all directors to the new movie via their IDs.
		for (auto& i : directorIDs) {
			tblInsertStmt = movieDirTbl.insert("movieID", "directorID");
			tblInsertStmt.values(movieID, i).execute();
		}


		// Link genres to the new movie via their IDs.
		for (auto& i : movieGenreIDs) {
			tblInsertStmt = movieGenreTbl.insert("movieID", "genreID");
			tblInsertStmt.values(movieID, i).execute();
		}
	}

	catch (const mysqlx::Error& err) {
		msgs.push_back("MYSQLX_ERROR [sendMovieToDB()]: " + string(err.what()));
	}
	catch (exception& ex) {
		msgs.push_back("EXCEPTION [sendMovieToDB()]: " + string(ex.what()));
	}
}




// Processes user requests to INSERT a new movie (and other associated info) to the database.
vector<string> DB_MovieData::insertMovieData(mysqlx::Schema db) {
	setDefaultValues(); // Reset global variables to default values.

	while (movieTitle == "") {
		setTitle(db);
	}

	setYear();
	setRating();

	setNumCast();
	while (movieCastMembers.size() < movieNumCast) {
		setCast(db);
	}

	setNumDir();
	while (movieDirectors.size() < movieNumDir) {
		setDir(db);
	}

	input = "";
	while ( !(input == "C") ) {
		setGenre(db);
	}

	input = "";
	while ( !(input == "C") && !(input == "~") ) {
		validationSCRN(); // Display all of the user's entered data for confirmation.

		if (input == "M") {
			modifyNewMovie(db); // Modify previously entered data of the user's choosing.
			input = "";
		}
	}
	
	if (input == "~") { // Abort process and return to Admin Actions UI.
		msgs.clear();
		msgs.push_back("SYS: Process aborted! Movie not added to database.");
	}
	else if (input == "C") {
		sendMovieToDB(db); // Send all movie data to database.
		msgs.push_back("SYS: New movie successfully added to the database!");
	}

	return msgs;
}

// Processes user requests to UPDATE data on the database. [*NOT IMPLEMENTED*]
vector<string> DB_MovieData::updateMovieData(mysqlx::Schema db) {
	setDefaultValues(); // Reset global variables to default values.
	// do something...

	return { "SYS: Functionality not implemented yet! Will be added in a future release." };
}

// Processes user requests to DELETE data from the database. [*NOT IMPLEMENTED*]
vector<string> DB_MovieData::deleteMovieData(mysqlx::Schema db) {
	setDefaultValues(); // Reset global variables to default values.
	// do something...

	return { "SYS: Functionality not implemented yet! Will be added in a future release." };
}

