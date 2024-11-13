#include "transaction.h"
#include <iostream>
#include <cassert>

void testTransaction() {
    Transaction transaction;

    // Test begin
    transaction.begin();
    transaction.logOperation("INSERT INTO test_table VALUES (1, 'Alice', 30)");
    transaction.logOperation("INSERT INTO test_table VALUES (2, 'Bob', 25)");

    // Test commit
    transaction.commit();

    // Test rollback
    transaction.begin();
    transaction.logOperation("DELETE FROM test_table WHERE id = 1");
    transaction.rollback();

    std::cout << "Transaction tests passed.\n";
}

int main() {
    testTransaction();
    return 0;
}