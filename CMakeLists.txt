cmake_minimum_required(VERSION 3.10)
project(MyDBDaemon)
set(CMAKE_CXX_STANDARD 20)

# Add the main application executable
add_executable(mydb_daemon
    src/main.cpp
    src/server.cpp
    src/database.cpp
    src/table.cpp
    src/sql_interpreter.cpp
)

# Add the test executables
add_executable(test_bplustree src/tests/test_bplustree.cpp src/bplustree.cpp)
add_executable(test_sqlinterpreter src/tests/test_sqlinterpreter.cpp src/sql_interpreter.cpp src/database.cpp src/table.cpp)
add_executable(test_server src/tests/test_server.cpp src/server.cpp)
add_executable(test_transaction src/tests/test_transaction.cpp src/transaction.cpp)
add_executable(test_table src/tests/test_table.cpp src/table.cpp)

# Add custom targets for running the tests
add_custom_target(run_tests
    COMMAND test_sqlinterpreter && test_server && test_transaction && test_bplustree && test_table
    DEPENDS test_sqlinterpreter test_server test_transaction test_bplustree test_table
    COMMENT "Running all tests..."
)

# Add a custom command to build the main application only if the tests pass
add_custom_command(TARGET mydb_daemon POST_BUILD
    COMMAND ${CMAKE_COMMAND} --build . --target run_tests
    COMMENT "Building main application only if tests pass..."
)

# Ensure the tests are run before building the main application
add_dependencies(mydb_daemon run_tests)