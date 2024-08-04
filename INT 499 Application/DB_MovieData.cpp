
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
* 1. Add a title to the header indicating that the user in in the process of "adding a new movie" to the database.
* 2. IDEA: add a new function that handles displaying the UI and clearing [msgs].
* 
*/


DB_MovieData::DB_MovieData() {
	// Define ANSI color codes
	TEXT =		"\033[97m";
	YELLOW =	"\033[93m";
	GREEN =		"\033[92m";
	RED =		"\033[91m";
	PURPLE =	"\033[95m";
	CYAN =		"\033[96m";
	BLUE =		"\033[94m";
	BLACK =		"\033[90m";
	
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
	// Format = [index, firstName, middleName, lastName]
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

// Adds any messages in [message] to the end of [msgs].
void DB_MovieData::addMsg(vector<string> message) {
	if (!message.empty()) {
		msgs.insert(msgs.end(), message.begin(), message.end());
	}
}

// Adds a string to the end of [msgs].
void DB_MovieData::addMsg(string message) {
	if (!message.empty()) {
		msgs.push_back(message);
	}
}

// Takes in a string and verifies it is not empty, and contains no spaces prior to first char.
bool DB_MovieData::validInput() {
	if (input.empty()) {
		addMsg(fct.addErr("User input is empty! Please enter a value this time..."));
		return false;
	}
	else if (isspace(input[0])) {
		addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] is invalid! Input cannot begin with a space."));
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
			std::cout << "  First Name: ";
			std::getline(cin, input);

			// Error handling
			if (validInput()) {
				person.push_back(input);
				notValid = false;
			}
		}
		catch (exception& ex) {
			addMsg(fct.addExc(string(ex.what()), "EXCEPTION"));
		}
	}

	notValid = true;
	// Middle name
	while (notValid) { 
		try {
			menu.displayMenu(msgs);
			msgs.clear();
			std::cout << "  First Name: " << person[0] << endl
				 << "NOTE: Enter [~] to skip middle name entry." << endl
				 << "  Middle Name: ";
			std::getline(cin, input);

			// Error handling
			if (validInput()) {
				if (input == "~") {
					person.push_back("NULL");
					notValid = false;
				}
				else {
					person.push_back(input);
					notValid = false;
				}
			}
		}
		catch (exception& ex) {
			addMsg(fct.addExc(string(ex.what()), "EXCEPTION"));
		}
	}

	notValid = true;
	// Last name
	while (notValid) {
		try {
			menu.displayMenu(msgs);
			msgs.clear();
			std::cout << "  First Name: " << person[0] << endl;

			// If user chose not to enter middle name, display "N/A".
			if (person[1].empty()) {
				std::cout << "  Middle Name: N/A" << endl;
			}
			else {
				std::cout << "  Middle Name: " << person[1] << endl;
			}

			std::cout << "  Last Name: ";
			std::getline(cin, input);

			// Error handling
			if (validInput()) {
				person.push_back(input);
				notValid = false;
			}
		}
		catch (exception& ex) {
			addMsg(fct.addExc(string(ex.what()), "EXCEPTION"));
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
		fct.getTableData(movieTbl, &tableData, &msgs); // Obtain data from table {tbl_moviedata}.

		// Record existing movie titles from table {tbl_moviedata}.
		for (auto& i : tableData) {
			tblIndexes.push_back(i[1]); // NOTE: Reusing this variable to store titles instead of indexes.
		}

		menu.displayMenu(msgs);
		msgs.clear();
		std::cout << "Movie Title: ";

		try {
			std::getline(cin, input);

			// Error handling + data processing
			if (validInput()) {

				for (auto& i : tblIndexes) { // Verify that user entry doesn't exist in database.
					string newTitle = fct.strToUpperCase(input);
					string oldTitle = fct.strToUpperCase(i);
					if (newTitle == oldTitle) {
						duplicate = true;
					}
				}

				if (!(duplicate == true)) { // If no duplicate...
					movieTitle = input;
					notValid = false;
				}

				while (duplicate == true) { // If duplicate...
					addMsg(fct.addWarn("Duplicate found! A movie title [" + fct.inptClr(input) + "] already exists in the database."));
					menu.displayMenu(msgs);
					msgs.clear();

					string title = input; // Record user input as title for new movie.

					std::cout << "Would you like to keep this title or enter a new one?" << endl
						<< string(YELLOW) + "  [1]" + TEXT + " Keep duplicate title." << endl
						<< string(YELLOW) + "  [2]" + TEXT + " Enter new title." << endl;

					std::cout << "\nUser Input: ";
					std::getline(cin, input);

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
							addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] is invalid!"));
						}
					}
				}
			}
		}

		catch (const mysqlx::Error& err) {
			addMsg(fct.addExc(string(err.what()), "MYSQLX_ERROR"));
		}
		catch (exception& ex) {
			addMsg(fct.addExc(string(ex.what()), "EXCEPTION"));
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
		std::cout << "NOTE: Year must be in format [YYYY] with range of [1888 - present]." << endl;
		std::cout << "\nMovie Year: ";

		try {
			std::getline(cin, input);

			// Error handling + data processing
			if (validInput()) {
				if ( !(fct.strIsInt(input)) ) { // Verify input is type int.
					addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] is invalid! Contains non-numerical characters."));
				}
				else if ( (1888 <= stoi(input)) && (stoi(input) <= currYear) ) { // Verify date range.
					movieYear = stoi(input);
				}
				else {
					addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] is invalid! Year is not within allowed range."));
				}
			}
		}

		catch (exception& ex) {
			addMsg(fct.addExc(string(ex.what()), "EXCEPTION"));
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
		std::cout << "Movie Rating [G,PG,PG-13,NC-17,R]: ";

		try {
			std::getline(cin, input);

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
					addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] is not a valid rating!"));
				}
			}
		}

		catch (exception& ex) {
			addMsg(fct.addExc(string(ex.what()), "EXCEPTION"));
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
		std::cout << "How many cast members? [1-5]: ";

		try {
			std::getline(cin, input);

			// Error handling + data processing
			if (validInput()) {
				if ( !(fct.strIsInt(input)) ) { // If not a number...
					addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] is not a number! Please enter a number [1-5]."));
				}
				else {
					if (((stoi(input) - 1) | (5 - stoi(input))) >= 0) { // If number is between 1-5 (bit opperation).
						movieNumCast = stoi(input);
					}
					else {
						addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] is not within the allowed numerical range! Please enter a number [1-5]."));
					}
				}
			}
		}

		catch (exception& ex) {
			addMsg(fct.addExc(string(ex.what()), "EXCEPTION"));
		}
	}
}

