#pragma once

#include <asio.hpp>
#include <memory>
#include <map>
#include "Command.h"

class CommandFactory
{
public:
	explicit CommandFactory(asio::io_service& ioService);
	std::shared_ptr<Command> getCommand(const std::string& name) const;
	void registerCommand(std::shared_ptr<Command> command);
private:
	std::map<std::string, std::shared_ptr<Command>> _commands;
};
