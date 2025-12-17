
#include "launcher.h"
#include "command.h"
#include "app.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> // std::replace

// ---- helpers ----

// Parse: "Title" <duration(double)> <days_left(int)>, supports commas: 0.8, 0
static bool parseAddLineRobust(const std::string& line,
                               std::string& title,
                               double& duration,
                               int& days_left)
{
    // Replace commas with spaces
    std::string cleaned = line;
    std::replace(cleaned.begin(), cleaned.end(), ',', ' ');

    // Slice off the command token
    std::size_t firstSpace = cleaned.find(' ');
    if (firstSpace == std::string::npos) return false;
    std::string args = cleaned.substr(firstSpace + 1);

    // Quoted title?
    std::size_t q1 = args.find('"');
    if (q1 != std::string::npos) {
        std::size_t q2 = args.find('"', q1 + 1);
        if (q2 == std::string::npos) return false;
        title = args.substr(q1 + 1, q2 - (q1 + 1));

        // After closing quote, parse duration and days_left
        std::string rest = args.substr(q2 + 1);
        std::istringstream restIss(rest);
        std::string durStr, daysStr;
        if (!(restIss >> durStr >> daysStr)) return false;
        try {
            duration = std::stod(durStr);
            days_left = std::stoi(daysStr);
        } catch (...) { return false; }
    } else {
        // Unquoted: first token is title, then duration, days_left
        std::istringstream iss(args);
        std::string durStr, daysStr;
        if (!(iss >> title >> durStr >> daysStr)) return false;
        try {
            duration = std::stod(durStr);
            days_left = std::stoi(daysStr);
        } catch (...) { return false; }
    }
    return !title.empty();
}

// Parse a single title (quoted or token)
static bool parseTitleOnly(std::istringstream& iss, std::string& title) {
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

// ---- core executor ----
bool ExecuteCommandLine(const std::string& raw, App& app) {
    // Normalize commas before command resolution
    std::string line = raw;
    std::replace(line.begin(), line.end(), ',', ' ');

    const Command& cmd = Command::Find(line);
    if (cmd == Command::INVALID) {
        std::cout << "Unknown command. Type HELP.\n";
        return true;
    }

    // Build a stream for branches that need token parsing
    std::istringstream iss(line);
    std::string cmdToken;
    iss >> cmdToken; // consume the command word

    if (cmd == Command::HELP) {
        std::cout << Command::GetHelp();
        return true;
    }

    if (cmd == Command::EXIT) {
        return false;
    }

    if (cmd == Command::ADD_TASK) {
        std::string title; double duration = 0.0; int days_left = 0;
        if (!parseAddLineRobust(line, title, duration, days_left)) {
            std::cout << "Usage: ADD_TASK \"Title With Spaces\" <duration> <days_left>\n";
            return true;
        }
        app.AddTask(title, duration, days_left); // duration is double
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
        // If you have App::ShowAll(), use it; otherwise reuse ShowPriority
        app.ShowPriority();
        return true;
    }

    if (cmd == Command::COMPLETE_TASK) {
        std::string title;
        if (!parseTitleOnly(iss, title)) {
            std::cout << "Usage: COMPLETE_TASK \"Title\"\n";
            return true;
        }
        // If CompleteTask returns bool, you can print feedback:
        // if (!app.CompleteTask(title)) std::cout << "Task not found: " << title << "\n";
        app.CompleteTask(title);
        return true;
    }

    std::cout << "Unhandled command. Type HELP.\n";
    return true;
}

// ---- interactive and file-run ----

void RunInteractive(App& app) {
    std::cout << "Task Manager CLI\nType HELP for commands. Type EXIT to quit.\n";
    for (std::string line; std::cout << "> " && std::getline(std::cin, line); ) {
        if (!ExecuteCommandLine(line, app)) break;
    }
}

int RunFile(App& app, const std::string& path) {
    std::ifstream fin(path);
    if (!fin) {
        std::cerr << "Failed to open command file: " << path << "\n";
        return 1;
    }
    for (std::string line; std::getline(fin, line); ) {
        if (!ExecuteCommandLine(line, app)) break; // EXIT stops
    }
    return 0;
}

