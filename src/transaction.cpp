#include "transaction.h"
#include <iostream>

void Transaction::begin() {
    state = State::ACTIVE;
    log.clear();
    std::cout << "Transaction started.\n";
}

void Transaction::commit() {
    if (state == State::ACTIVE) {
        state = State::COMMITTED;
        applyLog();
        std::cout << "Transaction committed.\n";
    } else {
        std::cerr << "Cannot commit. Transaction is not active.\n";
    }
}

void Transaction::rollback() {
    if (state == State::ACTIVE) {
        state = State::ABORTED;
        revertLog();
        std::cout << "Transaction rolled back.\n";
    } else {
        std::cerr << "Cannot rollback. Transaction is not active.\n";
    }
}

void Transaction::logOperation(const std::string& operation) {
    if (state == State::ACTIVE) {
        log.push_back(operation);
    } else {
        std::cerr << "Cannot log operation. Transaction is not active.\n";
    }
}

void Transaction::applyLog() {
    for (const auto& operation : log) {
        // Apply each logged operation to the database
        // This is a simplified example; actual implementation would be more complex
        std::cout << "Applying operation: " << operation << "\n";
    }
}

void Transaction::revertLog() {
    for (const auto& operation : log) {
        // Revert each logged operation
        // This is a simplified example; actual implementation would be more complex
        std::cout << "Reverting operation: " << operation << "\n";
    }
}