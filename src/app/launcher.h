
#ifndef LAUNCHER_H
#define LAUNCHER_H
#pragma once
#include <string>
class App;
int RunFile(App& app, const std::string& path);
void RunInteractive(App& app);
bool ExecuteCommandLine(const std::string& line, App& app);

#endif