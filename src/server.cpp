#include "../include/server.h"
#include "../include/protocol.h"
#include <arpa/inet.h>
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

Server::Server(Store &store, int port)
    : store_(store), port_(port), serverSocket_(-1) {}

Server::~Server() {
  if (serverSocket_ >= 0)
    close(serverSocket_);
}

void Server::start() {
  serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket_ < 0)
    throw std::runtime_error("[Server] Failed to create socket");

  int opt = 1;
  setsockopt(serverSocket_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  struct sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port_);

  if (bind(serverSocket_, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    throw std::runtime_error("[Server] Failed to bind");

  if (listen(serverSocket_, SOMAXCONN) < 0)
    throw std::runtime_error("[Server] Failed to listen");

  while (true) {
    int clientSocket = accept(serverSocket_, nullptr, nullptr);
    if (clientSocket < 0)
      break;
    std::thread([this, clientSocket]() {
      handleClient(clientSocket);
      close(clientSocket);
    }).detach();
  }
}

void Server::handleClient(int clientSocket) {
  char buffer[1024];
  while (true) {
    ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));
    if (bytesRead <= 0)
      break;

    std::string_view rawInput(buffer, bytesRead);
    std::cout << "[Server] Received command : " << rawInput;
    ParsedCommand command = parseInput(rawInput);

    switch (command.type) {
    case CommandType::SET:
      store_.set(command.key, *command.value);
      write(clientSocket, "OK\n", 3);
      break;
    case CommandType::GET: {
      auto value = store_.get(command.key);
      if (value.has_value()) {
        std::string response = value.value() + "\n";
        write(clientSocket, response.c_str(), response.size());
      } else {
        write(clientSocket, "NULL\n", 5);
      }
      break;
    }
    case CommandType::DEL:
      store_.del(command.key);
      write(clientSocket, "OK\n", 3);
      break;
    case CommandType::UNKOWN:
      std::cout << "ERR unknown command: " << rawInput;
      write(clientSocket, "ERR unknown command\n", 20);
      break;
    }
  }
}
