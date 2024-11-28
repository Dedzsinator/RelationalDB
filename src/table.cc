#include "include/table.h"

void Schema::print() {
    for (const auto &def : Schema::field_defs) {
        std::cout << def << " ";
    }

    std::cout << "\n";
}

bool Table::validate_row(Row &r) {
    if (r.size != Table::schema.size) {
        return false;
    }

    for (unsigned int i = 0; i < r.size; ++i) {
        if (r.fields[i].type != Table::schema.field_defs[i].type) {
            return false;
        }
    }

    return true;
}

void Table::print_schema() {
    Table::schema.print();
}

void Table::insert_row(Row &r) {
    std::cout << "Inserting row: " << r << std::endl; // Debugging statement
    if (validate_row(r)) {
        data.push_back(r);
        int key = std::get<int>(r.fields[0].val); // Assuming the first field is the key
        index.insert(key, r);
        std::cout << "Row inserted successfully." << std::endl; // Debugging statement
    } else {
        std::cout << "Row validation failed." << std::endl; // Debugging statement
    }
}

void Table::select_all() {
    for (const auto &r : data) {
        std::cout << r << "\n";
    }
}

std::vector<Row> Table::search_index(int key) {
    return index.search(key);
}