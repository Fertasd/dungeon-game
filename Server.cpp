#include "Server.h"
#include "ConsoleController.h"

Server::Server(asio::io_service& ioService) : _ioService(ioService)
{
	auto localCtrl = std::make_shared<ConsoleController>();
	ioService.post([=]{ localCtrl->processInput(); });
}
