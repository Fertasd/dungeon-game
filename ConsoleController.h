#pragma once

#include "PlayerController.h"
#include "CommandFactory.h"

class ConsoleController : public PlayerController
{
public:
	ConsoleController();
	void processInput(const CommandFactory& commandFactory);
};
