#include "../table.h"
#include <iostream>
#include <cassert>

void testTable() {
    // Create a table
    Table table("test_table", {"id", "name", "age"});
    std::cout << "Table created.\n";

    // Insert rows
    table.insert({"1", "Alice", "30"});
    table.insert({"2", "Bob", "25"});
    std::cout << "Rows inserted.\n";

    // Save to disk
    table.saveToDisk();
    std::cout << "Table saved to disk.\n";

    // Create a new table object and load from disk
    Table loadedTable("test_table", {});
    loadedTable.loadFromDisk();
    std::cout << "Table loaded from disk.\n";

    // Select rows and verify
    auto rows = loadedTable.select({"id", "name", "age"});
    std::cout << "Rows selected.\n";
    std::cout << "Number of rows: " << rows.size() << "\n";
    for (const auto& row : rows) {
        for (const auto& value : row) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Verifying rows...\n";
    if (rows.size() != 2) {
        std::cerr << "Error: Expected 2 rows, but got " << rows.size() << "\n";
    }
    assert(rows.size() == 2);

    if (!(rows[0][0] == "1" && rows[0][1] == "Alice" && rows[0][2] == "30")) {
        std::cerr << "Error: First row does not match expected values.\n";
        std::cerr << "Expected: 1 Alice 30\n";
        std::cerr << "Got: " << rows[0][0] << " " << rows[0][1] << " " << rows[0][2] << "\n";
    }
    assert(rows[0][0] == "1" && rows[0][1] == "Alice" && rows[0][2] == "30");

    if (!(rows[1][0] == "2" && rows[1][1] == "Bob" && rows[1][2] == "25")) {
        std::cerr << "Error: Second row does not match expected values.\n";
        std::cerr << "Expected: 2 Bob 25\n";
        std::cerr << "Got: " << rows[1][0] << " " << rows[1][1] << " " << rows[1][2] << "\n";
    }
    assert(rows[1][0] == "2" && rows[1][1] == "Bob" && rows[1][2] == "25");

    std::cout << "All tests passed.\n";
}

int main() {
    testTable();
    return 0;
}