#include "app.h"

#include <iostream>
#include <string>
#include "task.h"
#include <cctype>
#include <algorithm>
using namespace std;

App::App(){
    array_size_ = 0;
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

void App::AddTask(string title, int duration, int days_left){
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
            cout << "You have " << overdue << " overdue tasks:" << endl;
            for (Task* current : overdue_list){
                  string days = "days";
                  if (abs(current->days_left_) == 1){
                    days = "day";
                  }
        cout << current->title_<< " is overdue by " << (current->days_left_)*-1 << " " << days << endl;
            }
        }
    } return;
}