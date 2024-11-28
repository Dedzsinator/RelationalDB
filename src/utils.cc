#include "include/table.h"

std::ostream& operator<<(std::ostream& os, const FieldDefinition& fd) {
    os << fd.name << ':' << field_type_to_string.at(fd.type);
    return os;
}

std::ostream& operator<<(std::ostream& os, const Field& f) {
    switch (f.type) {
        case INTEGER:
            os << std::get<int>(f.val) << ':' << field_type_to_string.at(f.type);
            break;
        case STRING:
            os << std::get<std::string>(f.val) << ':' << field_type_to_string.at(f.type);
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Row& r) {
    for (const auto &field : r.fields) {
        os << field << " ";
    }
    return os;
}

void FieldDefinition::serialize(std::ofstream &file) const {
    // Serialize field name length and field name
    size_t nameLength = name.size();
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(size_t));
    file.write(name.c_str(), nameLength);

    // Serialize field type
    FieldType fieldType = type;
    file.write(reinterpret_cast<const char*>(&fieldType), sizeof(FieldType));
}

FieldDefinition FieldDefinition::deserialize(std::ifstream &file) {
    // Deserialize field name length and field name
    size_t nameLength;
    file.read(reinterpret_cast<char*>(&nameLength), sizeof(size_t));
    char nameBuffer[nameLength];
    file.read(nameBuffer, nameLength);
    std::string name = std::string(nameBuffer, nameLength);

    // Deserialize field type
    FieldType type;
    file.read(reinterpret_cast<char*>(&type), sizeof(FieldType));

    return FieldDefinition(name, type);
}

void Field::serialize(std::ofstream &file) const {
    // Serialize field type first
    FieldType field_type = type;
    file.write(reinterpret_cast<char*>(&field_type), sizeof(FieldType));

    switch (field_type) {
        case INTEGER:
        {
            // Serialize the integer
            int v = std::get<int>(val);
            file.write(reinterpret_cast<char*>(&v), sizeof(int));

            break;
        }
        case STRING:
        {
            // Serialize the size of the string
            std::string s = std::get<std::string>(val);
            size_t s_length = s.size();
            file.write(reinterpret_cast<char*>(&s_length), sizeof(size_t));

            // Serialize string
            file.write(s.c_str(), s_length);

            break;
        }
    }
}

Field Field::deserialize(std::ifstream &file) {
    // Deserialize the field type first
    FieldType type;
    file.read(reinterpret_cast<char*>(&type), sizeof(FieldType));

    switch (type) {
        case INTEGER:
        {
            int val;
            file.read(reinterpret_cast<char*>(&val), sizeof(int));

            return Field(type, val);
        }
        case STRING:
        {
            size_t val_length;
            file.read(reinterpret_cast<char*>(&val_length), sizeof(size_t));

            char buffer[val_length];
            file.read(buffer, val_length);
            std::string val = std::string(buffer, val_length);
            
            return Field(type, val);
        }
    }

    return Field(type, 0);
}

void Row::serialize(std::ofstream& file) const {
    // Serialize the size
    file.write(reinterpret_cast<const char*>(&size), sizeof(size_t));

    // Serialize every field
    for (const auto &f : fields) {
        f.serialize(file);
    }
}

Row Row::deserialize(std::ifstream& file) {
    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size_t));

    std::vector<Field> fields;
    for (unsigned int i = 0; i < size; ++i) {
        fields.push_back(Field::deserialize(file));
    }

    return Row(fields);
}

void Schema::serialize(std::ofstream &file) const {
    // Serialize schema size
    file.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
    
    // Serialize field definitions
    for (const FieldDefinition &def : Schema::field_defs) {
        def.serialize(file);
    }
}

Schema Schema::deserialize(std::ifstream &file) {
    // Deserialize schema size
    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size_t));

    // Deserialize all field definition
    std::vector<FieldDefinition> field_defs;
    for (unsigned int i = 0; i < size; ++i) {
        field_defs.push_back(FieldDefinition::deserialize(file));
    }

    return Schema(field_defs);
}

void Table::serialize(const std::string& file_path) const {
    std::ofstream file(file_path, std::ios::out);

    // Serialize the name of the table
    size_t name_length = name.size();
    file.write(reinterpret_cast<char*>(&name_length), sizeof(size_t));
    file.write(name.c_str(), name_length);

    // Serialize the schema
    schema.serialize(file);

    // Serialize size of row vector
    size_t data_length = data.size();
    file.write(reinterpret_cast<char*>(&data_length), sizeof(size_t));

    // Serialize all rows
    for (const auto &r : data) {
        r.serialize(file);
    }
}

Table Table::deserialize(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::out);

    // Deserialize length of name
    size_t name_length;
    file.read(reinterpret_cast<char*>(&name_length), sizeof(size_t));

    // Deserialize name string
    char name_buffer[name_length];
    file.read(name_buffer, name_length);
    std::string name = std::string(name_buffer, name_length);

    // Deserialize the schema
    Schema schema = Schema::deserialize(file);

    // Deserialize the size of row vector
    size_t num_rows;
    file.read(reinterpret_cast<char*>(&num_rows), sizeof(size_t));

    // Deserialize all the rows
    std::vector<Row> data;
    for (unsigned int i = 0; i < num_rows; ++i) {
        data.push_back(Row::deserialize(file));
    }

    return Table(name, schema, data);
}
