
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
#include <mysqlx/xdevapi.h>

using namespace std;
using namespace mysqlx;
int qstate;

#include "EZTechMovie_Admin_App.h"


/*
* Default Constructor
*/
MySQL_Connection::MySQL_Connection() {
    hostname = "localhost";
    port = 33060;
    dbName = "eztechmoviedb";
    user = "root";
    pass = "Inferno24/7!";
    dbTables = {}; //holds a list of all tables in the database
    query = "";
}

/*
* Purpose: Create the connection to a locally stored MySQL database.
* NOTE: If reusing my code, don't forget to update the connection info to match your own local MySQL database.
*/
bool MySQL_Connection::startConnection() {
    try {
        // Alter how "sys_msg" is handled. Make it a global variable that can be set by any class.

        // There are multiple ways of inputting data into the "Session()" function, but this one is straight forward.
        // Session s1("localhost", 3306, "user", "pass");
        mysqlx::Session sess(hostname, port, user, pass); // Establish connection
        mysqlx::Schema db = sess.getSchema(dbName); // Points to specific database

        // If the schema "eztechmoviedb" exists in the database, return true, else return false.
        if (db.existsInDatabase()) {
            return true;
        }
        else {
            return false;
        }
    }
    catch (const mysqlx::Error& err) {
        cout << "ERROR: " << err << endl;
        return false;
    }
    catch (std::exception& ex) {
        cout << "STD EXCEPTION: " << ex.what() << endl;
        return false;
    }
    catch (const char* ex) {
        cout << "EXCEPTION: " << ex << endl;
        return false;
    }
}

/*
* Purpose: Close the connection to the MySQL database.
*/
void MySQL_Connection::closeConnection() {
    dbTables = {};
    query = "";
}

