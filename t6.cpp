#include <iostream>
#include <deque>
#include <mutex>
#include <thread>
#include <condition_variable>

std::deque<int> dq;
std::mutex mt;
std::condition_variable cond;

void function1() {
  using namespace std;
  int count = 10;
  while (count > 0) {
    std::unique_lock<mutex> lock1(mt);
    dq.push_front(count);
    lock1.unlock();
    cond.notify_one(); // Notify a waiting thread, if there is one.
    // cond.notify_all(); // Notifies all waiting threads.
    std::this_thread::sleep_for(chrono::seconds(1));;
    --count;
  }
}

void function2() {
  using namespace std;
  int data = 0;
  while (data != 1) {
    std::unique_lock<mutex> lock1(mt);
    cond.wait(lock1); // Thread will wake up once notified.
    // If a thread wakes by itself without notify, then it is a "spurious wake".
    // cond.wait(lock1, [](){ return !dq.empty(); }); // Spurious wake.
    data = dq.back();
    dq.pop_back();
    lock1.unlock();
    cout << "t2 got a value from t1: " << data << endl;
    // if (!dq.empty()) {
    //   data = dq.back();
    //   dq.pop_back();
    //   lock1.unlock();
    //   cout << "t2 got a value from t1: " << data << endl;
    // } else {
    //   lock1.unlock();
    //   std::this_thread::sleep_for(chrono::milliseconds(10));
    // }
  }
}

int main() {
  std::thread t1(function1);
  function2();
  t1.join();
  return 0;
}
