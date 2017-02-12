#ifndef TESTQUEUE_H

#include <mutex>
#include <condition_variable>
#include <vector>

class TestQueue {
  std::mutex mutex1;
  std::condition_variable cond;
  std::vector<int> data;
  TestQueue(); // Ensure that default constructor no args never called
 public:
  TestQueue(int _size);
  void insertInt(int _val);
  int extractInt();
};

#endif
