#include "console.hpp"
#include "cmds_register.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

namespace BaseApp {

Console::Console() {
    registerBuiltinCommands();
    registerDebugCommands(this);
}

void Console::registerBuiltinCommands() {
    registerCommand("help", "Show available commands", 
        [this](const std::vector<std::string>&) {
            printHelp();
        });
    
    registerCommand("exit", "Exit the application", 
        [this](const std::vector<std::string>&) {
            std::cout << "Goodbye!" << std::endl;
            std::exit(0);
        });
    
    registerCommand("clear", "Clear the console", 
        [this](const std::vector<std::string>&) {
            system("cls");
        });
}

void Console::registerCommand(const std::string& name, const std::string& description,
                             std::function<void(const std::vector<std::string>&)> handler) {
    commands[name] = std::make_unique<Command>(name, description, handler);
}

void Console::printPrompt() const {
    std::cout << "BaseApp> ";
}

std::vector<std::string> Console::parseInput(const std::string& input) const {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;
    
    while (ss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

void Console::executeCommand(const std::vector<std::string>& args) {
    if (args.empty()) {
        return;
    }
    
    const std::string& commandName = args[0];
    auto it = commands.find(commandName);
    
    if (it != commands.end()) {
        try {
            it->second->handler(args);
        } catch (const std::exception& e) {
            std::cout << "Error executing command '" << commandName << "': " << e.what() << std::endl;
        }
    } else {
        std::cout << "Unknown command: " << commandName << std::endl;
        std::cout << "Type 'help' for available commands" << std::endl;
    }
}

void Console::processInput() {
    printPrompt();
    
    std::string input;
    std::getline(std::cin, input);
    
    if (input.empty()) {
        return;
    }
    
    std::vector<std::string> args = parseInput(input);
    executeCommand(args);
}

void Console::printHelp() const {
    std::cout << "\nAvailable commands:" << std::endl;
    std::cout << "==================" << std::endl;
    
    for (const auto& pair : commands) {
        std::cout << "  " << pair.first << " - " << pair.second->description << std::endl;
    }
    
    std::cout << std::endl;
}

}
