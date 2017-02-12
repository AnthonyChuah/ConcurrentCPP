#include <thread>
#include <iostream>
#include <mutex>

class DeadlockDemo {
  std::mutex mt1;
  std::mutex mt2;
public:
  void proc1(int num) {
    // std::lock_guard<std::mutex> lock1(mt1);
    // std::cout << "Proc1 acquired mutex1.\n";
    // std::this_thread::sleep_for(std::chrono::milliseconds(10));
    // std::lock_guard<std::mutex> lock2(mt2);
    // std::cout << "Proc1 acquired mutex2.\n";
    // std::this_thread::sleep_for(std::chrono::milliseconds(10));
    // The version above causes deadlock. Use std::lock for deadlock avoidance.
    std::lock(mt1, mt2); // Simultaneously locks both, while avoiding deadlocks.
    std::lock_guard<std::mutex> lock1(mt1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mt2, std::adopt_lock);
    // http://stackoverflow.com/questions/27089434/whats-the-difference-between-first-locking-and-creating-a-lock-guardadopt-lock
    // This acquires the lock on the two mutexes, and then creates the lockguards to make
    // sure they are properly released (RAII-style).
    // The other way is to use unique_lock, defer_lock, and lock AFTER, like this:
    // std::unique_lock<std::mutex> lock1(mt1, std::defer_lock);
    // std::unique_lock<std::mutex> lock2(mt2, std::defer_lock);
    // std::lock(lock1, lock2);
    // std::lock_guard tends to be slightly faster/space-efficient. Most of the time, use it.
    std::cout << "Proc1 with int argument: " << num << ".\n";
  }
  void proc2(int num) {
    // std::lock_guard<std::mutex> lock2(mt2);
    // std::cout << "Proc2 acquired mutex2.\n";
    // std::this_thread::sleep_for(std::chrono::milliseconds(10));
    // std::lock_guard<std::mutex> lock1(mt1);
    // std::cout << "Proc2 acquired mutex1.\n";
    // std::this_thread::sleep_for(std::chrono::milliseconds(10));
    // The version above causes deadlock. Use std::lock for deadlock avoidance.
    std::lock(mt1, mt2);
    std::lock_guard<std::mutex> lock1(mt1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mt2, std::adopt_lock);    
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

/*
Avoiding deadlocks:
1. Prefer locking single mutex at a time.
2. Avoid locking a mutex and then calling a user-provided function.
3. Use std::lock() to lock more than one mutex. It has deadlock avoidance algorithms.
4. Lock the mutexes in the same order for all threads.
5. Provide a hierarchy of mutexes so that when a thread is locking a lower-level mutex,
   it is not allowed to lock a higher-level mutex.

Locking Granularity:
* Fine-grained lock protects small amount of data.
* Coarse-grained lock protects big amount of data.
You do not want to use overly-coarse grained locks.
*/
