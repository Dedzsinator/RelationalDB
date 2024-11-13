#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>

class Table {
public:
    Table(const std::string& name, const std::vector<std::string>& columns);
    void insert(const std::vector<std::string>& values);
    std::vector<std::vector<std::string>> select(const std::vector<std::string>& columns);
    void update(const std::string& column, const std::string& value, const std::string& condition);
    void deleteRows(const std::string& condition);
    void saveToDisk();
    void loadFromDisk();

private:
    std::string name;
    std::vector<std::string> columns;
    std::vector<std::vector<std::string>> rows;
};

#endif // TABLE_H