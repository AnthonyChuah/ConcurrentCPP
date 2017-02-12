#include <iostream>
#include <thread>
#include <string>

void function_1() {
  std::cout << "Beauty is only skin-deep\n";
}

class MyFunctor {
public:
  void operator()(std::string msg) {
    // for (int i = 0; i > -100; --i) {
    //   std::cout << "From t1: " << i << "\n";
    // }
    std::cout << "t1 says: " << msg << "\n";
    msg = "Trust is the mother of deceit.";
  }
};

int main() {
  // MyFunctor fct;
  std::string s = "Where there is no trust, there is no love";
  // std::thread t1(MyFunctor(), std::ref(s));
  std::thread t1(MyFunctor(), s);
  std::thread t2 = std::move(t1);
  int nthread_hint = std::thread::hardware_concurrency();
  /*
    You cannot do std::thread t1(MyFunctor());
    Because the compiler mistakes this for a function declaration.
    You cannot pass by reference to a thread. A parameter to a thread is always pass-by-value.
    If you wrap the argument in std::ref() then you can pass by reference.
    But generally, you should not pass by reference because memory sharing is dangerous
    when multithreading.
    Use std::move instead.
  */
  std::cout << std::this_thread::get_id() << "\n" << "numthreads: " << nthread_hint << "\n";
  std::cout << t1.get_id() << "\n";
  std::cout << t2.get_id() << "\n";
  t2.join();
  try {
    // for (int i = 0; i < 100; ++i) {
    //   std::cout << "From main: " << i << "\n";
    // }
    std::cout << "From main: " << s << "\n";
  } catch (...) {
    t1.join();
    throw;
  }
  // t1.join();
  return 0;
}
