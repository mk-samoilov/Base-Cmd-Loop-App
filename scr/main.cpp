#include "main.hpp"
#include "console/console.hpp"
#include <iostream>

namespace BaseApp {

BaseApp::BaseApp() : running(true) {
    console = std::make_unique<Console>();
}

BaseApp::~BaseApp() = default;

void BaseApp::run() {
    std::cout << "Base C++ Command Loop Application" << std::endl;
    std::cout << "Type 'help' for available commands or 'exit' to quit" << std::endl;
    
    while (running) {
        console->processInput();
    }
}

void BaseApp::shutdown() {
    running = false;
    std::cout << "Shutting down..." << std::endl;
}

bool BaseApp::isRunning() const {
    return running;
}

}

int main() {
    try {
        BaseApp::BaseApp app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
