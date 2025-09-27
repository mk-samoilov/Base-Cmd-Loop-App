#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <memory>

namespace BaseApp {

class Command {
public:
    std::string name;
    std::string description;
    std::function<void(const std::vector<std::string>&)> handler;
    
    Command(const std::string& cmdName, const std::string& cmdDesc, 
            std::function<void(const std::vector<std::string>&)> cmdHandler)
        : name(cmdName), description(cmdDesc), handler(cmdHandler) {}
};

class Console {
private:
    std::map<std::string, std::unique_ptr<Command>> commands;
    
    void registerBuiltinCommands();
    void printPrompt() const;
    std::vector<std::string> parseInput(const std::string& input) const;
    void executeCommand(const std::vector<std::string>& args);
    
public:
    Console();
    ~Console() = default;
    
    void registerCommand(const std::string& name, const std::string& description,
                        std::function<void(const std::vector<std::string>&)> handler);
    void processInput();
    void printHelp() const;
};

}
