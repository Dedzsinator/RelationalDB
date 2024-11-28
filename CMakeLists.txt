# FILE: CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Database)

set(CMAKE_CXX_STANDARD 20)

# Add the source files
add_executable(db src/db.cc src/table.cc src/utils.cc)

# Add the tests
add_subdirectory(tests)
enable_testing()