#include "table.h"
#include <iostream>
#include <cassert>

void testTable() {
    // Create a table
    Table table("test_table", {"id", "name", "age"});

    // Insert rows
    table.insert({"1", "Alice", "30"});
    table.insert({"2", "Bob", "25"});

    // Save to disk
    table.saveToDisk();

    // Create a new table object and load from disk
    Table loadedTable("test_table", {});
    loadedTable.loadFromDisk();

    // Select rows and verify
    auto rows = loadedTable.select({"id", "name", "age"});
    assert(rows.size() == 2);
    assert(rows[0][0] == "1" && rows[0][1] == "Alice" && rows[0][2] == "30");
    assert(rows[1][0] == "2" && rows[1][1] == "Bob" && rows[1][2] == "25");

    std::cout << "All tests passed.\n";
}

int main() {
    testTable();
    return 0;
}