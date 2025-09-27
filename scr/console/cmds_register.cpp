#include "cmds_register.hpp"
#include "cmd_scripts/print_debug.hpp"
#include <iostream>

namespace BaseApp {

void registerDebugCommands(Console* console) {
    console->registerCommand("debug", "Debug information commands", 
        [](const std::vector<std::string>& args) {
            PrintDebug::handleCommand(args);
        });
    
    console->registerCommand("echo", "Echo input text", 
        [](const std::vector<std::string>& args) {
            if (args.size() < 2) {
                std::cout << "Usage: echo <text>" << std::endl;
                return;
            }
            
            for (size_t i = 1; i < args.size(); ++i) {
                std::cout << args[i];
                if (i < args.size() - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        });
    
    console->registerCommand("version", "Show application version", 
        [](const std::vector<std::string>&) {
            std::cout << "Base C++ Command Loop Application v1.0.0" << std::endl;
        });
}

}
