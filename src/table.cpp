#include "table.h"
#include <iostream>
#include <algorithm>
#include <fstream>

Table::Table(const std::string& name, const std::vector<std::string>& columns)
    : name(name), columns(columns) {}

void Table::insert(const std::vector<std::string>& values) {
    if (values.size() != columns.size()) {
        std::cerr << "Error: Column count does not match value count.\n";
        return;
    }
    rows.push_back(values);
    std::cout << "Row inserted.\n";
}

std::vector<std::vector<std::string>> Table::select(const std::vector<std::string>& columns) {
    std::vector<std::vector<std::string>> result;
    std::vector<int> columnIndices;

    for (const auto& col : columns) {
        auto it = std::find(this->columns.begin(), this->columns.end(), col);
        if (it != this->columns.end()) {
            columnIndices.push_back(std::distance(this->columns.begin(), it));
        } else {
            std::cerr << "Error: Column " << col << " does not exist.\n";
            return result;
        }
    }

    for (const auto& row : rows) {
        std::vector<std::string> selectedRow;
        for (int index : columnIndices) {
            selectedRow.push_back(row[index]);
        }
        result.push_back(selectedRow);
    }

    return result;
}

void Table::update(const std::string& column, const std::string& value, const std::string& condition) {
    auto it = std::find(columns.begin(), columns.end(), column);
    if (it == columns.end()) {
        std::cerr << "Error: Column " << column << " does not exist.\n";
        return;
    }
    int columnIndex = std::distance(columns.begin(), it);

    for (auto& row : rows) {
        // Simplified: update all rows for demonstration purposes
        row[columnIndex] = value;
    }
    std::cout << "Rows updated.\n";
}

void Table::deleteRows(const std::string& condition) {
    // Simplified: delete all rows for demonstration purposes
    rows.clear();
    std::cout << "Rows deleted.\n";
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