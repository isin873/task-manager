#include "app.h"

#include <iostream>
#include <string>
#include "task.h"
#include <cctype>
#include <algorithm>
using namespace std;

App::App(){
    array_size_ = 0;
    work_hours_ = 8.0;
}

string App::MakeLower(string word){
    string lower = word;
    for (char& c : lower){
        if (c >= 'A' && c <= 'Z'){
            c = c +32;
        }
    }
    return lower;
}

void App::AddTask(string title, double duration, int days_left){
    //if there is nothing in the list 
    Task* to_add = nullptr;
    title = MakeLower(title);
    if (array_size_ == 0){
        to_add = new Task(title, duration, days_left);
    } else {
        //if there is something in the list
        for (Task* current : task_){
            if (title == MakeLower(current->title_)){
                cout << "Task with this title already exists: task not created" << endl;
                return;
            }
        }
        //if it doesn't already exist
        to_add = new Task(title, duration, days_left);
    }
    if (to_add != nullptr){
        to_add->ChangePriority(work_hours_); //assumes 8 hours a day work
        //creates a ratio of how long needed in hours / how long left in hours (assumes start of day)
        task_.push_back(to_add);
        array_size_++;
        string days = "days";
        if (abs(days_left) == 1){
            days = "day";
        }

        if (days_left < 0){
            cout << title << " created - overdue by " << days_left*-1 << " " << days << endl;
            return;
        }
        cout << title << " created - due in " << days_left << " " << days << endl;
    }
}

void App::NewDay(){
    if (array_size_ == 0){
        cout << "You have no tasks - have a great day!" << endl;
        return;
    } else {
        for (Task* current : task_){
            //updates the days left to do a task
            current->days_left_ = current->days_left_ - 1;
        }
        //once updated send urgent alerts

        //first due tasks
        int due_soon = 0;
        std::vector <Task*> due_today;
        for (Task* current : task_){
            if (current->days_left_ == 0){
                due_today.push_back(current);
                due_soon++;
            }
        }

        //for overdue tasks
        int overdue = 0;
        std::vector <Task*> overdue_list;
        for (Task* current : task_){
            if (current->days_left_ < 0){
                overdue++;
                overdue_list.push_back(current);
            }
        }
        //sorting overdue list in most recently overdue at top
        for (int i = 1; i<overdue; i++){
            Task* key = overdue_list[i];
            int j = i;
            while (j > 0 && overdue_list[j-1]->days_left_ < key->days_left_){
                overdue_list[j] = overdue_list[j - 1];
                j--;
            }
            overdue_list[j] = key;
        }
        //printing 
        if (due_soon == 0){
            cout << "You have no tasks due today!" << endl;
        } else {
            cout << "You have " << due_soon << " tasks due today:" << endl;
            for (Task* task : due_today){
                cout << task->title_ << endl;
            }
        }

        if (overdue == 0){
            cout << "You have no overdue tasks!"<< endl;
        } else {
            cout << "You have " << overdue << " overdue tasks." << endl;
            for (Task* current : overdue_list){
                  string days = "days";
                  if (abs(current->days_left_) == 1){
                    days = "day";
                  }
        // cout << current->title_<< " is overdue by " << (current->days_left_)*-1 << " " << days << endl; //make it cleaner
            }
        }
    } 
    //update priorities based on new dates
    for (Task* current : task_){
        current->ChangePriority(work_hours_);
    }
    
    return;
}


void App::ShowPriority(){
    if (task_.size() == 0){
        cout << "Task list is empty! Relax ;)" << endl;
        return;
    }

    std::vector<Task*> sorted = task_;
        for (int i = 1; i<array_size_; i++){
            Task* key = sorted[i];
            int j = i;
            while (j > 0 && sorted[j-1]->days_left_ > key->days_left_){
                sorted[j] = sorted[j - 1];
                j--;
            }
            sorted[j] = key;
        }

        int i = 1;
        cout << "PRIORITY LIST: You have " << array_size_ << " tasks:" << endl;
        for (Task* current : sorted){
            string days = " days.";
            if (abs(current->days_left_) == 1){
                days = " day.";
            }
            if (current->days_left_ < 0){
                cout << i << ": " << current->title_ << ". Overdue by " << current->days_left_*-1 << days << endl;
            } else {
            cout << i << ": " << current->title_ << ". Due in " << current->days_left_ << days << endl;
            }
            i++;
        }
 }

 void App::ChangeTime(string title, double time){
    //find task
    Task* to_change = nullptr;
    title = MakeLower(title);
    for (Task* current : task_){
        if (title == current->title_){
            to_change = current;
        }
    }
    if (to_change == nullptr){
        cout << "INVALID: There is no task called " << title << endl;
        return;
    }
    to_change->task_time_ = time;
    to_change->ChangePriority(work_hours_);
    cout << title << " updated: " << time << " hours needed to complete." << endl;
 }

  void App::ChangeDays(string title, int days){
    Task* to_change = nullptr;
    title = MakeLower(title);
    for (Task* current : task_){
        if (title == current->title_){
            to_change = current;
        }
    }
    if (to_change == nullptr){
        cout << "IMVALID: There is no task called " << title << endl;
        return;
    }
    //if task there
    to_change->days_left_ = days;
    to_change->ChangePriority(work_hours_);
    string plural = " days";
    if (abs(days) == 1){
        plural = " day";
    }
    if (days<0){
        cout << title << " updated: " << days*-1 << plural << " overdue." << endl;
        return;
    }
    cout << title << " updated: " << days << plural << " left to complete." << endl;
    return;
  }

  void App::ChangeTitle(string title, string new_title){
    title = MakeLower(title);
    new_title = MakeLower(new_title);
    Task* to_change = nullptr;
    Task* new_name = nullptr;
    for (Task* current : task_){
        if (title == current->title_){
            to_change = current;
        }
        if (new_title == current->title_){
            new_name = current;
        }
    }
    if (new_name != nullptr){
        cout << "INVALID: There is already a task called " << new_title << endl;
        return;
    }
    if (to_change == nullptr){
        cout << "INVALID: There is no current task called " << title << endl;
        return;
    }
    to_change->title_ = new_title;
    cout << "Task " << title << " has changed it's name to " << new_title << endl;
    return;
  }


void App::CompleteTask(std::string title) {
    title = MakeLower(title);  // assuming titles are stored lowercase

    int matchIndex = -1;
    Task* to_complete = nullptr;

    // Find the first matching task and its index
    for (int idx = 0; idx < static_cast<int>(task_.size()); ++idx) {
        Task* current = task_[idx];
        if (title == current->title_) {
            matchIndex = idx;
            to_complete = current;
            break; // stop at the first match
        }
    }

    if (matchIndex == -1) {
        std::cout << "There is no task called " << title << std::endl;
        return;
    }

    // Delete the heap allocation and erase the pointer from the vector
    delete to_complete;
    task_.erase(task_.begin() + matchIndex);
    --array_size_;

    std::cout << title << " completed! You have " << array_size_
              << " tasks remaining." << std::endl;
}

  void App::ResetList(){
    array_size_ = 0;
    for (Task* current : task_){
        delete current;
    }
    task_.clear();
    cout << "List reset: 0 tasks pending" << endl;
    return;
  }