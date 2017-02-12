#include <iostream>
#include <future>
#include <thread>

int factorial(std::shared_future<int> f) {
  int result = 1;
  int N = f.get(); // Gets the promised value in f.
  for (int i = N; i > 1; --i) {
    result *= i;
  }
  std::cout << "Result is: " << result << "\n";
  return result;
}

int main() {
  using namespace std;
  std::promise<int> p;
  std::future<int> f = p.get_future();
  std::shared_future<int> sf = f.share();
  std::future<int> f1 = std::async(std::launch::async, factorial, sf);
  std::future<int> f2 = std::async(std::launch::async, factorial, sf);
  std::future<int> f3 = std::async(std::launch::async, factorial, sf);
  p.set_value(4);
  return 0;
}

/*
Shared future is useful in a broadcast communication model.
If you do not set_value on a promise, you break promise. Throws exception broken_promise.
std::async is a way to launch a thread, just like std::thread.
Both take a callable object (Functor) and can take input variables.
*/
