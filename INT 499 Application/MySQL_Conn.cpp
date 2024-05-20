
#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <mysqlx/xdevapi.h>

using namespace std;
using namespace mysqlx;

#include "EZTechMovie_Admin_App.h"


MySQL_Connection::MySQL_Connection() {
    tempStr = "";
    sys_msg = {};
    dbUser = "";
    dbName = "";
}

std::string MySQL_Connection::run() {

    return tempStr;
}

/*
* Purpose: Create the connection to a locally stored MySQL database.
* NOTE: If reusing my code, don't forget to update the connection info to match your own local MySQL database.
*/
bool MySQL_Connection::startConnection() {
    try {
        //sys_msg.push_back("SYS: Establishing connection to local MySQL Server...");
        // 
        // There are multiple ways of inputting data into the "Session()" function, but this one is straight forward.
        // Session s1("localhost", 3306, "user", "pass");
        mysqlx::Session sess("localhost", 33060, "root", "Inferno24/7!"); // Establish connection with local MySQL server
        sys_msg.push_back("SYS: Connection to local MySQL Server establish successfully!");

        //sys_msg.push_back("SYS: Establishing connection to database: \"eztechmoviedb\"...");
        mysqlx::Schema db = sess.getSchema(dbName); // Points to specific database
        sys_msg.push_back("SYS: Connection to database \"eztechmoviedb\" successful!");

        //fct.addMsg(sys_msg);
        sys_msg.clear();
        return true;
    }
    catch (const mysqlx::Error& err) {
        sys_msg.push_back("[MySQL|mysqlx] ERROR: " + std::string(err.what()));
        //fct.addMsg(sys_msg);
        return false;
    }
    catch (const std::exception& ex) {
        sys_msg.push_back("[MySQL|std] ERROR: " + std::string(ex.what()));
        //fct.addMsg(sys_msg);
        return false;
    }
}

bool MySQL_Connection::userLogin(std::string username, std::string password) {
    bool validLogin = false;

    while (validLogin == false) {
        //vector<std::string> empty = {};
        //fct.displayHeader(empty);
        cout << "[MySQL_Conn|userLogin] Dump String" << endl;
        validLogin = true;
    }
    return validLogin;
}

/*
* Purpose: Close the connection to the MySQL database.
*/
bool MySQL_Connection::closeConnection() {
    sys_msg.push_back("SYS: Connection to MySQL server closed.");
    //fct.addMsg(sys_msg);
    sys_msg.clear();
    tempStr = "";
    return true;
}

