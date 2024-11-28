#include "../server.h"
#include <iostream>
#include <cassert>

void testServer() {
    Server server(8080);

    // Test start
    assert(server.start());

    // Test run (this would normally block, so we won't actually call it here)
    // server.run();

    std::cout << "Server tests passed.\n";
}

int main() {
    testServer();
    return 0;
}