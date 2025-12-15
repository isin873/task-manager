#ifndef APP_H
#define APP_H
#include <string>
#include "task.h"
#include <iostream>
#include <vector>

class App {
 public:
  std::vector<Task *> task_;
  int array_size_;
  App();

  string MakeLower(string);

  void AddTask(string title, int duration, int days_left);
  void NewDay();
  void ShowTasks();
  void ChangeTime(int time);
  void ChangeTitle(string title);
  void CompleteTask(string title);
  void ResetList();
};

#endif  // APP_H