// Allows the user to add a new actor to the database.
void DB_MovieData::addNewCast(mysqlx::Table tbl) {
	vector<string> newActor = newPerson();
	vector<string> uppercase = { fct.strToUpperCase(newActor[0]), fct.strToUpperCase(newActor[1]), fct.strToUpperCase(newActor[2]) };
	vector<string> oldActor = {}; // Stores a single actor from the database (used for comparison).
	bool duplicate = false;

	// Compare new actor to existing actors: verify no duplicates.
	for (auto& i : tableData) {
		oldActor = { fct.strToUpperCase(i[1]), fct.strToUpperCase(i[2]), fct.strToUpperCase(i[3]) };
		if (uppercase == oldActor) {
			duplicate = true;

			string name = newActor[0];
			if (newActor[1] != "NULL") {
				name.append(" " + newActor[1]);
			}
			name.append(" " + newActor[2]);

			addMsg(fct.addErr("Duplication error! The actor [" + fct.inptClr(name) + "] already exists in the database."));
		}
	}

	// If no duplicates are found, add new actor to database and break the loop.
	if (duplicate == false) {
		try {
			mysqlx::TableInsert tblInsertStmt = tbl.insert("actor_Fname", "actor_Mname", "actor_Lname");

			mysqlx::Value nullVal;
			if (newActor[1] == "NULL") {
				tblInsertStmt.values(newActor[0], nullVal, newActor[2]).execute();
			}
			else {
				tblInsertStmt.values(newActor[0], newActor[1], newActor[2]).execute();
			}

			addMsg(fct.addSys("Actor successfully added to the database!"));
		}
		catch (const mysqlx::Error& err) {
			addMsg(fct.addExc(string(err.what()), "MYSQLX_ERROR"));
		}
	}
}

