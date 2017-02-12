#include <thread>

class Runnable {
public:
  void f(int x, char c) {}
  long g(double x) { return 0; }
  int operator()(int N) { return 0; }
};

void foo(int x) {}

int main() {
  Runnable r;
  std::thread t1(r, 6); // Copy of Runnable in a different thread
  std::thread t2(std::ref(r), 6); // Runnable itself, by reference, in a different thread
  std::thread t8(std::move(r), 6); // Runnable NO LONGER USABLE in main thread
  std::thread t3(Runnable(), 6); // A temporary Runnable
  std::thread t4([](int x){return x*x;}, 6); // Lambda function called in different thread
  std::thread t5(foo, 7); // Function foo called in different thread
  std::thread t6(&Runnable::f, r, 8, 'w'); // Copy of Runnable's f in different thread
  std::thread t7(&Runnable::f, &r, 8, 'w'); // Runnable's f using 8 and 'w' args in diff thread
  return 0;
}

/*
Thread-making functions that take callable functors.
std::bind
std::call_once
*/
