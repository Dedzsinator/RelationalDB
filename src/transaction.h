#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <string>
#include <unordered_map>

class Transaction {
public:
    void begin();
    void commit();
    void rollback();
    void logOperation(const std::string& operation); // Move this to public

private:
    enum class State { ACTIVE, COMMITTED, ABORTED };
    State state;
    std::vector<std::string> log; // Simplified log for demonstration purposes

    void applyLog();
    void revertLog();
};

#endif // TRANSACTION_H