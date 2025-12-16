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
  double work_hours_; //defualt is 8 hours

  string MakeLower(string);

  void AddTask(string title, double duration, int days_left);
  void NewDay();
  void ShowPriority();
  void ChangeTime(int time);
  void ChangeDays(int days);
  void ChangeTitle(string title);
  void CompleteTask(string title);
  void ResetList();
};

#endif  // APP_H