// Prompts user to enter the names of each main cast member.
void DB_MovieData::setCast(mysqlx::Schema db) {
	msgs.clear();
	tblIndexes.clear();
	vector<string> tempMsg = {}; // Assists with [fct.getTableData()].
	int counter = movieCastMembers.size() + 1;
	bool running = true;


	while (running) {
		try {
			mysqlx::Table actorTbl = db.getTable("tbl_actors");
			fct.getTableData(actorTbl, &tableData, &tempMsg); // Obtain data from table {tbl_actors}.
			addMsg(tempMsg);

			// Record indexes from table {tbl_actors}.
			for (auto& j : tableData) {
				tblIndexes.push_back(j[0]);
			}

			menu.displayTable(msgs, tableData); // Display list of available indexes for table {tbl_actors}.
			msgs.clear();

			std::cout << "Actor (" << counter << "/" << movieNumCast << ") -->" << endl
				<< "  [#] Select an actor (# corresponds to actor ID)." << endl
				<< "  [N] Add a new actor to the database." << endl
				<< "\nUser Input: ";
			std::getline(cin, input);

			// Error handling + data processing
			if (validInput()) {

				if (fct.strIsInt(input)) { // If input is int...

					if (find(tblIndexes.begin(), tblIndexes.end(), input) != tblIndexes.end()) { // If user input == existing index in table...
						vector<string> person = {};
						fct.getRow(tableData, stoi(input), &person, &tempMsg); // This action creates a person with format [index, firstName, middleName, lastName].
						addMsg(tempMsg);

						// Verify that the chosen actor has not already been selected previously by the user.
						if (find(movieCastMembers.begin(), movieCastMembers.end(), person) != movieCastMembers.end()) {
							addMsg(fct.addErr("Actor with ID [" + fct.inptClr(input) + "] has already been selected! Cannot be added twice."));
						}
						else if (!person.empty()) {
							movieCastMembers.push_back(person); // Add user selection if no duplicates exist.
							running = false;
						}
					}
					else {
						addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] does not correlate to any Actor IDs in the database."));
					}
				}

				else { // If input is NOT int...
					input = fct.strToUpperCase(input);

					if (input == "N") { // Obtain name for new actor, and verify that they don't exist in table {tbl_actors}
						addNewCast(actorTbl);
					}
					else {
						addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] is invalid!"));
					}
				}
			}
		}

		catch (const mysqlx::Error& err) {
			addMsg(fct.addExc(string(err.what()), "MYSQLX_ERROR"));
			break;
		}
		catch (exception& ex) {
			addMsg(fct.addExc(string(ex.what()), "EXCEPTION"));
			break;
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
		std::cout << "How many directors? [1-3]: ";

		try {
			std::getline(cin, input);

			// Error handling + data processing
			if (validInput()) {
				if (!(fct.strIsInt(input))) { // If not a number...
					addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] is not a number! Please enter a number [1-3]."));
				}
				else {
					if (((stoi(input) - 1) | (3 - stoi(input))) >= 0) { // If number is between 1-3 (bit opperation).
						movieNumDir = stoi(input);
					}
					else {
						addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] is not within the allowed numberical range! Please enter a number [1-3]."));
					}
				}
			}
		}
		catch (exception& ex) {
			addMsg(fct.addExc(string(ex.what()), "EXCEPTION"));
		}
	}
}

