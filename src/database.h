#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <unordered_map>
#include <memory>
#include "table.h"

class Database {
public:
    void createTable(const std::string& name, const std::vector<std::string>& columns);
    void dropTable(const std::string& name);
    Table* getTable(const std::string& name);

private:
    std::unordered_map<std::string, std::unique_ptr<Table>> tables;
};

#endif
