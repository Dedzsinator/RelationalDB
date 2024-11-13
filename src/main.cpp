#include "server.h"
#include <iostream>

int main() {
    Server server(8080);
    if (server.start()) {
        std::cout << "Database server is running on port 8080..." << std::endl;
        server.run();
    } else {
        std::cerr << "Failed to start the server." << std::endl;
    }
    return 0;
}