// Allows the user to add a new director to the database.
void DB_MovieData::addNewDir(mysqlx::Table tbl) {
	vector<string> newDir = newPerson();
	vector<string> uppercase = { fct.strToUpperCase(newDir[0]), fct.strToUpperCase(newDir[1]), fct.strToUpperCase(newDir[2]) };
	vector<string> oldDir = {}; // Stores a single director from the database (used for comparison).
	bool duplicate = false;

	// Compare new director to existing directors: verify no duplicates.
	for (auto& i : tableData) {
		oldDir = { fct.strToUpperCase(i[1]), fct.strToUpperCase(i[2]), fct.strToUpperCase(i[3]) };
		if (uppercase == oldDir) {
			duplicate = true;

			string name = newDir[0];
			if (newDir[1] != "NULL") {
				name.append(" " + newDir[1]);
			}
			name.append(" " + newDir[2]);

			addMsg(fct.addErr("Duplication error! The director [" + fct.inptClr(input) + "] already exists in the database."));
		}
	}

	// If no duplicates are found, add new director to database and break the loop.
	if (duplicate == false) {
		try {
			mysqlx::TableInsert tblInsertStmt = tbl.insert("director_Fname", "director_Mname", "director_Lname");

			mysqlx::Value nullVal;
			if (newDir[1] == "NULL") {
				tblInsertStmt.values(newDir[0], nullVal, newDir[2]).execute();
			}
			else {
				tblInsertStmt.values(newDir[0], newDir[1], newDir[2]).execute();
			}

			addMsg(fct.addSys("Director successfully added to the database!"));
		}
		catch (const mysqlx::Error& err) {
			addMsg(fct.addExc(string(err.what()), "MYSQLX_ERROR"));
		}
	}
}

// Prompts user to enter the names of each director.
void DB_MovieData::setDir(mysqlx::Schema db) {
	msgs.clear();
	tblIndexes.clear();
	vector<string> tempMsg = {}; // Assists with [fct.getTableData()].
	int counter = movieDirectors.size() + 1;
	bool running = true;


	while (running) {
		try {
			mysqlx::Table directorTbl = db.getTable("tbl_directors");
			fct.getTableData(directorTbl, &tableData, &tempMsg); // Obtain data from table {tbl_directors}.
			addMsg(tempMsg);

			// Record indexes from table {tbl_directors}.
			for (auto& j : tableData) {
				tblIndexes.push_back(j[0]);
			}

			menu.displayTable(msgs, tableData); // Display list of available indexes for table {tbl_directors}.
			msgs.clear();

			std::cout << "Director (" << counter << "/" << movieNumDir << ") -->" << endl
				<< "  [#] Select a director (# corresponds to director ID)." << endl
				<< "  [N] Add a new director to the database." << endl
				<< "\nUser Input: ";
			std::getline(cin, input);

			// Error handling + data processing
			if (validInput()) {

				if (fct.strIsInt(input)) { // If input is int...

					if (find(tblIndexes.begin(), tblIndexes.end(), input) != tblIndexes.end()) { // If user input == existing index in table...
						vector<string> person = {};
						fct.getRow(tableData, stoi(input), &person, &tempMsg); // This action creates a person with format [index, firstName, middleName, lastName].
						addMsg(tempMsg);

						// Verify that the chosen director has not already been selected previously by the user.
						if (find(movieDirectors.begin(), movieDirectors.end(), person) != movieDirectors.end()) {
							addMsg(fct.addErr("Director with ID [" + fct.inptClr(input) + "] has already been selected! Cannot be added twice."));
						}
						else if (!person.empty()) {
							movieDirectors.push_back(person); // Add user selection if no duplicates exist.
							running = false;
						}
					}
					else {
						addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] does not correlate to any director IDs in the database."));
					}
				}

				else { // If input is NOT int...
					input = fct.strToUpperCase(input);

					if (input == "N") { // Obtain name for new director, and verify that they don't exist in table {tbl_directors}
						addNewDir(directorTbl);
					}
					else {
						addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] is invalid!"));
					}
				}
			}
		}

		catch (const mysqlx::Error& err) {
			addMsg(fct.addExc(string(err.what()), "MYSQLX_ERROR"));
			break;
		}
		catch (exception& ex) {
			addMsg(fct.addExc(string(ex.what()), "EXCEPTION"));
			break;
		}
	}
}

