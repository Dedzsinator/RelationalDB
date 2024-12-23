#ifndef SERVER_H
#define SERVER_H

class Server {
public:
    explicit Server(int port);
    bool start();
    void run();

private:
    int port;
    void handleClient(int clientSocket);
};

#endif