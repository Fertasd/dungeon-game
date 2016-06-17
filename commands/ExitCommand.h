#pragma once

#include <asio.hpp>
#include "Command.h"

class ExitCommand : public Command
{
public:
	explicit ExitCommand(asio::io_service& ioService);
	void execute(std::shared_ptr<Controller> sender, const std::vector<std::string>& args) override;
private:
	asio::io_service& _ioService;
};
