// FILE: tests/test_table.cpp
#include <iostream>
#include <sstream>
#include "include/table.h"
#include "include/db.h"

void test_create_table() {
    std::stringstream ss("create my_table id:int name:string age:int");
    execute_sql(CREATE, ss);
    tables["my_table"]->print_schema();
}

void test_insert_row() {
    std::stringstream ss("insert my_table 1:int John:string 25:int");
    execute_sql(INSERT, ss);
    tables["my_table"]->select_all();
}

int main() {
    test_create_table();
    test_insert_row();
    return 0;
}