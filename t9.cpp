#include <mutex>
#include <thread>
#include <condition_variable>

/*
Packaged Tasks: You can pass these tasks around to different threads.
*/

int factorial(int N) {
  int result = 1;
  for (int i = N; i > 1; --i)
    result *= i;
  std::cout << "Result is: " << result << std::endl;
  return result;
}

std::deque<std::packaged_task<int()> > tq;
std::mutex mt;
std::condition_variable cond;

void thread1() {
  std::packaged_task<int()> t;
  {
    std::unique_lock<std::mutex> lock1(mt);
    cond.wait(lock1, [](){return !tq.empty();});
    t = std::move(tq.front());
    tq.pop_front();
  }
  t(); // Executes the task from the queue.
}

int main() {
  using namespace std;
  // std::packaged_task<int(int)> t(factorial);
  // Cannot pass additional parameters into the packaged_task.
  // Need to use bind function.
  std::packaged_task<int(int)> t(std::bind(factorial, 6));
  // But it seems you can do all these by just using a function object.
  auto t = std::bind(factorial, 6); // Creates t, a function object.
  // Main advantage of packaged_task is to link a Runnable object to a future.
  std::thread t1(thread1);
  std::packaged_task<int()> t(bind(factorial, 6));
  std::future<int> fut = t.get_future();
  {
    std::lock_guard<std::mutex> lock1(mt);
    tq.push_back(t);
  }
  cout << fut.get();

  t1.join();
  // Do other things...
  t(6); // Execute this in a different context
  int x = t.get_future().get(); // Gives the return value from the factorial function.
  return 0;
}

/*
3 ways to get a future:
promise::get_future()
packaged_task::get_future()
async() returns a future
*/
