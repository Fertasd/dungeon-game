#include "ConsoleController.h"
#include <iostream>
#include <string>

ConsoleController::ConsoleController()
{
}

void ConsoleController::processInput()
{
	std::string line;
	while (std::getline(std::cin, line))
		if (line == "exit")
			break;
}
