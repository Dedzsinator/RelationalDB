#include "sql_interpreter.h"
#include <sstream>
#include <iostream>

SQLInterpreter::SQLInterpreter(Database& db) : db(db) {}

std::string SQLInterpreter::parseAndExecute(const std::string& query) {
    std::istringstream stream(query);
    std::string command;
    stream >> command;

    if (command == "CREATE") {
        std::string table;
        stream >> table;
        if (table == "TABLE") {
            std::string tableName;
            stream >> tableName;
            // Parse columns and types
            std::string columns;
            std::getline(stream, columns);
            // Assuming columns are in the format: (col1 type1, col2 type2, ...)
            // Implement the actual parsing and table creation logic here
            db.createTable(tableName, columns);
            return "Table created successfully";
        }
    } else if (command == "INSERT") {
        std::string into;
        stream >> into;
        if (into == "INTO") {
            std::string tableName;
            stream >> tableName;
            std::string values;
            std::getline(stream, values);
            // Assuming values are in the format: (val1, val2, ...)
            // Implement the actual parsing and insertion logic here
            db.insertIntoTable(tableName, values);
            return "Row inserted successfully";
        }
    } else if (command == "SELECT") {
        std::string columns;
        stream >> columns;
        std::string from;
        stream >> from;
        if (from == "FROM") {
            std::string tableName;
            stream >> tableName;
            // Implement the actual selection logic here
            std::string result = db.selectFromTable(tableName, columns);
            return result;
        }
    }
    return "Unknown command";
}