#include "TestQueue.h"
#include <iostream>
#include <chrono>
#include <thread>

TestQueue::TestQueue(int _size) {
  data.reserve(_size);
}

void TestQueue::insertInt(int _val) {
  std::unique_lock<std::mutex> locker(mutex1);
  data.emplace_back(_val);
  std::cout << "Inserted int into queue: " << _val << "\n";
  locker.unlock();
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  cond.notify_one();
}

int TestQueue::extractInt() {
  std::unique_lock<std::mutex> locker(mutex1);
  while (data.empty()) {
    std::cout << "Empty queue, waiting.\n";
    cond.wait(locker);
  }
  int result = data.back();
  data.pop_back();
  std::cout << "Extracted int from queue: " << result << "\n";
  return result;
}
