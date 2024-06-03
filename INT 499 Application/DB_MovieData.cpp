
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <mysqlx/xdevapi.h>
using namespace std;

#include "EZTechMovie_Admin_App.h"


// Declare global variables
Global_Functions fct;
Menus menu;


DB_MovieData::DB_MovieData() {
	msgs = {}; // Vector to hold all sys/err messages.
	tableData = {}; // Holds table data in <std> format to be sent to Menus object for display.
	running = true;
	input = "";
}




// a
int static setYear() {
	vector<string> msgs = {};
	string input = "";
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

// a
string static setRating() {
	vector<string> msgs = {};
	string input = "";
	vector<string> ratings = { "G","PG","PG-13","R" };
	bool running = true;

	while (running) {
		menu.displayMenu(msgs);
		msgs.clear();

		cout << "\nRating [G,PG,PG-13,R]: ";
		getline(cin, input);

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

// a
int static setNumCast() {
	vector<string> msgs = {};
	string input = "";
	int numCast = -1;

	while (numCast == -1) {
		menu.displayMenu(msgs);
		msgs.clear();

		cout << "\nHow many cast members? [1-5]: ";
		getline(cin, input);

		if (!(fct.strIsInt(input))) {
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

// a
vector<vector<string>> static setCast(int numCast) {
	vector<string> msgs = {};
	string input = "";
	vector<vector<string>> castMembers = {};
	vector<string> person = {};

	//a

	return {};
}

// a
int static setNumDir() {
	vector<string> msgs = {};
	string input = "";
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

// a
vector<vector<string>> static setDir(int numDir) {
	vector<string> msgs = {};
	string input = "";

	return {};
}

// a
vector<int> static setGenre() {
	vector<string> msgs = {};
	string input = "";

	return {};
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


	// NOTE: Function will prompt user for each input one at a time. If user enters invalid data, method starts again.
	// REWORK: Don't make the user re-enter each prompt after 1 mistake. Reprompt for only the 1 prompt to which the user entered invalid data.
	//		   Could create a function in the new class "Admin_Actions" that takes in a string/prompt, obtains user input, verifies input, and
	//		   returns value if valid/reprompts if invalid.
	try {
		// Obtain input data from user

		menu.displayMenu(msgs); //display header
		msgs.clear();
		cout << "\nMovie Title: ";
		getline(cin, title);

		year = setYear();
		rating = setRating();
		numCast = setNumCast();
		castMembers = setCast(numCast);
		numDir = setNumDir();
		directors = setDir(numDir);
		genres = setGenre();

		for (int i = 0; i < numCast; i++) {
			string name = "";
			person.clear();
			cout << "\nCast Member #" + to_string(i + 1) + " -->\n" << endl;

			cout << "\n  First Name: ";
			cin >> name;
			person.push_back(name);
			cout << "\n  Middle Name: ";
			cin >> name;
			person.push_back(name);
			cout << "\n  Last Name: ";
			cin >> name;
			person.push_back(name);

			castMembers.push_back(person);
		}

		menu.displayMenu({}); // Reset UI for next set of inputs
		cout << "\nHow many directors?: ";
		// NOTE: Num must be >= 1!!!
		cin >> numDir;
		cout << endl;

		for (int i = 0; i < numDir; i++) {
			string name = "";
			person.clear();
			cout << "\nDirector #" + to_string(i + 1) + " -->\n" << endl;

			cout << "\n  First Name: ";
			cin >> name;
			person.push_back(name);
			cout << "\n  Middle Name: ";
			cin >> name;
			person.push_back(name);
			cout << "\n  Last Name: ";
			cin >> name;
			person.push_back(name);

			directors.push_back(person);
		}

		// Get genre data: which genres to link to new movie (optional to add a new genre to the db)
		while ((genres.size() == 0 || !(input == "C")) && !(input == "~")) {
			tableData = fct.getTableData(genreTbl);
			menu.displayTable(msgs, tableData); // Display list of available genres
			msgs.clear();

			cout << "\nEnter one or more genres by their index number -->" << endl
				<< "\n  Enter[G] to add a new genre to the database."
				<< "\n  Enter[C] to add this new movie to the database."
				<< "\n  Enter[~] to cancel this process and return to the Admin Actions menu." << endl;
			//Add function to CANCEL current function and return to Admin Actions menu.

			cout << "\nGenres Selected = " + genres.size() << endl;
			cout << "User Input: ";
			cin >> input;

			// Verify genre selection
			for (auto& i : tableData) {
				int index = stoi(input);
				if ( index = stoi(i[0]) ) {
					genres.push_back(index);
				}
			}

			if (genres.size() == 0) {
				msgs.push_back("ERROR [insertMovieData()]: No genres selected! Please select at least 1 genre for the movie before continuing.");
			}
			else {
				input = fct.strToUpperCase(input);
				if (input == "G") { // Add new genre to database
					//addNewGenre();
					msgs.push_back("TEST [insertMovieData()]: Cannot add new genre! Functionality not implemented yet!");
					break;
				}
				else if (input == "C" || input == "~") { // These options are handled below 
					break;
				}
				else {
					msgs.push_back("ERROR [insertMovieData()]: User input [" + input + "] is invalid!");
					break;
				}
			}
		}

		if (input == "~") { //Abord process! Return to Admin Settings menu
			msgs.push_back("SYS [insertMovieData()]: Process aborted! No new movies added to the database.");
			running = false;
		}
		else if (input == "C") { // process data to database
			// code here*

			msgs.push_back("SYS [insertMovieData()]: New movie successfully added to the database!");
			running = false;
		}
	}
	catch (const mysqlx::Error& err) {
		msgs.push_back("MYSQLX_ERROR [insertMovieData()]: " + string(err.what()));
	}
	catch (exception& ex) {
		msgs.push_back("ERROR [insertMovieData()]: " + string(ex.what()));
	}

	return msgs;
}

// Processes user requests to UPDATE data on the database
vector<string> DB_MovieData::updateMovieData(mysqlx::Schema db) {
	// do something...
}

// Processes user requests to DELETE data from the database
vector<string> DB_MovieData::deleteMovieData(mysqlx::Schema db) {
	// do something...
}

