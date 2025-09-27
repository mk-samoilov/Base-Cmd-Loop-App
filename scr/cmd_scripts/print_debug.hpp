#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <thread>

namespace BaseApp {

class PrintDebug {
public:
    static void printSystemInfo();
    static void printMemoryInfo();
    static void printTimeInfo();
    static void printThreadInfo();
    static void stressTest(int iterations = 1000);
    static void handleCommand(const std::vector<std::string>& args);
};

}
