#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "console.hpp"

namespace
{
	std::vector<std::string> splitBySpaces(const std::string &line)
	{
		std::istringstream iss(line);
		std::vector<std::string> tokens;
		std::string token;
		while (iss >> token)
		{
			tokens.push_back(token);
		}
		return tokens;
	}
}

int main()
{
	using namespace console;
	console::log("qq");

	bool running = true;
	while (running)
	{
		std::string line = console::getUserInput("> ");
		auto args = splitBySpaces(line);
		if (args.empty())
		{
			continue;
		}

		std::string cmd = args[0];
		std::transform(cmd.begin(), cmd.end(), cmd.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

		if (cmd == "exit" || cmd == "quit")
		{
			console::log("Завершение работы...");
			running = false;
		}
		else if (cmd == "help")
		{
			console::log("Доступные команды:");
			console::log("  help                 - показать помощь");
			console::log("  echo <text>          - вывести текст");
			console::log("  log <lvl> <message>  - логировать с уровнем (info/warning/error/wint)");
			console::log("  exit                 - выйти из приложения");
		}
		else if (cmd == "echo")
		{
			if (args.size() < 2)
			{
				console::log("Использование: echo <text>", LogLevel::Warning);
				continue;
			}
			std::string out = line.substr(line.find(cmd) + cmd.size());
			if (!out.empty() && out.front() == ' ')
			{
				out.erase(out.begin());
			}
			console::log(out);
		}
		else if (cmd == "log")
		{
			if (args.size() < 3)
			{
				console::log("Использование: log <info|warning|error|wint> <message>", LogLevel::Warning);
				continue;
			}
			LogLevel lvl = parseLogLevel(args[1]);
			std::size_t pos = line.find(args[1]);
			std::string msg = (pos != std::string::npos) ? line.substr(pos + args[1].size()) : std::string();
			if (!msg.empty() && msg.front() == ' ')
			{
				msg.erase(msg.begin());
			}
			console::log(msg, lvl);
		}
		else
		{
			console::log("Неизвестная команда: '" + cmd + "'", LogLevel::Warning);
		}
	}

	return 0;
}


