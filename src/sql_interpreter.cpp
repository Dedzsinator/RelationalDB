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
            std::string columnsStr;
            std::getline(stream, columnsStr);
            // Assuming columns are in the format: (col1 type1, col2 type2, ...)
            std::vector<std::string> columns;
            size_t start = columnsStr.find('(') + 1;
            size_t end = columnsStr.find(')');
            std::string cols = columnsStr.substr(start, end - start);
            std::istringstream colStream(cols);
            std::string col;
            while (std::getline(colStream, col, ',')) {
                // Extract only the column name (before the space)
                columns.push_back(col.substr(0, col.find(' ')));
            }
            db.createTable(tableName, columns);
            return "Table created successfully";
        }
    } else if (command == "INSERT") {
        std::string into;
        stream >> into;
        if (into == "INTO") {
            std::string tableName;
            stream >> tableName;
            std::string valuesStr;
            std::getline(stream, valuesStr);
            // Assuming values are in the format: (val1, val2, ...)
            std::vector<std::string> values;
            size_t start = valuesStr.find('(') + 1;
            size_t end = valuesStr.find(')');
            std::string vals = valuesStr.substr(start, end - start);
            std::istringstream valStream(vals);
            std::string val;
            while (std::getline(valStream, val, ',')) {
                values.push_back(val);
            }
            db.insertIntoTable(tableName, values);
            return "Row inserted successfully";
        }
    } else if (command == "SELECT") {
        std::string columnsStr;
        std::getline(stream, columnsStr, ' ');
        std::string from;
        stream >> from;
        if (from == "FROM") {
            std::string tableName;
            stream >> tableName;
            // Parse columns
            std::vector<std::string> columns;
            std::istringstream colStream(columnsStr);
            std::string col;
            while (std::getline(colStream, col, ',')) {
                columns.push_back(col);
            }
            // Implement the actual selection logic here
            std::string result = db.selectFromTable(tableName, columnsStr);
            std::cout << "SELECT result: " << result << std::endl; // Debug statement
            return result;
        }
    }
    return "Unknown command";
}