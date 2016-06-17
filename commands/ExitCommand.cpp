#include "ExitCommand.h"
#include "ConsoleController.h"

ExitCommand::ExitCommand(asio::io_service& ioService) : Command("exit"), _ioService(ioService)
{
}

void ExitCommand::execute(std::shared_ptr<Controller> sender, const std::vector<std::string>&)
{
	if (dynamic_cast<ConsoleController*>(sender.get()) != nullptr)
		_ioService.stop();
}
