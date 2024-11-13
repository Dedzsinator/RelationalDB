#include "database.h"
#include <iostream>

void Database::createTable(const std::string& name, const std::vector<std::string>& columns) {
    tables[name] = std::make_unique<Table>(name, columns);
    std::cout << "Table '" << name << "' created successfully.\n";
}

void Database::dropTable(const std::string& name) {
    tables.erase(name);
    std::cout << "Table '" << name << "' dropped successfully.\n";
}

Table* Database::getTable(const std::string& name) {
    auto it = tables.find(name);
    return (it != tables.end()) ? it->second.get() : nullptr;
}
