#ifndef TASK_H
#define TASK_H
#include <string>
using namespace std;

class Task{
private:
public:
const int task_id_;
double task_time_;
double priority_;
string title_;
static int global_id;
int days_left_;

Task(string title, double task_time, int days_left);

};



#endif