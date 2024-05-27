
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
    currTbl = "";
    // Session sess
    // Schema scm
    // Table tbl
}

MySQL_Connection::MySQL_Connection(std::string user, std::string pass) {
    msgs = {};
    dbUser = user; //Not good to store credentials in code!!!
    dbPass = pass; //Not good to store credentials in code!!!
    conn = false;
    currTbl = "";
    Session sess2 = getSession("localhost", 33060, user, pass);
    Schema scm2 = sess2.getSchema("eztechmoviedb");
    // Table tbl2
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
        scm = std::make_unique<mysqlx::Schema> (sess, "eztechmoviedb"); // sets "scm" to point to the eztechmoviedb database on the MySQL server
    }
    else {
        msgs.push_back("SYS [MySQL]: Could not establish connection to MySQL server! Ensure you have entered the correct credentials (case sensitive).");
    }

    dbUser = "";
    dbPass = "";
    return msgs;
}

vector<std::string> MySQL_Connection::setTable(char input) {
    msgs.clear();

    switch (input) {
        case '1':
            currTbl = "tbl_plans";
            //tbl = std::make_unique<mysqlx::Table>(scm->getTable("tbl_plans"));
            break;
        case '2':
            currTbl = "tbl_actors";
            //tbl = std::make_unique<mysqlx::Table>(scm->getTable("tbl_actors"));
            break;
        case '3':
            currTbl = "tbl_custdata";
            //tbl = std::make_unique<mysqlx::Table>(scm->getTable("tbl_custdata"));
            break;
        case '4':
            currTbl = "tbl_moviedata";
            //tbl = std::make_unique<mysqlx::Table>(scm->getTable("tbl_moviedata"));
            break;
        case '5':
            currTbl = "tbl_paymentinfo";
            //tbl = std::make_unique<mysqlx::Table>(scm->getTable("tbl_paymentinfo"));
            break;
        case '6':
            currTbl = "tbl_directors";
            //tbl = std::make_unique<mysqlx::Table>(scm->getTable("tbl_directors"));
            break;
        case '7':
            currTbl = "tbl_genredata";
            //tbl = std::make_unique<mysqlx::Table>(scm->getTable("tbl_genredata"));
            break;
        case '8':
            currTbl = "tbl_moviedirectors";
            //tbl = std::make_unique<mysqlx::Table>(scm->getTable("tbl_moviedirectors"));
            break;
        case '9':
            currTbl = "tbl_moviegenres";
            //tbl = std::make_unique<mysqlx::Table>(scm->getTable("tbl_moviegenres"));
            break;
        case '10':
            currTbl = "tbl_moviecast";
            //tbl = std::make_unique<mysqlx::Table>(scm->getTable("tbl_moviecast"));
            break;
        case '11':
            currTbl = "tbl_custactivity_dvd";
            //tbl = std::make_unique<mysqlx::Table>(scm->getTable("tbl_custactivity_dvd"));
            break;
        case '12':
            currTbl = "tbl_custactivity_stream";
            //tbl = std::make_unique<mysqlx::Table>(scm->getTable("tbl_custactivity_stream"));
            break;
        case '13':
            currTbl = "tbl_dvdrentalhistory";
            //tbl = std::make_unique<mysqlx::Table>(scm->getTable("tbl_dvdrentalhistory"));
            break;
        default:
            msgs.push_back("ERR [MySQL|setTable()]: Table does not exist in the database!");
            break;
    }
    //tbl = std::make_unique<mysqlx::Table>(scm->getTable(currTbl));
    //tbl = scm->getTable(currTbl);

    return msgs;
}

// Returns the current table object as a vector<vector<std::string>> object.
// This allows for easier display and compatibility in the main().
vector<vector<std::string>> MySQL_Connection::getTable() {
    RowResult result = tbl->select("*").execute();
    vector<vector<std::string>> tableData = {};

    try {
        for (Row row : result) {
            vector<std::string> rowData;
            for (int i = 0; i < row.colCount(); ++i) {
                Value val = row[i];
                std::string strValue;

                switch (val.getType()) {
                case Value::Type::UINT64:
                    strValue = to_string(val.get<uint64_t>());
                    break;
                case Value::Type::INT64:
                    strValue = to_string(val.get<int64_t>());
                    break;
                case Value::Type::FLOAT:
                    strValue = to_string(val.get<float>());
                    break;
                case Value::Type::DOUBLE:
                    strValue = to_string(val.get<double>());
                    break;
                case Value::Type::BOOL:
                    strValue = to_string(val.get<bool>());
                    break;
                case Value::Type::STRING:
                    strValue = val.get<std::string>();
                    break;
                case Value::Type::VNULL:
                    strValue = "NULL";
                    break;
                default:
                    strValue = "UNKNOWN_TYPE";
                    break;
                }

                rowData.push_back(strValue);
            }
            tableData.push_back(rowData);
        }
    }
    catch (const mysqlx::Error& err) {
        cout << "\nERROR: " << err << endl;
        return {};
    }
    catch (std::exception& ex) {
        cout << "\nSTD EXCEPTION: " << ex.what() << endl;
        return {};
    }
    catch (const char* ex) {
        cout << "\nEXCEPTION: " << ex << endl;
        return {};
    }

    return tableData;
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
        //tbl.reset();
        scm.reset();
        sess->close();
        sess.reset();
        conn = false;
        currTbl = "";
        msgs.push_back("SYS [MySQL]: Connection to MySQL server closed.");
    }
    else {
        msgs.push_back("ERROR [MySQL|closeConn()]: No active connection to MySQL server. Cannot perform action.");
    }

    return msgs;
}

