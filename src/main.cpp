
#include <iostream>
#include "app/app.h"
#include "app/task.h"
#include <string>
#include "app/launcher.h"
#include "app/command.h"


int main(int argc, char* argv[]) {
    App app;
    if (argc > 1) {
        return RunFile(app, argv[1]);   // run commands from a file
    }
    RunInteractive(app);                // interactive REPL
    return 0;

};