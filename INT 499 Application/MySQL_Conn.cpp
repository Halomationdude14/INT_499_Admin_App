
#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <mysqlx/xdevapi.h>

using namespace std;
using namespace mysqlx;

#include "EZTechMovie_Admin_App.h"


MySQL_Connection::MySQL_Connection() {
    msgs = {};
    dbUser = ""; //Not good to store credentials in code!!!
    dbPass = ""; //Not good to store credentials in code!!!
    conn = false;
    //mysqlx::Session sess;
}

bool MySQL_Connection::getConn() {
    return conn;
}

vector<std::string> MySQL_Connection::login() {
    msgs.clear();

    cout << "Login to the EZTechMovie MySQL Server -->\n\n";
    cout << "Username: ";
    getline(cin, dbUser);
    cout << "Password: ";
    getline(cin, dbPass);

    conn = (startConn(dbUser, dbPass));

    if (conn == true) {
        msgs.push_back("SYS [MySQL]: Connection to MySQL server successful!");
    }
    else {
        msgs.push_back("SYS [MySQL]: Could not establish connection to MySQL server! Ensure you have entered the correct credentials (case sensitive).");
    }

    return msgs;
}

/*
* Purpose: Create the connection to a locally stored MySQL database.
* NOTE: If reusing my code, don't forget to update the connection info to match your own local MySQL database.
*/
bool MySQL_Connection::startConn(std::string user, std::string pass) {
    try {
        //sys_msg.push_back("SYS: Establishing connection to local MySQL Server...");
        // 
        // There are multiple ways of inputting data into the "Session()" function, but this one is straight forward.
        // Session s1("localhost", 3306, "user", "pass");
        //mysqlx::Session sess("localhost", 33060, "root", "Inferno24/7!"); // Establish connection with local MySQL server
        //sys_msg.push_back("SYS: Connection to local MySQL Server establish successfully!");
        //sys_msg.push_back("SYS: Establishing connection to database: \"eztechmoviedb\"...");
        //mysqlx::Schema db = sess.getSchema(dbName); // Points to specific database
        //sys_msg.push_back("SYS: Connection to database \"eztechmoviedb\" successful!");

        mysqlx::Session sess("localhost", 33060, user, pass); // Establish connection with local MySQL server

        return true;
    }
    catch (const mysqlx::Error& err) {
        msgs.push_back("MYSQLX_ERROR [MySQL|startConn()]: " + std::string(err.what()));
        return false;
    }
    catch (const std::exception& ex) {
        msgs.push_back("ERROR [MySQL|startConn()]: " + std::string(ex.what()));
        return false;
    }
}

/*
* Purpose: Close the connection to the MySQL database.
*/
vector<std::string> MySQL_Connection::closeConn() {
    //sess.close();
    msgs.clear();
    msgs.push_back("SYS [MySQL]: Connection to MySQL server closed.");
    return msgs;
}

