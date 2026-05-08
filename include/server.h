#pragma once
#include "store.h"

class Server {
public:
  explicit Server(Store &store, int port);
  ~Server();

  void start();

private:
  void handleClient(int clientSocket);

  Store &store_;
  int serverSocket_;
  int port_;
};
