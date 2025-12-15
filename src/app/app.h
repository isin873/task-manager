#ifndef APP_H
#define APP_H
#include <string>
#include "task.h"

class App {
 public:
  Task** task_;
  int array_size_;
  App();
  ~App();
};

#endif  // APP_H