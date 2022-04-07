// File based database program
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <filesystem>
#include <dirent.h>
#include "../bin/tools.h"

using namespace std;
// Database class
class Database
{
public:
    string database;
    Tools tools;
    // Database(){}
    bool connect(string database)
    {
        if (!tools.dir_exists(database.data()))
        {
            cout << "Database does not exist" << endl;
            return false;
        }
        this->database = database;
        cout << "Connected to database" << endl;
        return true;
    }
    void createTable(string tableName, vector<string> columns)
    {
        string tablePath = database + "/" + tableName + ".csv";
        if (tools.dir_exists(tablePath.data()))
        {
            cout << "Table already exists" << endl;
            return;
        }
        ofstream tableFile;
        tableFile.open(tablePath);
        tableFile << "\"id\",";
        for (string column : columns)
        {
            tableFile << "\"" << column << "\",";
        }
        tableFile << "\"created_at\",";
        tableFile << "\"updated_at\"\n";

        tableFile.close();
        cout << "Table created" << endl;
    }
};