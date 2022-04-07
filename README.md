## Basic DB

This is very basic solid/concrete database for basic c++ programs written in c++.
This is small expriment to create database.

## Features

- very light
- tables in csv
- fast
- easy to use

## Installation

Install basicdb with git

```bash
  mkdir my-project
  cd my-project
  git clone https://github.com/prolaxu/basicdb.git
```

Use libery in this way

```
//main.cpp

#include <iostream>
#include <string>
#include <vector>
#include "libs/basicdb/basicdb.h"

using namespace std;

// function toprint all objects
void print_all(vector<pair<string, string>> objects)
{
    for (pair<string, string> object : objects)
    {
        cout << object.first << ": " << object.second << endl;
    }
}
int main()
{
    cout << "Welcome to Library!" << endl;
    Database db; // create a database object
    db.connect("db/lms"); // connect to database  don't for date to  make folder db and db/lms

    // creating table
    db.createTable("users", {"name", "email", "password"});

    // table object
    Table users(db, "users");

    // inserting data
    users.create({
        {"password", "12345"},
        {"email", "john@gmail.com"},
        {"name", "Usre1"},
    });

    // fetch data
    vector<pair<string, string>> loginUser = users.findOne({
        {"email", "user1@gmail.com"},
        {"password", "12345678"},
    });

    if (loginUser.size() > 0)
    {
        cout << "##########################################" << endl;
        cout << "Login Successful!" << endl;
        print_all(loginUser);
        cout << "##########################################" << endl;
    }
    else
    {
        cout << "Login Failed!" << endl;
    }

    return 0;
}


```

## Author

[@solocodeninja](https://github.com/prolaxu)
