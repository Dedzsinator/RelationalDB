#include "database.h"
#include <iostream>
#include <sstream>
#include <algorithm> // For std::isspace

std::string trim(const std::string& str) {
    const auto first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return ""; // No content
    const auto last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

void Database::createTable(const std::string& tableName, const std::vector<std::string>& columnNames) {
    if (tables.find(tableName) != tables.end()) {
        throw std::runtime_error("Error: Table '" + tableName + "' already exists.");
    }
    tables[tableName] = std::make_unique<Table>(tableName, columnNames);
}

void Database::dropTable(const std::string& name) {
    tables.erase(name);
    std::cout << "Table '" << name << "' dropped successfully.\n";
}

Table* Database::getTable(const std::string& name) {
    auto it = tables.find(name);
    return (it != tables.end()) ? it->second.get() : nullptr;
}

void Database::insertIntoTable(const std::string& tableName, const std::vector<std::string>& values) {
    Table* table = getTable(tableName);
    if (table) {
        table->insert(values);
    } else {
        std::cerr << "Table '" << tableName << "' does not exist.\n";
    }
}

std::string Database::selectFromTable(const std::string& tableName, const std::string& columns) {
    if (tables.find(tableName) == tables.end()) {
        throw std::runtime_error("Error: Table '" + tableName + "' does not exist.");
    }

    Table* table = tables[tableName].get();

    // Debug: Print table columns to check if they match
    std::cout << "Table columns: ";
    for (const auto& col : table->getColumns()) {
        std::cout << col << " ";
    }
    std::cout << std::endl;

    // Parse columns (assuming comma-separated string)
    std::vector<std::string> columnList;
    std::istringstream ss(columns);
    std::string column;
    while (std::getline(ss, column, ',')) {
        columnList.push_back(trim(column));  // Trim column names
    }

    // Validate columns
    for (const auto& col : columnList) {
        if (std::find(table->getColumns().begin(), table->getColumns().end(), col) == table->getColumns().end()) {
            throw std::runtime_error("Error: Column '" + col + "' does not exist.");
        }
    }

    // Select rows
    auto result = table->select(columnList);

    // Build result string
    std::ostringstream oss;
    for (const auto& row : result) {
        for (const auto& value : row) {
            oss << value << " ";
        }
        oss << "\n";
    }
    return oss.str();
}