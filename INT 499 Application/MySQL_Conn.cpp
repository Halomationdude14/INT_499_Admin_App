
#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <mysqlx/xdevapi.h>

using namespace std;
using namespace mysqlx;
//int qstate;

#include "EZTechMovie_Admin_App.h"


/*
* Default Constructor
*/
MySQL_Connection::MySQL_Connection() {
    sys_msg = {};
    hostname = "localhost";
    port = 33060;
    dbName = "eztechmoviedb";
    dbUser = "root";
    dbPass = "Inferno24/7!";
    dbTables = {}; //holds a list of all tables in the database
    tempStr = "";
}

/*
* Purpose: Create the connection to a locally stored MySQL database.
* NOTE: If reusing my code, don't forget to update the connection info to match your own local MySQL database.
*/
bool MySQL_Connection::startConnection() {
    try {
        sys_msg.push_back("SYS: Establishing connection to local MySQL Server...");
        // There are multiple ways of inputting data into the "Session()" function, but this one is straight forward.
        // Session s1("localhost", 3306, "user", "pass");
        mysqlx::Session sess(hostname, port, user, pass); // Establish connection with local MySQL server
        sys_msg.push_back("SYS: Connection to local MySQL Server establish successfully!");

        sys_msg.push_back("SYS: Establishing connection to database: \"eztechmoviedb\"...");
        mysqlx::Schema db = sess.getSchema(dbName); // Points to specific database
        sys_msg.push_back("SYS: Connection to database \"eztechmoviedb\" successful!");

        fct.addMsg(sys_msg);
        sys_msg.clear();
    }
    catch (const mysqlx::Error& err) {
        sys_msg.push_back("[MySQL|mysqlx] ERROR: " + std::string(err.what()));
        fct.addMsg(sys_msg);
        return false;
    }
    catch (const std::exception& ex) {
        sys_msg.push_back("[MySQL|std] ERROR: " + std::string(ex.what()));
        fct.addMsg(sys_msg);
        return false;
    }
}

void MySQL_Connection::userLogin(std::string username, std::string password) {
    bool validLogin = false;

    while (validLogin == false) {
        vector<string> empty = {};
        fct.displayHeader(empty);
    }
}

/*
* Purpose: Close the connection to the MySQL database.
*/
void MySQL_Connection::closeConnection() {
    sys_msg.push_back("SYS: Connection to MySQL server closed.");
    fct.addMsg(sys_msg);
    sys_msg.clear();
    dbTables.clear();
    query = "";
}

