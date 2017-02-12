#ifndef TASKQUEUE_H

#include <mutex>
#include <vector>
#include "task.h"

class TaskQueue {
  std::mutex mutex1;
  std::vector<Task*> data;
  TaskQueue(); // Ensure that constructor is never called with no args
 public:
  TaskQueue(int _size);
  void insertTask(Task* _task);
  Task* extractTask();
};

#endif
