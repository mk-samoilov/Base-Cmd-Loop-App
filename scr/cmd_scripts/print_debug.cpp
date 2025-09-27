#define _CRT_SECURE_NO_WARNINGS
#include "print_debug.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <random>
#include <windows.h>

namespace BaseApp {

void PrintDebug::printSystemInfo() {
    std::cout << "\n=== System Information ===" << std::endl;
    std::cout << "Platform: Windows" << std::endl;
    std::cout << "Compiler: MSVC/GCC" << std::endl;
    std::cout << "Architecture: x64" << std::endl;
}

void PrintDebug::printMemoryInfo() {
    std::cout << "\n=== Memory Information ===" << std::endl;
    
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    
    std::cout << "Total Physical Memory: " << (memInfo.ullTotalPhys / (1024 * 1024)) << " MB" << std::endl;
    std::cout << "Available Physical Memory: " << (memInfo.ullAvailPhys / (1024 * 1024)) << " MB" << std::endl;
    std::cout << "Memory Load: " << memInfo.dwMemoryLoad << "%" << std::endl;
}

void PrintDebug::printTimeInfo() {
    std::cout << "\n=== Time Information ===" << std::endl;
    
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    std::cout << "Current Time: " << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    std::cout << "." << std::setfill('0') << std::setw(3) << ms.count() << std::endl;
    
    auto uptime = std::chrono::steady_clock::now().time_since_epoch();
    auto hours = std::chrono::duration_cast<std::chrono::hours>(uptime).count();
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(uptime).count() % 60;
    
    std::cout << "Program Uptime: " << hours << "h " << minutes << "m" << std::endl;
}

void PrintDebug::printThreadInfo() {
    std::cout << "\n=== Thread Information ===" << std::endl;
    std::cout << "Main Thread ID: " << std::this_thread::get_id() << std::endl;
    std::cout << "Hardware Concurrency: " << std::thread::hardware_concurrency() << std::endl;
}

void PrintDebug::stressTest(int iterations) {
    std::cout << "\n=== Stress Test ===" << std::endl;
    std::cout << "Running " << iterations << " iterations..." << std::endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);
    
    long long sum = 0;
    for (int i = 0; i < iterations; ++i) {
        sum += dis(gen);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
    std::cout << "Operations per second: " << (iterations * 1000 / duration.count()) << std::endl;
}

void PrintDebug::handleCommand(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Usage: debug <option>" << std::endl;
        std::cout << "Options: system, memory, time, thread, stress [iterations]" << std::endl;
        return;
    }
    
    const std::string& option = args[1];
    
    if (option == "system") {
        printSystemInfo();
    } else if (option == "memory") {
        printMemoryInfo();
    } else if (option == "time") {
        printTimeInfo();
    } else if (option == "thread") {
        printThreadInfo();
    } else if (option == "stress") {
        int iterations = 1000;
        if (args.size() > 2) {
            try {
                iterations = std::stoi(args[2]);
            } catch (const std::exception&) {
                std::cout << "Invalid iteration count, using default: 1000" << std::endl;
            }
        }
        stressTest(iterations);
    } else if (option == "all") {
        printSystemInfo();
        printMemoryInfo();
        printTimeInfo();
        printThreadInfo();
        stressTest(1000);
    } else {
        std::cout << "Unknown debug option: " << option << std::endl;
        std::cout << "Available options: system, memory, time, thread, stress, all" << std::endl;
    }
}

}
