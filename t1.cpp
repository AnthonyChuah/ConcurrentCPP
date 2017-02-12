#include <iostream>
#include <thread>

void function_1() {
  std::cout << "Beauty is only skin-deep\n";
}

int main() {
  std::thread t1(function_1);
  t1.join(); // main thread will wait for t1 to finish.
  // t1.detach(); // t1 will act freely on its own -- daemon process.
  if (t1.joinable()) {
    std::cout << "t1 was joinable.\n";
    t1.join();
  } else {
    std::cout << "t1 was not joinable!\n";
  }
  return 0;
}
