#include "TaskQueue.h"

TaskQueue::TaskQueue(int _size) {
  data.reserve(_size); // Reserves vector capacity
}

void TaskQueue::insertTask(Task* _task) {
  std::unique_lock<std::mutex> locker(mutex1);
  data.emplace_back(_task);
  locker.unlock();
  cond.notify_one();
}

Task* TaskQueue::extractTask() {
  std::unique_lock<std::mutex> locker(mutex1); // Locks the mutex.
  while (data.empty()) {
    cond.wait(locker);
  }
  Task* result = data.back();
  data.pop_back();
  return result;
}
