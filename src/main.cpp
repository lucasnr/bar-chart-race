#include <iostream>

#include "./util/message.h"

int main() {
  message::info("Goodbye World");
  std::cout << "Wait, you were waiting for " << message::inline_danger("Hello World") << "?";

  return 0;
}
