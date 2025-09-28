#include "console.hpp"

#include <iostream>
#include <algorithm>

namespace console
{
	static std::string toLower(std::string s)
	{
		std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
		return s;
	}

	LogLevel parseLogLevel(const std::string &levelStr)
	{
		std::string v = toLower(levelStr);
		if (v == "info") return LogLevel::Info;
		if (v == "warning" || v == "warn") return LogLevel::Warning;
		if (v == "error" || v == "err") return LogLevel::Error;
		if (v == "hint") return LogLevel::Hint;
        if (v == "debug") return LogLevel::Debug;
		return LogLevel::Info;
	}

	std::string getUserInput(const std::string &prompt)
	{
		if (!prompt.empty())
		{
			std::cout << prompt;
			std::cout.flush();
		}
		std::string input;
		std::getline(std::cin, input);
		return input;
	}

	void log(const std::string &message, LogLevel level)
	{
		switch (level)
		{
		case LogLevel::Info:
			std::cout << "[INFO] " << message << std::endl;
			break;
		case LogLevel::Warning:
			std::cout << "[WARNING] " << message << std::endl;
			break;
		case LogLevel::Error:
			std::cerr << "[ERROR] " << message << std::endl;
			break;
		case LogLevel::Hint:
			std::cout << "hint: " << message << std::endl;
			break;
        case LogLevel::Debug:
			std::cout << "debug: " << message << std::endl;
			break;
		}
	}
}


