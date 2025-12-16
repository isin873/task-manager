
#include <iostream>
#include "app/app.h"
#include "app/task.h"
#include <string>

int main(){
    App app;
    app.AddTask("buy alexa", 0.1, 10); //should be very low
    app.AddTask("buy groceries", 1.2, 0); //should be very high
    app.AddTask("walk dog", 0.75, -1); //should be highest as overdue

    app.ShowPriority();

    app.NewDay();

    app.ShowPriority();

    app.NewDay();
 

    app.ShowPriority();

    app.ChangeTitle("buy alexa", "walk dog");
    app.ChangeTitle("buy alexa", "mum christmas");
    app.ChangeTitle("walk cat", "idk");
}