// Allows the user to add a new genre to the database.
void DB_MovieData::addNewGenre(mysqlx::Table tbl) {
	msgs.clear();
	string genre = "";
	bool duplicate = false;
	

	// Obtain user input.
	while (duplicate == false) {
		try {
			menu.displayMenu(msgs);
			msgs.clear();
			input = "";

			std::cout << "\nEnter the genre you would like to add to the database -->" << endl
				<< "\nUser Input: ";
			std::getline(cin, input);

			// Error handling + data processing.
			if (validInput()) {
				
				// Verify no duplicates.
				for (auto& i : tableData) {
					if (fct.strToUpperCase(input) == fct.strToUpperCase(i[1])) {
						duplicate = true;
					}
				}

				if (duplicate == true) {
					duplicate = false; // Keep loop active.
					addMsg(fct.addErr("Duplication error! The genre [" + fct.inptClr(input) + "] exists in the database."));
				}
				else {
					genre = input;
					duplicate = true; // Close loop.
				}
			}
		}
		catch (exception& ex) {
			addMsg(fct.addExc(string(ex.what()), "EXCEPTION"));
		}
	}

	// Send new genre to the table {tbl_genredata}.
	try {
		mysqlx::TableInsert tblInsertStmt = tbl.insert("genreTitle").values(genre);
		tblInsertStmt.execute();
	}
	catch (const mysqlx::Error& err) {
		addMsg(fct.addExc(string(err.what()), "MYSQLX_ERROR"));
	}
}

