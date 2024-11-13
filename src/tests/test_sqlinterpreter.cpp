#include "sql_interpreter.h"
#include "database.h"
#include <iostream>
#include <cassert>

void testSQLInterpreter() {
    Database db;
    SQLInterpreter interpreter(db);

    // Test CREATE TABLE
    std::string createTableQuery = "CREATE TABLE test_table (id INT, name TEXT, age INT)";
    assert(interpreter.parseAndExecute(createTableQuery) == "Table created successfully");

    // Test INSERT INTO
    std::string insertQuery = "INSERT INTO test_table VALUES (1, 'Alice', 30)";
    assert(interpreter.parseAndExecute(insertQuery) == "Row inserted successfully");

    // Test SELECT
    std::string selectQuery = "SELECT id, name, age FROM test_table";
    std::string result = interpreter.parseAndExecute(selectQuery);
    assert(result.find("Alice") != std::string::npos);

    std::cout << "SQLInterpreter tests passed.\n";
}

int main() {
    testSQLInterpreter();
    return 0;
}