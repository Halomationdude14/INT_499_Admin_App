
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
	running = true;
	input = "";
}


// Prompts user for the year the movie was published
int DB_MovieData::setYear() {
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

	return year;
}

// Prompts user for the rating of the movie
string DB_MovieData::setRating() {
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

	return input;
}

// Prompts user for the number of cast members in the movie
int DB_MovieData::setNumCast() {
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

	return numCast;
}

// Prompts user to enter the names of each main cast member
vector<vector<string>> DB_MovieData::setCast(int numCast) {
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

	return castMembers;
}

// Prompts user for number of directors of the movie
int DB_MovieData::setNumDir() {
	msgs.clear();
	int numDir = -1;

	while (numDir == -1) {
		menu.displayMenu(msgs);
		msgs.clear();

		cout << "\nHow many directors? [1-3]: ";
		getline(cin, input);

		if (!(fct.strIsInt(input))) {
			msgs.push_back("ERROR: User entry was not a number!");
		}
		else if (!(0 < stoi(input) < 4)) { //if not between 1-3
			msgs.push_back("ERROR: User entry was not a valid number! Please enter a number [1-3].");
		}
		else {
			numDir = stoi(input);
		}
	}

	return numDir;
}

// Prompts user to enter the names of each director
vector<vector<string>> DB_MovieData::setDir(int numDir) {
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

	return directors;
}

// Prompts user to select 1 or more genres that the movie falls into.
// Also allows the user to add a genre to the database if one is missing.
vector<int> DB_MovieData::setGenre(mysqlx::Table tbl) {
	msgs.clear();
	tableData.clear();
	vector<int> genres = {};
	tableData = fct.getTableData(tbl);

	// Get genre data: which genres to link to new movie (optional to add a new genre to the db)
	while ( genres.size() == 0 || !(input == "C") ) {
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
		if (fct.strIsInt(input)) { //if input is int
			for (auto& i : tableData) {
				int index = stoi(input);
				if (index == stoi(i[0])) {
					genres.push_back(index);
				}
			}
		}
		else { //if input is NOT int
			input = fct.strToUpperCase(input);
		}

		if (input == "G") { //add new genre to database
			//addNewGenre();
		}

		// Error handling
		if (genres.size() == 0) {
			msgs.push_back("ERROR [insertMovieData()]: No genres selected! Please select at least 1 genre for the movie before continuing.");
		}
		else {
			if ( !(input == "C") ) {
				msgs.push_back("ERROR [insertMovieData()]: User input [" + input + "] is invalid!");
			}
		}
	}

	return genres;
}

// Final screen during the "add movie" process.
// Displays the user's entered data, asks them to confirm, allows them to modify, and asks to continue.
void DB_MovieData::validationSCRN() {

}


// Processes user requests to INSERT a new movie (and other associated info) to the database
vector<string> DB_MovieData::insertMovieData(mysqlx::Schema db) {
	running = true; //loop*
	input = "";
	msgs.clear();

	string title = "";
	int year = -1;
	string rating = "";
	int numCast = -1;
	int numDir = -1;
	vector<vector<string>> castMembers = {};
	vector<vector<string>> directors = {};

	mysqlx::Table genreTbl = db.getTable("tbl_genredata");
	vector<int> genres = {}; // Stores a list of integers (indicates the index of an existing genre in the database) to be associated with the newly added movie.


	/*
	mysqlx::Table movieTbl = db.getTable("tbl_moviedata");
	mysqlx::Table actorTbl = db.getTable("tbl_actors");
	mysqlx::Table genreTbl = db.getTable("tbl_moviecast"); //relational
	mysqlx::Table dirTbl = db.getTable("tbl_directors");
	mysqlx::Table movieDirTbl = db.getTable("tbl_moviedirectors"); //relational
	mysqlx::Table genreTbl = db.getTable("tbl_genredata");
	mysqlx::Table movieGenreTbl = db.getTable("tbl_moviegenres"); //relational
	*/

	try {
		menu.displayMenu({}); //display header
		msgs.clear();
		cout << "\nMovie Title: ";
		getline(cin, title);

		year = setYear();
		rating = setRating();
		numCast = setNumCast();
		castMembers = setCast(numCast);
		numDir = setNumDir();
		directors = setDir(numDir);
		genres = setGenre(genreTbl);
		
	}
	catch (const mysqlx::Error& err) {
		msgs.push_back("MYSQLX_ERROR [insertMovieData()]: " + string(err.what()));
	}
	catch (exception& ex) {
		msgs.push_back("ERROR [insertMovieData()]: " + string(ex.what()));
	}

	msgs.push_back("SYS: New movie successfully added to the database!"); //what if the process was cancelled?

	return msgs;
}

// Processes user requests to UPDATE data on the database
vector<string> DB_MovieData::updateMovieData(mysqlx::Schema db) {
	// do something...
	return {};
}

// Processes user requests to DELETE data from the database
vector<string> DB_MovieData::deleteMovieData(mysqlx::Schema db) {
	// do something...
	return {};
}

