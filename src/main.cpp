
#include <iostream>
#include "app/app.h"
#include "app/task.h"
#include <string>

int main(){
    App app;
    app.AddTask("buy alexa", 10, 10);
    app.AddTask("buy groceries", 80, 0);
    app.AddTask("walk dog", 45, -1);
    app.AddTask("Buy Alexa", 10, 10);

    app.NewDay();

    app.AddTask("ok", 10 , 0);
    app.AddTask("no", 10, -20);

    app.NewDay();
}