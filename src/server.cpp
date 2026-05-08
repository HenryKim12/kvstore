#include "../include/server.h"
#include <arpa/inet.h>
#include <stdexcept>
#include <sys/socket.h>
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
    throw std::runtime_error("Failed to create socket");

  int opt = 1;
  setsockopt(serverSocket_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  struct sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port_);

  if (bind(serverSocket_, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    throw std::runtime_error("Failed to bind");

  if (listen(serverSocket_, SOMAXCONN) < 0)
    throw std::runtime_error("Failed to listen");

  while (true) {
    int clientSocket = accept(serverSocket_, nullptr, nullptr);
    if (clientSocket < 0)
      break;
    handleClient(clientSocket);
    close(clientSocket);
  }
}

void Server::handleClient(int clientSocket) { (void)clientSocket; }
