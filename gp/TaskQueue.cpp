#include "TaskQueue.h"

TaskQueue::TaskQueue(int _size) {
  data.reserve(_size); // Reserves vector capacity
}

void TaskQueue::insertTask(Task* _task) {
  std::lock(mutex1);
  std::lock_guard<std::mutex> locker(mutex1, std::adopt_lock);
  data.push_back(_task);
}

Task* TaskQueue::extractTask() {
  Task* result = data.back();
  std::lock(mutex1);
  std::lock_guard<std::mutex> locker(mutex1, std::adopt_lock);
  data.pop_back();
}
