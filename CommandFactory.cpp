#include "CommandFactory.h"
#include "commands/ExitCommand.h"

CommandFactory::CommandFactory(asio::io_service& ioService)
{
	registerCommand(std::make_shared<ExitCommand>(ioService));
}

std::shared_ptr<Command> CommandFactory::getCommand(const std::string& name) const
{
	auto command = _commands.find(name);
	return command == _commands.end() ? nullptr : command->second;
}

void CommandFactory::registerCommand(std::shared_ptr<Command> command)
{
	_commands.insert(std::make_pair(command->name(), command));
}
