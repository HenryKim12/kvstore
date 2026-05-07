#include "../include/store.h"
#include <iostream>

int main() {
  std::cout << "Initializing store..." << std::endl;
  Store store;
  store.set("x", "1");
  store.set("y", "2");
  store.set("z", "3");

  std::optional<std::string> test = store.get("x");
  if (test.has_value()) {
    std::cout << "X is " << test.value() << std::endl;
  }
  return 0;
}
