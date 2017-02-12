#ifndef TASKQUEUE_H

#include <mutex>
#include <condition_variable>
#include <vector>
#include "task.h"

class TaskQueue {
  std::mutex mutex1;
  std::condition_variable cond;
  std::vector<Task*> data;
  TaskQueue(); // Ensure that constructor is never called with no args
 public:
  TaskQueue(int _size);
  void insertTask(Task* _task);
  Task* extractTask();
};

#endif
