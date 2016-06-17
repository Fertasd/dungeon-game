#include "ConsoleController.h"
#include <iostream>
#include <string>
#include <global.h>

ConsoleController::ConsoleController()
{
}

void ConsoleController::processInput(const CommandFactory& commandFactory)
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		auto args = split(line, ' ');
		if (args.size() >= 1)
		{
			auto command = commandFactory.getCommand(args[0]);
			if (command)
			{
				command->execute(shared_from_this(), args);
				if (args[0] == "exit")
					break;
			}
		}
	}
}
