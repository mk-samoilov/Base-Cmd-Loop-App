#include "core.hpp"
#include "capi/console_api.hpp"
#include "cr/commands_registry.hpp"

int main() {
    app_core::CommandRegistry registry;
    
    app_core::setup_commands(registry);

    console_api::write_line("[INFO] app started");
    app_core::run_repl(registry, "[baseapp]$ ");
    return 0;
}