// Prompts user to select 1 or more genres that the movie falls into.
// Also allows the user to add a genre to the database if one is missing.
void DB_MovieData::setGenre(mysqlx::Schema db) {
	msgs.clear();
	input = "";
	vector<string> tempMsg = {}; // Assists with [fct.getTableData()].
	vector<int> genreIDs = {};
	vector<string> genreNames = {};


	// Get genre data: which genres to link to new movie (optional to add a new genre to the db).
	while ( !(input == "C") ) {
		try {
			mysqlx::Table genreTbl = db.getTable("tbl_genredata");
			fct.getTableData(genreTbl, &tableData, &tempMsg); // Obtain data from table {tbl_genredata}.
			addMsg(tempMsg);
			menu.displayTable(msgs, tableData); // Display list of available genres.
			msgs.clear();

			std::cout << "Select one or more genres for the new movie -->" << endl
				<< "  [#] Select a genre (# corresponds to index of genre)." << endl
				<< "  [G] Add a new genre to the database." << endl
				<< "  [~] Clear your current selection of genres." << endl
				<< "  [C] Confirm selection and continue." << endl;

			std::cout << "\nGenres Selected = ";
			if (genreIDs.size() == 0) { // If no genres have been selected...
				std::cout << "NONE" << endl;
			}
			else {
				for (auto& i : genreNames) { // Displays each genre (by name) that the user has selected.
					if (i == genreNames.back()) { // Print WITHOUT comma.
						std::cout << i;
					}
					else { // Print WITH comma.
						std::cout << i << ", ";
					}
				}
				std::cout << endl;
			}

			std::cout << "\nUser Input: ";
			std::getline(cin, input);

			// Error handling + data processing.
			if (validInput()) {

				if (fct.strIsInt(input)) { // If input is int...
					bool validIndex = false;

					for (auto& i : tableData) { // Verify that user input corresponds to an existing index in the table {tbl_genredata}.
						if (input == i[0]) { // If input == index...
							validIndex = true;

							// Verify that the user cannot select the same genre more than once.
							if ( find(genreIDs.begin(), genreIDs.end(), stoi(input)) != genreIDs.end() ) {
								addMsg(fct.addErr("Genre with index [" + fct.inptClr(input) + "] has already been selected! Cannot be added twice."));
							}
							else {
								genreIDs.push_back(stoi(input));
								genreNames.push_back(i[1]);
							}
						}
					}

					if (validIndex == false) { // If input is NOT in the table {tbl_genredata}...
						addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] is not within the allowed numerical range! Please enter a number between[1-" + to_string(tableData.size()) + "]."));
					}
				}

				else { // If input is NOT int...
					input = fct.strToUpperCase(input);

					if (input == "G") {
						addNewGenre(genreTbl); // Add new genre to the database.
					}
					else if (input == "~") { // Clear genre selection.
						if (genreIDs.empty()) {
							addMsg(fct.addErr("Cannot clear genre selection! No genres have been selected."));
						}
						else {
							genreIDs.clear();
							genreNames.clear();
							addMsg(fct.addSys("Genre selection cleared."));
						}
					}
					else if (input == "C") { // Close loop and continue with process.
						if (genreIDs.size() == 0) {
							input = ""; // Reset [input] to keep loop active.
							addMsg(fct.addErr("No genres selected! Please select at least 1 genre for the movie before continuing."));
						}
					}
					else {
						addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] is invalid!"));
					}
				}
			}
		}

		catch (const mysqlx::Error& err) {
			addMsg(fct.addExc(string(err.what()), "MYSQLX_ERROR"));
		}
		catch (exception& ex) {
			addMsg(fct.addExc(string(ex.what()), "EXCEPTION"));
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

	std::cout << "Here's what you've entered for the new movie -->" << endl << endl
		<< "  Title: " << movieTitle << endl
		<< "  Year: " << movieYear << endl
		<< "  Rating: " << movieRating << endl;

	std::cout << "  Cast Member(s): " << movieNumCast << endl;
	for (int i = 0; i < movieNumCast; i++) {
		std::cout << "    [#" << (i + 1) << "]: " << movieCastMembers.at(i).at(1) << " ";
		if (movieCastMembers.at(i).at(2) != "NULL") { // If middle name is "NULL", don't print.
			std::cout << movieCastMembers.at(i).at(2) << " ";
		}
		std::cout << movieCastMembers.at(i).at(3) << endl;
	}

	std::cout << "  Director(s): " << movieNumDir << endl;
	for (int i = 0; i < movieNumDir; i++) {
		std::cout << "    [#" << (i + 1) << "]: " << movieDirectors.at(i).at(1) << " ";
		if (movieDirectors.at(i).at(2) != "NULL") { // If middle name is "NULL", don't print.
			std::cout << movieDirectors.at(i).at(2) << " ";
		}
		std::cout << movieDirectors.at(i).at(3) << endl;
	}

	std::cout << "  Genre(s): ";
	for (auto& i : movieGenreNames) {
		string curr = i;
		string lastItem = movieGenreNames.back();

		if (curr == lastItem) { // Print WITHOUT comma.
			std::cout << i;
		}
		else { // Print WITH comma.
			std::cout << i << ", ";
		}
	}

	std::cout << endl;
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

			std::cout << "\nWhat would you like to change?"
				<< "\n  [1] Title"
				<< "\n  [2] Year"
				<< "\n  [3] Rating"
				<< "\n  [4] Cast Member(s)"
				<< "\n  [5] Director(s)"
				<< "\n  [6] Genre(s)"
				<< "\n  [~] Cancel this change request and return to the previous UI." << endl;

			std::cout << "\nWARNING: This process will delete all previously entered data for whichever field you choose to modify!"
				<< "\nYou will have to re-enter all data for any chosen field again!" << endl;

			std::cout << "\nUser Input: ";
			std::getline(cin, input);

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
					setGenre(db);
					input = "";
					break;
				}
				else if (input == "~") { // Abort change request.
					input = "";
					break;
				}
				else { // If input is invalid (contains chars but not valid ones) keep loop going.
					notValid = true;
					if (fct.strIsInt(input)) { // [Input] contains invalid number(s).
						addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] is not within the allowed numerical range!"));
					}
					else { // [Input] contains invalid alphanumerical character(s).
						addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] is invalid!"));
					}
					
				}
			}
			else { // If input is invalid (has <SPACE> or is empty) keep loop going.
				notValid = true;
			}
		}

		catch (const mysqlx::Error& err) {
			addMsg(fct.addExc(string(err.what()), "MYSQLX_ERROR"));
		}
		catch (exception& ex) {
			addMsg(fct.addExc(string(ex.what()), "EXCEPTION"));
		}
	}
}

