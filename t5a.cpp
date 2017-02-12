#include <thread>
#include <iostream>
#include <mutex>
#include <fstream>

class LazyInitialization {
  std::mutex mt1;
  std::once_flag flag;
  std::ofstream f;
public:
  void doThingRequiringOpenFile() {
    // Lazy initialization means that you acquire the resource only upon the first time
    // you actually ned it. That is, you do NOT pre-acquire the resource to ready yourself for
    // using the resource later. If your resource requires a mutex lock, this gets tricky.
    // Example:
    // {
    //   std::unique_lock<std::mutex> lock1(mt1);
    //   if (!f.is_open())
    // 	f.open("log.txt");
    // }
    std::call_once(flag, [&](){f.open("log.txt");});
    std::unique_lock<std::mutex> lock1(mt1, std::defer_lock);
    // CRITICAL SECTION CODE.
  }
};

int main() {
  LazyInitialization lazy;
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
