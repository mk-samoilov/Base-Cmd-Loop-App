#include "commands_registry.hpp"
#include "../core.hpp"
#include "../capi/console_api.hpp"

#include <string>
#include <sstream>

namespace app_core {

void setup_commands(CommandRegistry& registry) {
    registry.register_command("echo", [](const std::string& args) {
        console_api::write_line(args);
    }, "Print arguments");

    registry.register_command("sum", [](const std::string& args) {
        long long total = 0;
        long long value = 0;
        std::string token;
        std::istringstream iss(args);
        while (iss >> value) {
            total += value;
        }
        console_api::write_line("out: " + std::to_string(total));
    }, "Add numbers: sum 1 2 3");
}

}
