#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <cstdlib>

std::mutex mt;

void shared_print(std::string msg, int id) {
  std::lock_guard<std::mutex> guard(mt); // RAII
  // mt.lock();
  std::cout << msg << id << std::endl;
  // mt.unlock();
  // Do not use lock() and unlock(): because if critical section throws an exception,
  // then the mutex will forever be locked!
  // Use lock_guard, see above. This is RAII: whenever it goes out of scope it will always
  // unlock.
  // In fact this is still not good enough: in order to protect cout completely, you need to
  // bind a mutex to the global cout.
  // See t3a.cpp.
}

void function_1() {
  for (int i = 0; i > -100; --i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    shared_print(std::string("From t1: "), i);
  }
}

int main() {
  std::thread t1(function_1);
  for (int i = 0; i < 100; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    shared_print(std::string("From main: "), i);
  }
  t1.join();
  return 0;
}
