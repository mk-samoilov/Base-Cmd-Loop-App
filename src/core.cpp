#include "core.hpp"
#include "capi/console_api.hpp"

#include <sstream>
#include <algorithm>

namespace app_core {

static std::string trim_copy(const std::string& s) {
    const auto not_space = [](unsigned char c){ return !std::isspace(c); };
    auto begin_it = std::find_if(s.begin(), s.end(), not_space);
    auto end_it = std::find_if(s.rbegin(), s.rend(), not_space).base();
    if (begin_it >= end_it) return std::string();
    return std::string(begin_it, end_it);
}

void CommandRegistry::register_command(const std::string& name, CommandFn handler, const std::string& help) {
    name_to_command_[name] = CommandInfo{ std::move(handler), help };
}

bool CommandRegistry::execute(const std::string& line) const {
    std::istringstream iss(line);
    std::string cmd;
    if (!(iss >> cmd)) return false;
    std::string args;
    std::getline(iss, args);
    if (!args.empty() && args.front() == ' ') args.erase(args.begin());

    auto it = name_to_command_.find(cmd);
    if (it == name_to_command_.end()) return false;
    it->second.handler(args);
    return true;
}

std::string CommandRegistry::build_help() const {
    std::string out;
    out += "Available commands:\n";
    for (const auto& kv : name_to_command_) {
        out += "  " + kv.first + " - " + kv.second.help + "\n";
    }
    if (!out.empty() && out.back() == '\n') {
        out.pop_back();
    }
    return out;
}

void run_repl(CommandRegistry& registry, const std::string& prompt) {
    using namespace console_api;
    
    while (true) {
        show_prompt(prompt);
        const std::string line = read_line();
        const std::string trimmed = trim_copy(line);
        
        if (trimmed.empty()) continue;

        if (trimmed == "exit" || trimmed == "quit") {
            write_line("Exiting...");
            break;
        }

        if (trimmed == "help") {
            write_line(registry.build_help());
            continue;
        }

        if (!registry.execute(trimmed)) {
            write_line("Unknown command. Type 'help' for a list.");
        }
    }
}

}
