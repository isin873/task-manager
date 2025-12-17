
#include "launcher.h"
#include "command.h"
#include "app.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> // for std::replace

// --- helpers for parsing add/delete arguments ---

// Parse: "Title" <duration(double)> <days_left(int)>
static bool parseAddArgs(std::istringstream& iss,
                         std::string& title,
                         double& duration,
                         int& days_left)
{
    iss >> std::ws;
    if (iss.peek() == '"') {
        iss.get(); // consume opening quote
        std::getline(iss, title, '"');
    } else {
        iss >> title;
    }

    // Read duration (double) and days_left (int)
    iss >> duration >> days_left;
    return !title.empty() && iss.good();
}

// REMOVE the int version entirely
// static bool parseAddArgs(std::istringstream& iss, std::string& title, int& duration, int& days_left) { ... }

static bool parseDeleteArgs(std::istringstream& iss, std::string& title) {
    iss >> std::ws;
    if (iss.peek() == '"') {
        iss.get();
        std::getline(iss, title, '"');
        return !title.empty();
    } else {
        iss >> title;
        return !title.empty();
    }
}

// --- core executor ---

bool ExecuteCommandLine(const std::string& raw, App& app) {
    // Optional: be forgiving with commas: turn commas into spaces
    std::string line = raw;
    std::replace(line.begin(), line.end(), ',', ' ');

    const Command& cmd = Command::Find(line);
    if (cmd == Command::INVALID) {
        std::cout << "Unknown command. Type HELP.\n";
        return true;
    }

    std::istringstream iss(line);
    std::string cmdToken;
    iss >> cmdToken; // consume command token

    if (cmd == Command::HELP) {
        std::cout << Command::GetHelp();
        return true;
    }

    if (cmd == Command::EXIT) {
        return false; // signal to exit
    }

    if (cmd == Command::ADD_TASK) {
        std::string title;
        double duration = 0.0;    // <-- double, not int
        int days_left = 0;

        if (!parseAddArgs(iss, title, duration, days_left)) {
            std::cout << "Usage: ADD_TASK \"Title With Spaces\" <duration> <days_left>\n";
            return true;
        }
        app.AddTask(title, duration, days_left);  // <-- duration is double
        return true;
    }

    if (cmd == Command::NEW_DAY) {
        app.NewDay();
        return true;
    }

    if (cmd == Command::SHOW_PRIORITY) {
        app.ShowPriority();
        return true;
    }

    if (cmd == Command::SHOW_TASKS) {
        // If you have App::ShowAll(), call it; else reuse ShowPriority
        app.ShowPriority();
        return true;
    }

    if (cmd == Command::DELETE_TASK) {
        std::string title;
        if (!parseDeleteArgs(iss, title)) {
            std::cout << "Usage: DELETE_TASK \"Title\"\n";
            return true;
        }
        // app.DeleteTask(title);
        std::cout << "DELETE_TASK not yet implemented in App.\n";
        return true;
    }

    std::cout << "Unhandled command. Type HELP.\n";
    return true;
}

// --- interactive and file-run ---

void RunInteractive(App& app) {
    std::cout << "Task Manager CLI\nType HELP for commands. Type EXIT to quit.\n";
    for (std::string line; std::cout << "> " && std::getline(std::cin, line); ) {
        if (!ExecuteCommandLine(line, app)) break;
    }
}


int RunFile(App& app, const std::string& path) {
    std::ifstream fin(path);  // construct with path
    if (!fin) {
        std::cerr << "Failed to open command file: " << path << "\n";
        return 1;
    }
    for (std::string line; std::getline(fin, line); ) {
        if (!ExecuteCommandLine(line, app)) {
            break;  // EXIT command will return false
        }
    }
    return 0;
}
