#ifndef TASK_H

class Task {
  char* dataPtr;
  int numPhotos;
  static photoSize;
  Task(); // Ensure that constructor is never called with no args
 public:
  Task(char* _startPtr, int _numPhotos, int _size);
  Task(char* _startPtr, int _numPhotos);
  char* getStart(int photoNum);
  int getLengthOfPhoto();
};

#endif
