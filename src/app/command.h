
#pragma once
#include <string>
#include <vector>
#include <initializer_list>

/*
  Command class in the same style as your example:
  - Static const Command instances for supported commands
  - A registry via std::initializer_list<Command> commands
  - Find(), GetHelp(), IsValidCommand()
*/

class Command {
public:
    // ---- Task Manager commands (adjust as needed) ----
    static const Command ADD_TASK;         // add a task: <TITLE> <DURATION> <DAYS_LEFT>
    static const Command NEW_DAY;          // decrement days for all tasks and report
    static const Command SHOW_PRIORITY;    // show tasks ordered by urgency
    static const Command SHOW_TASKS;       // list all tasks (optional if you implement App::ShowAll)
    static const Command COMPLETE_TASK;      // delete by <TITLE> (optional if you implement App::DeleteTask)
    static const Command HELP;             // print usage
    static const Command EXIT;             // exit application
    static const Command INVALID;          // sentinel

    // Registry    // Registry of all valid commands
    static std::initializer_list<Command> commands;

    // Constructors (matching your style)
    Command(const std::string& name, int num_args, const std::string& message);
    Command(const std::string& name, int num_args, const std::string& message,
            const std::vector<std::string>& option_prompts);

    // Accessors
    std::string GetName() const;
    bool HasArguments() const;
    int GetNumArgs() const;
    bool HasOptions() const;
    int GetNumOptions() const;
    std::string GetMessage() const;
    std::string GetOptionPrompt(int index) const;

    // Helpers
    static std::string GetHelp();
    static bool IsValidCommand(const std::string& cmd_input);
    static const Command& Find(const std::string& cmd_input);

    // Equality (same semantics as your sample)
    bool operator==(const Command& other) const;
    bool operator!=(const Command& other) const;

private:
    std::string name_;
    int num_args_ = 0;
    std::string message_;
    std::vector<std::string> option_prompts_;
    };