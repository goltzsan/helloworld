#include "../World.hpp"

#include <iostream>

int World::sayHello() {
  std::cout << "Hello World!" << std::endl;
  return 0;
}

bool World::sayThis(const std::string msg) {
  if (msg.empty()) {
    return false;
  }

  std::cout << msg << std::endl;
  return true;
}
