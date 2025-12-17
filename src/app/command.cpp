
#include "command.h"
#include <string>
#include <cctype>
#include <algorithm>

// -----------------------------------------------------------------------------
// Local helpers (self-contained, no external utils required)
// -----------------------------------------------------------------------------
namespace {
    // Returns the first token (space-delimited) from the input line.
    std::string GetFirstWord(const std::string& s) {
        std::size_t start = s.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) return "";
        std::size_t end = s.find_first_of(" \t\r\n", start);
        return (end == std::string::npos) ? s.substr(start) : s.substr(start, end - start);
    }

    // Converts input to UPPERCASE_WITH_UNDERSCORES (spaces, tabs, dashes -> underscore).
    std::string GetUppercaseUnderscore(const std::string& s) {
        std::string out;
        out.reserve(s.size());
        for (unsigned char uc : s) {
            char c = static_cast<char>(uc);
            if (c == ' ' || c == '-' || c == '\t') {
                out.push_back('_');
            } else {
                out.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
            }
        }
        return out;
    }
}

// -----------------------------------------------------------------------------
// Static Command definitions (same pattern as your example)
// -----------------------------------------------------------------------------

const Command Command::ADD_TASK(
    "ADD_TASK", 3,
    "Add a task with <TITLE>, <DURATION> and <DAYS_LEFT>.",
    {"Title (quoted if spaces)", "Duration (minutes)", "Days left (integer)"}
);

const Command Command::NEW_DAY(
    "NEW_DAY", 0,
    "Advance one day: decrement days_left and report due/overdue."
);

const Command Command::SHOW_PRIORITY(
    "SHOW_PRIORITY", 0,
    "Show tasks ordered by urgency (e.g., by days_left or a priority score)."
);

const Command Command::SHOW_TASKS(
    "SHOW_TASKS", 0,
    "Display all tasks with details."
);

const Command Command::DELETE_TASK(
    "DELETE_TASK", 1,
    "Delete a task by <TITLE>.",
    {"Title (quoted if spaces)"}
);

const Command Command::HELP("HELP", 0, "Print usage");
const Command Command::EXIT("EXIT", 0, "Exit the application");
const Command Command::INVALID("_____INVALID____", 0, "Placeholder for INVALID Command value");

// Registry (same approach as your sample)
std::initializer_list<Command> Command::commands = {
    Command::ADD_TASK,
    Command::NEW_DAY,
    Command::SHOW_PRIORITY,
    Command::SHOW_TASKS,
    Command::DELETE_TASK,
    Command::HELP,
    Command::EXIT
};

// -----------------------------------------------------------------------------
// Implementations (same style as your sample)
// -----------------------------------------------------------------------------

Command::Command(const std::string& name, int num_args, const std::string& message)
    : name_(name), num_args_(num_args), message_(message) {}

Command::Command(const std::string& name, int num_args, const std::string& message,
                 const std::vector<std::string>& option_prompts)
    : name_(name), num_args_(num_args), message_(message), option_prompts_(option_prompts) {}

std::string Command::GetName() const { return name_; }
bool Command::HasArguments() const { return num_args_ > 0; }
int Command::GetNumArgs() const { return num_args_; }
bool Command::HasOptions() const { return !option_prompts_.empty(); }
int Command::GetNumOptions() const { return static_cast<int>(option_prompts_.size()); }
std::string Command::GetMessage() const { return message_; }

std::string Command::GetOptionPrompt(int index) const {
    return option_prompts_.at(index);
}

bool Command::operator==(const Command& other) const {
    return name_ == other.name_;
}
bool Command::operator!=(const Command& other) const {
    return !(*this == other);
}

std::string Command::GetHelp() {
    std::string help;
    for (const Command& command : commands) {
        const int num_args = command.GetNumArgs();
        const std::string command_name = command.GetName();

        help += command_name + "\t";
        if (command_name.length() < 16) help += "\t";
        if (command_name.length() < 8)  help += "\t";

        help += "[" + std::string(num_args == 0 ? "no" : std::to_string(num_args)) +
                " argument" + (num_args == 1 ? "" : "s") + "]\t";
        help += command.GetMessage() + "\n";
    }
    return help;
}

bool Command::IsValidCommand(const std::string& cmd_input) {
    return Find(cmd_input) != Command::INVALID;
}

const Command& Command::Find(const std::string& cmd_input) {
    std::string cmd = GetFirstWord(cmd_input);
    cmd = GetUppercaseUnderscore(cmd);

    for (const Command& command : commands) {
        if (command.GetName() == cmd) {
            return command;
        }
    }
    return Command::INVALID;
};