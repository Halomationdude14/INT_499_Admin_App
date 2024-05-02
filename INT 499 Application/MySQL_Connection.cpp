
/*
INT 499 Capstone for Information Technology
Interactive Assignment
Date: 2024-04-22
Author: Paul Oram
NOTE: This is a modified version of the original code that has been reworked to integrate into the final project (MySQL DB).
*/

#include <iostream>
#include <string>
#include <cppconn/driver.h> 
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>
using namespace std;

#include "EZTechMovie_Admin_App.h"

/*
* Default Constructor
*/
MySQL_Connection::MySQL_Connection() {
    driver(nullptr);
    con(nullptr);
    stmt(nullptr);
    res(nullptr);
    selectQuery = "";
}

/*
* Purpose: Create the connection to a locally stored MySQL database.
* NOTE: If reusing my code, don't forget to update the connection info to match your own local MySQL database.
*/
bool MySQL_Connection::establishConnection() {
    try {
        driver = get_driver_instance();
        con = driver->connect("tcp://localhost:3306", "root", "Inferno24/7!"); //connect(host, user, password);
        con->setSchema("eztechmoviedb");
        stmt = con->createStatement(); //initialize "Statement* stmt" now that the connection has been established
        cout << "Connected to MySQL database successfully!" << endl;
        return true;
    }
    catch (SQLException& e) {
        cerr << "Error connecting to MySQL: " << e.what() << endl;
        return false;
    }
    return false;
}

/*
* Purpose: Close the connection to the MySQL database.
*/
void MySQL_Connection::closeConnection() {
    if (con) {
        delete con;
        con = nullptr;
    }
    driver = nullptr;
    stmt = nullptr;
    selectQuery = "";
}

