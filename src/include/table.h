#include <vector>
#include <utility>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <variant>
#include <unordered_map>
#include "bptree.h"

typedef enum {
    INTEGER,
    STRING,
} FieldType;

typedef std::variant<int, std::string> FieldValue;

const std::unordered_map<std::string, FieldType> string_to_field_type = {
    {"int", INTEGER},
    {"string", STRING}
};

const std::unordered_map<FieldType, std::string> field_type_to_string = {
    {INTEGER, "int"},
    {STRING, "string"}
};

class FieldDefinition {
    const std::string name;
    const FieldType type;

public:
    void serialize(std::ofstream &file) const;
    static FieldDefinition deserialize(std::ifstream &file);

    FieldDefinition(std::string n, FieldType t) : name{n}, type{t} {}

    friend std::ostream& operator<<(std::ostream& os, const FieldDefinition& fd);
    friend class Table;
};

class Field {
    FieldType type;
    FieldValue val;

public:
    void serialize(std::ofstream& file) const;
    static Field deserialize(std::ifstream& file);
    Field(FieldType t, FieldValue v) : type{t}, val{std::move(v)} {}

    Field(const Field& other) : type{other.type}, val{other.val} {}
    Field(Field&& other) noexcept : type{other.type}, val{std::move(other.val)} {}

    Field& operator=(const Field& other) {
        if (this != &other) {
            type = other.type;
            val = other.val;
        }
        return *this;
    }

    Field& operator=(Field&& other) noexcept {
        if (this != &other) {
            type = other.type;
            val = std::move(other.val);
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Field& f);
    friend class Table;
};

class Row {
    std::vector<Field> fields;

public:
    const size_t size;
    Row() : size{0} {} // Default constructor
    void serialize(std::ofstream& file) const;
    static Row deserialize(std::ifstream& file);
    Row(std::vector<Field> f) : fields{std::move(f)}, size{fields.size()} {}
    Row(const Row& other) : fields{other.fields}, size{other.size} {}
    Row(Row&& other) noexcept : fields{std::move(other.fields)}, size{other.size} {}
    Row& operator=(const Row& other) {
        if (this != &other) {
            fields = other.fields;
            const_cast<size_t&>(size) = other.size;
        }
        return *this;
    }
    Row& operator=(Row&& other) noexcept {
        if (this != &other) {
            fields = std::move(other.fields);
            const_cast<size_t&>(size) = other.size;
        }
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Row& r);
    friend class Table;
};

class Schema {
    const std::vector<FieldDefinition> field_defs;

public:
    void serialize(std::ofstream &file) const;
    static Schema deserialize(std::ifstream &file);

    const size_t size;
    Schema(std::vector<FieldDefinition> f) : field_defs{f}, size{f.size()} {}
    void print();

    friend class Table;
};

class Table {
    std::string name;
    std::vector<Row> data;
    BPTree<int, Row> index; // Assuming the index is on an integer field

    bool validate_row(Row &r);

public:
    Schema schema;
    Table(std::string n, Schema s, std::vector<Row> d) : name{n}, schema{s}, data{d}, index(3) {} // B+ Tree of degree 3

    void insert_row(Row &r);
    void select_all();
    void print_schema();
    std::vector<Row> search_index(int key);

    void serialize(const std::string& filePath) const;
    static Table deserialize(const std::string& filePath);
};