#include "TestQueue.h"
#include <thread>
#include <iostream>
#include <mutex>

void thread1(TestQueue& _tq, int _reps) {
  for (int i = 0; i < _reps; ++i) {
    std::this_thread::sleep_for(chrono::milliseconds(5));
    _tq.insertInt(i);
  }
}

int main() {
  int reps = 100;
  TestQueue tq(128);
  std::thread t1(thread1, std::ref(tq), reps);
  for (int i = 0; i < reps; ++i) {
    std::this_thread::sleep_for(chrono::milliseconds(5));
    int received = tq.extractInt();
  }
  t1.join();
  return 0;
}
