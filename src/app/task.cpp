#include <string>
#include "task.h"

int Task::global_id = 1;

Task::Task(string title, double task_time, int days_left) : task_id_(global_id){
    task_time_ = task_time;
    title_ = title;
    days_left_ = days_left;
    global_id++;
    priority_ = 0;

}

void Task::ChangePriority(double work_hours){
    priority_ = task_time_/double((days_left_)*work_hours);
}