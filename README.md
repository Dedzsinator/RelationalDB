# Description

In this project, I am writing my own idea for a relational database from scratch. I am trying to do so without much outside influence, to see how I would implement some DBMS ideas. The database will use a basic version of SQL with some changes to make it easier for me to parse.

# Usage

1. Compile all <code>.cc</code> files in the src folder with <code>g++ -std=c++20 src/*.cc -o db</code>
2. Run the executable with <code>./db</code>
3. Create a new table with <code>create TABLE_NAME VAR_NAME:VAR_TYPE...</code>
4. Insert to the table with <code>insert TABLE_NAME VAR_VAL:VAR_TYPE...</code>
5. View a table its rows with with <code>select TABLE_NAME</code>
6. Load a database with <code>load TABLE_NAME</code>

With each table creation and row insertion, the database should automatically serialize itself and save the data to disk. Tables are by default stored in <code>databases/</code>.

# To-Do

* Implement more comprehensive Select-From-Where queries
* Implement indexing with B+ Trees
