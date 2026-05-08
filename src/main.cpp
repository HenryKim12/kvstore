#include "../include/server.h"
#include "../include/store.h"
#include <_stdio.h>
#include <iostream>

int main() {
  std::cout << "Initializing store..." << std::endl;
  Store store;
  std::cout << "Done!" << std::endl;

  std::cout << "Starting server..." << std::endl;
  Server server(store, 6379);
  std::cout << "Done!" << std::endl;

  try {
    server.start();
  } catch (const std::exception &e) {
    std::cerr << "Server error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
