#include "table.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

Table::Table(const std::string& name, const std::vector<std::string>& columns)
    : name(name), columns(columns) {
    // Optionally, print the columns for debugging
    std::cout << "Table created with columns: ";
    for (const auto& col : columns) {
        std::cout << col << " ";
    }
    std::cout << std::endl;
}

void Table::insert(const std::vector<std::string>& values) {
    if (values.size() != columns.size()) {
        throw std::runtime_error("Error: Number of values does not match number of columns.");
    }
    rows.push_back(values);
}


std::vector<std::vector<std::string>> Table::select(const std::vector<std::string>& columns) {
    // Find indices of the requested columns
    std::vector<int> columnIndices;
    for (const auto& col : columns) {
        auto it = std::find(this->columns.begin(), this->columns.end(), col);
        if (it == this->columns.end()) {
            throw std::runtime_error("Error: Column '" + col + "' does not exist.");
        }
        columnIndices.push_back(std::distance(this->columns.begin(), it));
    }

    // Extract rows with only the specified columns
    std::vector<std::vector<std::string>> result;
    for (const auto& row : rows) {
        std::vector<std::string> selectedRow;
        for (const auto& index : columnIndices) {
            selectedRow.push_back(row[index]);
        }
        result.push_back(selectedRow);
    }

    return result;
}

void update(const std::string& column, const std::string& value, const std::string& condition) {
    // Implement update
}

void deleteRows(const std::string& condition) {
    // Implement delete
}

void Table::saveToDisk() {
    std::ofstream file(name + ".tbl");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }
    // Write columns
    for (const auto& column : columns) {
        file << column << ",";
    }
    file << "\n";
    // Write rows
    for (const auto& row : rows) {
        for (const auto& value : row) {
            file << value << ",";
        }
        file << "\n";
    }
    file.close();
    std::cout << "Table saved to disk.\n";
}

const std::vector<std::string>& Table::getColumns() const {
    return columns;
}

void Table::loadFromDisk() {
    std::ifstream file(name + ".tbl");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for reading.\n";
        return;
    }
    columns.clear();
    rows.clear();
    std::string line;
    // Read columns
    if (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string column;
        while (std::getline(ss, column, ',')) {
            if (!column.empty()) {
                columns.push_back(column);
            }
        }
    }
    // Read rows
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string value;
        std::vector<std::string> row;
        while (std::getline(ss, value, ',')) {
            if (!value.empty()) {
                row.push_back(value);
            }
        }
        if (!row.empty()) {
            rows.push_back(row);
        }
    }
    file.close();
    std::cout << "Table loaded from disk.\n";
}