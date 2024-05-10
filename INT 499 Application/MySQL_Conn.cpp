
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
MySQL_Conn::MySQL_Conn() {
    hostname = "localhost";
    port = 3306;
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
bool MySQL_Conn::startConn() {
    try {
        /*
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, "localhost", "root", "Inferno24/7!", "eztechmoviedb", 3306, NULL, 0);

        if (conn) {
            puts("\nSuccessful connection to database!\n");

            query = "SELECT * FROM tbl_custdata";
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);
            if (!qstate) {
                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res)) {
                    printf("custID: %s, User: %s, Pass: %s, Email: %s, planID: %s, Activity: %s, payType: %s, Start Date: %s\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
                }
            }
            else {
                cout << "Query failed: " << mysql_error(conn) << endl;
            }
        }
        */

        // Alter how "sys_msg" is handled. Make it a global variable that can be set by any class.

        // There are multiple ways of inputting data into the "Session()" function, but this one is straight forward.
        // Session s1("localhost", 3306, "user", "pass");
        Session sess(hostname, port, user, pass); // Establish connection
        Schema db = sess.getSchema(dbName); // Points to specific database

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
void MySQL_Conn::closeConn() {
    dbTables = {};
    query = "";
}

