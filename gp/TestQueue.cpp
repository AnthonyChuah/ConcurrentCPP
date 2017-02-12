#include "TestQueue.h"
#include <iostream>

TestQueue::TestQueue(int _size) {
  data.reserve(_size);
}

void TestQueue::insertInt(int _val) {
  std::unique_lock<std::mutex> locker(mutex1);
  data.emplace_back(_val);
  std::cout << "Inserted int into queue: " << _val << "\n";
  locker.unlock();
  cond.notify_one();
}

int TestQueue::extractInt() {
  std::unique_lock<std::mutex> locker(mutex1);
  while (data.empty()) {
    cond.wait(locker);
  }
  int result = data.back();
  data.pop_back();
  std::cout << "Extracted int from queue: " << result << "\n";
  return result;
}
