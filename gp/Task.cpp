#include "Task.h"

Task::Task(char* _startPtr, int _numPhotos, int _size) :
  dataPtr(_startPtr), numPhotos(_numPhotos), photoSize(_size) {}

Task::Task(char* _startPtr, int _numPhotos) :
  dataPtr(_startPtr), numPhotos(_numPhotos) {}

char* Task::getStart(int photoNum) {
  return (dataPtr + photoNum*Task::photoSize);
}

int Task::getLengthOfPhoto() {
  return Task::photoSize;
}
