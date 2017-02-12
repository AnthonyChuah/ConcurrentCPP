#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int factorial(int N) {
  std::this_thread::sleep_for(chrono::seconds(0.1*N));;
}

int main() {
  // Thread
  std::thread t1(factorial, 6);
  std::this_thread::sleep_for(chrono::milliseconds(3));
  chrono::steady_clock::time_point tp = chrono::steady_clock::now() + chrono::microseconds(4);
  std::this_thread::sleep_until(tp); // Sleeps until time point
  
  // Mutex
  std::mutex mt;
  // Locking mutexes through lock_guard
  {
    std::lock_guard<mutex> locker(mt);
    // Critical section code
  }
  // Unique_lock more flexible version, can lock and unlock multiple times.
  {
    std::unique_lock<mutex> ulocker(mt);
    // ulocker.try_lock(); // Try to lock now.
    ulocker.try_lock_for(chrono::milliseconds(500)); // Try to lock for 500 ms
    ulocker.try_lock_until(tp); // Try to lock until a certain time point
    // Critical section code
  }
  
  
  // Condition variable
  std::condition_variable cond;
  cond.wait_for(chrono::microseconds(2));
  cond.wait_until(tp);

  // Future and promise
  std::promise<int> p;
  std::future<int> f = p.get_future();
  f.get(); // Actually calls the wait() function, so it will wait until you can get
  f.wait(); // Waits for the data to be available
  f.wait_for(chrono::milliseconds(50));
  f.wait_until(tp);
  
  // Async()
  std::future<int> fut = async(factorial, 6);
  // Packaged Task
  std::packaged_task<int(int)> t(factorial);
  std::future<int> fut2 = t.get_future();
  t(6);

  return 0;
}
