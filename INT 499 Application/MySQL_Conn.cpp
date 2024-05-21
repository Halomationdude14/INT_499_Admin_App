
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

    if (conn) {
        msgs.push_back("SYS [MySQL]: Connection to MySQL server successful!");
    }
    else {
        msgs.push_back("SYS [MySQL]: Could not establish connection to MySQL server! Ensure you have entered the correct credentials (case sensitive).");
    }

    return msgs;
}

/*
* Purpose: Create the connection to a locally stored MySQL database.
*/
bool MySQL_Connection::startConn(std::string user, std::string pass) {
    try {
        sess = std::make_unique<mysqlx::Session> ("localhost", 33060, user, pass); // Establish connection with local MySQL server
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
    msgs.clear();

    if (conn) {
        table.reset();
        schema.reset();
        sess->close();
        sess.reset();
        msgs.push_back("SYS [MySQL]: Connection to MySQL server closed.");
    }
    else {
        msgs.push_back("ERROR [MySQL|closeConn()]: No active connection to MySQL server. Cannot perform action.");
    }

    return msgs;
}

