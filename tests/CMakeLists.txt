# FILE: tests/CMakeLists.txt
add_executable(test_table test_table.cpp)
target_link_libraries(test_table db)

add_test(NAME TestTable COMMAND test_table)