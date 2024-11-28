#include "../sql_interpreter.h"
#include "../database.h"
#include <iostream>
#include <cassert>

void testSQLInterpreter() {
    Database db;
    SQLInterpreter interpreter(db);

    // Test CREATE TABLE
    std::string createTableQuery = "CREATE TABLE test_table (id INT, name TEXT, age INT)";
    std::string createResult = interpreter.parseAndExecute(createTableQuery);
    std::cout << "CREATE TABLE result: " << createResult << std::endl;

    // Test INSERT INTO
    std::string insertQuery = "INSERT INTO test_table VALUES (1, 'Alice', 30)";
    std::string insertResult = interpreter.parseAndExecute(insertQuery);
    std::cout << "INSERT INTO result: " << insertResult << std::endl;

    // Test SELECT
    std::string selectQuery = "SELECT id, name, age FROM test_table";
    std::string result = interpreter.parseAndExecute(selectQuery);
    std::cout << "SELECT result: " << result << std::endl;

    if (result.find("Alice") == std::string::npos) {
        std::cerr << "Error: 'Alice' not found in SELECT result.\n";
    }

    // Print the results on the screen
    std::cout << "Final SELECT result: " << result << std::endl;

    std::cout << "SQLInterpreter tests completed.\n";
}

int main() {
    testSQLInterpreter();
    return 0;
}