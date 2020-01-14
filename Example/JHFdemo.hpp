//
//  JHFdemo.hpp
//  Example
//
//  Created by desarrollo on 1/14/20.
//  Copyright © 2020 dev. All rights reserved.
//
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <array>
#include <stdio.h>
#include <cstdio>
#include <sqlite3.h>
#include <string>
#include <stdio.h>
#ifndef JHFdemo_h
#define JHFdemo_h
using json = nlohmann::json;
using namespace std;

class DemoClass{
private:
  int response;
public:
  int FunctionDemo (std::string _jsonfPath, std::string _dbfPath)
  {
    std::cout << "Example ...\n";
    //define variables
    std::string jsonfPath;
    std::string dbfPath;
    jsonfPath = _jsonfPath;
    dbfPath = _dbfPath;
    
    //int code_return;
    // variables for sql transactions
    std::string sql_createTable;
    std::string sql_insert;
    
    // Create SQL Table
    sql_createTable= "CREATE TABLE IF NOT EXISTS Persona("  \
    "id VARCHAR NOT NULL," \
    "name INT NOT NULL," \
    "email VARCHAR," \
    "telephone VARCHAR,"\
    "PRIMARY KEY(id,email));";

    
    //declarate sqlite instance
    sqlite3 *db;
    char *zErrMsg = 0; //variable for sqlite error message
    int connection; // variable for sqlite connection
    
    try {
      //Read JSON FILE
      std::ifstream file(jsonfPath); //json file path
      json j = json::parse(file); // function for read json file
      
    } catch(exception e)  {
      cout << "Json File is missing or Error while decoding Json File";
      return 1;
    }
    
    
    //IF for evaluate if connection is success or no
    // open connection to database and storage status
    connection = sqlite3_open(dbfPath.c_str(), &db);
    if( connection != SQLITE_OK ) {
      fprintf(stderr, "Database not found: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      return  2;
    }
    
    
    else{
      connection = sqlite3_exec(db, sql_createTable.c_str(), NULL, 0, &zErrMsg);
      if (connection == SQLITE_OK) {
        std::ifstream file(jsonfPath); //json file path
        json j = json::parse(file); // function for read json file
        //cout << j;
        int id = j["id"];
        string name = j["name"];
        string email = j["email"];
        string telephone = j["telephone"];
        sql_insert  = "INSERT INTO Persona VALUES("+std::to_string(id)+",'"+ name+"','"+email+"','"+telephone+"');";
        cout << sql_insert << "\n";
        connection = sqlite3_exec(db, sql_insert.c_str(), NULL, 0, &zErrMsg);
        if(connection == SQLITE_OK){
          cout << "The data was inserted! \n";
          sqlite3_close(db);    // close connection to database
          // Delete json file
          int remove_file;
          remove_file = remove(jsonfPath.c_str());
          if ( remove_file != 0) { //evaluation of remove function result
            cout << "File can not be deleted \n";
          }else {
            cout << "File deleted successfull \n";
          }
        }
        else{
          cout << "Error to try to insert \n";
          sqlite3_close(db);    // close connection to database
          return 3;
        }
      }
      sqlite3_close(db);    // close connection to database
    }return 0;
  }
};

#endif /* JHFdemo_h */
