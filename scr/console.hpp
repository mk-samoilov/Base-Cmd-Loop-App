#pragma once

#include <string>

namespace console
{
	enum class LogLevel
	{
		Info,
		Warning,
		Error,
		Hint,
        Debug
	};

	std::string getUserInput(const std::string &prompt);

	void log(const std::string &message, LogLevel level = LogLevel::Info);

	LogLevel parseLogLevel(const std::string &levelStr);
}


