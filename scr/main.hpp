#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace BaseApp {
    class Console;
    
    class BaseApp {
    private:
        std::unique_ptr<Console> console;
        bool running;
        
    public:
        BaseApp();
        ~BaseApp();
        
        void run();
        void shutdown();
        bool isRunning() const;
    };
}