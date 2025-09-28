#include "core.hpp"
#include "capi/console_api.hpp"

#include <string>
#include <sstream>

int main() {
    app_core::CommandRegistry registry;

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
        console_api::write_line(std::to_string(total));
    }, "Add numbers: sum 1 2 3");

    console_api::write_line("[INFO] app started");
    app_core::run_repl(registry, "[baseapp]$ ");
    return 0;
}
