#include <thread>
#include <iostream>
#include <mutex>

class DeadlockDemo {
  std::mutex mt1;
  std::mutex mt2;
public:
  void proc1(int num) {
    std::unique_lock<std::mutex> lock1(mt1, std::defer_lock);
    std::unique_lock<std::mutex> lock2(mt2, std::defer_lock);
    std::lock(lock1, lock2);
    std::cout << "Proc1 with int argument: " << num << ".\n";
    lock1.unlock(); // Notice how you can do fine-grained manual locking and unlocking.
    // NON-CRITICAL-SECTION.
    lock1.lock(); // unique_lock basically allows more control over your locks.
    // You're not entirely at the mercy of RAII in unlocking, unlike lock_guard.
    // But generally in most use-cases this isn't a concern. You can use scope brackets.
    // You can even move ownership of the lock1 to another new lock.
    std::unique_lock<std::mutex> lock3 = std::move(lock1);
    // Now lock1 no longer identifies anything. lock_guard cannot be moved, unlike this.
  }
  void proc2(int num) {
    std::unique_lock<std::mutex> lock1(mt1, std::defer_lock);
    std::unique_lock<std::mutex> lock2(mt2, std::defer_lock);
    std::lock(lock1, lock2);
    // std::lock(mt1, mt2);
    // std::lock_guard<std::mutex> lock1(mt1, std::adopt_lock);
    // std::lock_guard<std::mutex> lock2(mt2, std::adopt_lock);
    std::cout << "Proc2 with int argument: " << num << ".\n";
  }
};

int main() {
  DeadlockDemo demo;
  auto lambda = [](DeadlockDemo& d) {
    for (int i = 0; i > -10000; --i)
      d.proc1(i);
  };
  std::thread t1(lambda, std::ref(demo));
  for (int i = 0; i < 10000; ++i)
    demo.proc2(i);
  t1.join();
  return 0;
}
