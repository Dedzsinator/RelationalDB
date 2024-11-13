#ifndef SQL_INTERPRETER_H
#define SQL_INTERPRETER_H

#include "database.h"
#include <string>

class SQLInterpreter {
public:
    explicit SQLInterpreter(Database& db);
    std::string parseAndExecute(const std::string& query);

private:
    Database& db;
};

#endif
