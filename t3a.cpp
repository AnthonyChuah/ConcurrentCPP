#include <thread>
#include <string>
#include <mutex>
#include <fstream>
using namespace std;

class LogFile {
  std::mutex m_mutex;
  ofstream f;
public:
  LogFile() {
    f.open("log.txt");
  } // Need destructor to close file.
  ~LogFile() {
    f.close();
  }
  void shared_print(string id, int value) {
    std::lock_guard<mutex> locker(m_mutex);
    f << "From " << id << ": " << value << endl;
  }
  // Never return f to the outside world. For example never do this:
  ofstream& getStream() { return f; }
  // If you do this, user has opportunity to access f without locking the mutex.
  // Never pass f as an argument to user-provided function. Like this beblow:
  void processf(void fun(ofstream&)) {
    fun(f);
  }
};

// class stack {
//   int* _data;
//   std::mutex _mt;
// public:
//   int& pop();
//   int& top();
// };

void function_1(LogFile& log) {
  for (int i = 0; i > -100; --i)
    log.shared_print(string("From t1: "), i);
}

// void function_1(stack& st) {
//   int v = st.top();
//   st.pop();
//   std::cout << v << "\n";
// }

int main() {
  LogFile log;
  std::thread t1(function_1, std::ref(log));
  for (int i = 0; i < 100; ++i) {
    log.shared_print(string("From main: "), i);
  }
  t1.join();
}

/*
Avoiding Data Race:
1. Use mutex to sync.
2. Never leak a handle of data to outsde.
3. Design interface appropriately.
*/
