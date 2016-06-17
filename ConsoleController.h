#pragma once

#include "PlayerController.h"

class ConsoleController : public PlayerController
{
public:
	ConsoleController();
	void processInput();
};
