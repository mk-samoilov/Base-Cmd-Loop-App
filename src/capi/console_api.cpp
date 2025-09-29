#include "console_api.hpp"

#include <iostream>

namespace console_api {

void write_line(const std::string& text) {
    std::cout << text << std::endl;
}

void write(const std::string& text) {
    std::cout << text;
}

std::string read_line() {
    std::string input;
    if (!std::getline(std::cin, input)) {
        std::cin.clear();
        std::cin.ignore();
        return "";
    }
    return input;
}

void show_prompt(const std::string& prompt) {
    write(prompt);
    std::cout.flush();
}

}
