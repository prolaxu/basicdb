#include <iostream>
#include <string>
#include "../bin/db.h"
using namespace std;

class Table
{
private:
    Tools tools;

public:
    string database;
    string table_name;
    string table_path;
    vector<string> headers;
    Table(Database db, string table)
    {
        this->database = db.database;
        this->table_name = table;
        this->table_path = this->database + "/" + this->table_name + ".csv";
        this->headers = this->getheaders();
        isTableExist();
    }
    vector<pair<string, string>> create(vector<pair<string, string>> values)
    {
        vector<string> headers = this->headers;

        ofstream tableFile;
        tableFile.open(this->table_path, ios::app);

        tableFile << "\"" << this->last_id() << "\",";
        for (pair<string, string> value : this->sort(values))
        {
            tableFile << "\"" << value.second << "\",";
        }
        // created at
        string currentdate = tools.getCurrentDateTime();
        tableFile << "\"" << currentdate << "\",\"null\"" << endl;
        tableFile.close();
        return values;
    }
    // check_conditions
    bool check_conditions(vector<pair<string, string>> object, vector<pair<string, string>> conditions, string method)
    {
        vector<bool> results;
        for (pair<string, string> condition : conditions)
        {
            for (pair<string, string> object_value : object)
            {
                if (condition.first.compare(object_value.first) == 0)
                {
                    results.push_back(condition.second.compare(object_value.second) == 0);
                }
            }
        }
        if (method == "AND")
        {
            for (bool result : results)
            {
                if (!result)
                {
                    return false;
                }
            }
            return true;
        }
        else if (method == "OR")
        {
            for (bool result : results)
            {
                if (result)
                {
                    return true;
                }
            }
            return false;
        }
        return false;
    }

    // select with where conditions
    vector<vector<pair<string, string>>> select(vector<pair<string, string>> conditions, string method = "AND")
    {
        vector<vector<pair<string, string>>> final_objects;
        ifstream tableFile;
        tableFile.open(this->table_path);
        string line;

        while (getline(tableFile, line))
        {
            vector<pair<string, string>> processed_obj = this->process_csv_line(line);
            if (this->check_conditions(processed_obj, conditions, method))
            {
                final_objects.push_back(processed_obj);
            }
        }
        tableFile.close();
        return final_objects;
    }

    // find one
    vector<pair<string, string>> findOne(vector<pair<string, string>> conditions, string method = "AND")
    {
        vector<vector<pair<string, string>>> objects = this->select(conditions, method);
        if (objects.size() > 0)
        {
            return objects[0];
        }
        return {};
    }
    bool isTableExist()
    {
        if (!tools.file_exists(this->table_path.data()))
        {
            cout << "Table does not exist" << endl;
            return false;
        }
        return true;
    }
    vector<string> getheaders()
    {
        ifstream file;
        file.open(table_path);
        string line;
        vector<string> headers;
        getline(file, line);
        headers = tools.split_str(line, ",");
        file.close();
        return headers;
    }
    // get last row of table
    vector<pair<string, string>> last_row()
    {
        ifstream file;
        file.open(this->table_path);
        string line;
        string lastLine;
        while (getline(file, line))
        {
            lastLine = line;
        }
        file.close();
        return this->process_csv_line(lastLine);
    }
    // process csv line to c++ object
    vector<pair<string, string>> process_csv_line(string line)
    {
        vector<pair<string, string>> values;
        vector<string> splittedLine = tools.split_str(line, ",");
        int i = 0;
        for (string value : splittedLine)
        {
            pair<string, string> pair;
            pair.first = this->tools.trim_ends(this->headers[i]);
            pair.second = this->tools.trim_ends(value);
            values.push_back(pair);
            i++;
        }
        return values;
    }
    int keyOf(string value)
    {
        vector<string> headers = this->headers;
        for (int i = 0; i < headers.size(); i++)
        {
            string key = this->tools.trim_ends(headers[i]);
            if (key.compare(value) == 0)
            {
                return i;
            }
        }
        return -1;
    }
    int last_id()
    {
        string id = this->last_row()[0].second;
        if (id.compare("id") == 0)
        {
            return 1;
        }
        return stoi(id) + 1;
    }

    // sort values according to headers
    vector<pair<string, string>> sort(vector<pair<string, string>> values)
    {
        vector<pair<string, string>> sortedValues;
        vector<string> headers = this->headers;
        for (int i = 0; i < headers.size(); i++)
        {
            string key = this->tools.trim_ends(headers[i]);
            for (pair<string, string> value : values)
            {
                if (key.compare(value.first) == 0)
                {
                    sortedValues.push_back(value);
                }
            }
        }
        return sortedValues;
    }
};