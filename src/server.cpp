#include "server.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

Server::Server(int port) : port(port) {}

bool Server::start() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        std::cerr << "Socket creation failed.\n";
        return false;
    }

    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cerr << "setsockopt failed.\n";
        close(server_fd);
        return false;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed.\n";
        close(server_fd);
        return false;
    }

    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed.\n";
        close(server_fd);
        return false;
    }

    std::cout << "Server started on port " << port << ".\n";
    return true;
}

void Server::run() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    while (true) {
        std::cout << "Waiting for a connection...\n";
        int clientSocket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (clientSocket < 0) {
            std::cerr << "Accept failed.\n";
            close(server_fd);
            return;
        }
        std::cout << "Connection accepted.\n";
        handleClient(clientSocket);
        close(clientSocket);
    }
}

void Server::handleClient(int clientSocket) {
    char buffer[1024] = {0};
    const char *hello = "Hello from server";
    int valread = read(clientSocket, buffer, 1024);
    std::cout << "Received: " << buffer << "\n";
    send(clientSocket, hello, strlen(hello), 0);
    std::cout << "Hello message sent\n";
}