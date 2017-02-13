#include "TestQueue.h"
#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>

int main() {
  int reps = 100;
  TestQueue tq(128);
  auto lambda = [](TestQueue& _tq, int _reps) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    for (int i = 0; i < _reps; ++i) {
      _tq.insertInt(i);
    }
  };
  std::thread t1(lambda, std::ref(tq), reps);
  int received[100];
  for (int i = 0; i < reps; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    received[i] = tq.extractInt();
  }
  t1.join();
  for (int i = 0; i < reps; ++i) {
    std::cout << received[i] << " ";
  }
  return 0;
}