/*
* Final screen during the "add new movie" process.
* Displays the user's entered data. Allows for 3 options:
*	1. Modify movie data
*	2. Confirm movie data (send to database)
*	3. Abort process (don't send to database)
*/
void DB_MovieData::validationSCRN(mysqlx::Schema db) {
	msgs.clear();
	input = "";

	while ( !(input == "C") && !(input == "~") ) {
		try {
			displayNewMovie(); // Display all data entered by user for the new movie.

			std::cout << "\nReview the information shown above and select one of the following options:"
				<< "\n  [M] Modify information."
				<< "\n  [C] Confirm information and add new movie to database."
				<< "\n  [~] Abort process and return to the Admin Actions menu." << endl
				<< "\nUser Input: ";
			std::getline(cin, input);

			// Error handling + data processing
			if (validInput()) {
				input = fct.strToUpperCase(input);
				
				if (input == "M") { // Modify data
					modifyNewMovie(db);
				}
				else if (input == "C") { // Continue (send to database)
					sendMovieToDB(db);
					addMsg(fct.addSys("New movie successfully added to the database!"));
				}
				else if (input == "~") { // Abort (don't send to database)
					msgs.clear();
					addMsg(fct.addSys("Process aborted! Movie not added to database"));
				}
				else {
					addMsg(fct.addErr("User input [" + fct.inptClr(input) + "] is invalid!"));
				}
			}
		}

		catch (const mysqlx::Error& err) {
			addMsg(fct.addExc(string(err.what()), "MYSQLX_ERROR"));
			break;
		}
		catch (exception& ex) {
			addMsg(fct.addExc(string(ex.what()), "EXCEPTION"));
			break;
		}
	}
}

// Once user enters all requires data into the terminal for a new movie, this function processes that data to the database.
void DB_MovieData::sendMovieToDB(mysqlx::Schema db) {

	/*
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

	try {
		mysqlx::Table movieTbl = db.getTable("tbl_moviedata");
		mysqlx::Table actorTbl = db.getTable("tbl_actors");
		mysqlx::Table movieActorTbl = db.getTable("tbl_moviecast");
		mysqlx::Table dirTbl = db.getTable("tbl_directors");
		mysqlx::Table movieDirTbl = db.getTable("tbl_moviedirectors");
		mysqlx::Table movieGenreTbl = db.getTable("tbl_moviegenres");


		// Link TableInsert object to Table object and specify which columns are targets of the INSERT statement.
		mysqlx::TableInsert tblInsertStmt = movieTbl.insert("movieTitle", "movieYear", "numCast", "movieRating");
		// Specify the values to be inserted in each of the columns defined in the previous statement.
		tblInsertStmt.values(movieTitle, movieYear, movieNumCast, movieRating);

		// Execute the TableInsert object to send data to database. Store results of INSERT query in Result object [res].
		mysqlx::Result res = tblInsertStmt.execute();
		movieID = res.getAutoIncrementValue();
		
		// Link all actors to the new movie via their IDs.
		for (auto& i : movieCastMembers) {
			tblInsertStmt = movieActorTbl.insert("movieID", "actorID");
			tblInsertStmt.values(movieID, stoi(i[0])).execute();
		}

		// Link all directors to the new movie via their IDs.
		for (auto& i : movieDirectors) {
			tblInsertStmt = movieDirTbl.insert("movieID", "directorID");
			tblInsertStmt.values(movieID, stoi(i[0])).execute();
		}

		// Link genres to the new movie via their IDs.
		for (auto& i : movieGenreIDs) {
			tblInsertStmt = movieGenreTbl.insert("movieID", "genreID");
			tblInsertStmt.values(movieID, i).execute();
		}
	}

	catch (const mysqlx::Error& err) {
		addMsg(fct.addExc(string(err.what()), "MYSQLX_ERROR"));
	}
	catch (exception& ex) {
		addMsg(fct.addExc(string(ex.what()), "EXCEPTION"));
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
	setGenre(db);
	validationSCRN(db); // Display all of the user's entered data for confirmation.

	return msgs;
}

// Processes user requests to UPDATE data on the database. [*NOT IMPLEMENTED*]
vector<string> DB_MovieData::updateMovieData(mysqlx::Schema db) {
	setDefaultValues(); // Reset global variables to default values.
	// do something...

	return { fct.addSys("Functionality not implemented yet! Will be added in a future release.") };
}

// Processes user requests to DELETE data from the database. [*NOT IMPLEMENTED*]
vector<string> DB_MovieData::deleteMovieData(mysqlx::Schema db) {
	setDefaultValues(); // Reset global variables to default values.
	// do something...

	return { fct.addSys("Functionality not implemented yet! Will be added in a future release.") };
}

