#pragma once

#include <string>
#include <unordered_map>
#include <functional>

namespace app_core {

using CommandFn = std::function<void(const std::string& args)>;

class CommandRegistry {
public:
    void register_command(const std::string& name, CommandFn handler, const std::string& help);
    bool execute(const std::string& line) const;
    std::string build_help() const;

private:
    struct CommandInfo {
        CommandFn handler;
        std::string help;
    };
    std::unordered_map<std::string, CommandInfo> name_to_command_;
};

void run_repl(CommandRegistry& registry, const std::string& prompt);

}
