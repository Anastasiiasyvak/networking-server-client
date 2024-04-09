#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>

#include "SafeFile.hpp"

#define PORT 15000
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    recv(client_socket, buffer, BUFFER_SIZE, 0);
    std::cout << "Received from client: " << buffer << std::endl;

    send(client_socket, "Wait", strlen("Wait"), 0);
    sleep(1);

    send(client_socket, "Ready", strlen("Ready"), 0);

    memset(buffer, 0, BUFFER_SIZE);
    recv(client_socket, buffer, BUFFER_SIZE, 0);

    SafeFile::writeToFile("/home/ubuntu/request.txt", buffer);

    send(client_socket, "Ok", strlen("Ok"), 0);

    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Error in socket creation" << std::endl;
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error in binding" << std::endl;
        return -1;
    }

    if (listen(server_socket, 5) < 0) {
        std::cerr << "Error in listening" << std::endl;
        return -1;
    }

    while (true) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            std::cerr << "Error in accepting connection" << std::endl;
            continue;
        }

        std::thread(handle_client, client_socket).detach();
    }

    close(server_socket);
    return 0;
}

