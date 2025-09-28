#pragma once

#include <string>
#include <functional>

namespace console_api {

using CommandHandler = std::function<void(const std::string& args)>;

void write_line(const std::string& text);
void write(const std::string& text);
std::string read_line();

void show_prompt(const std::string& prompt);

}
