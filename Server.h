#pragma once

#include <asio.hpp>
#include "CommandFactory.h"

class Server
{
public:
	explicit Server(asio::io_service& ioService);
private:
	asio::io_service& _ioService;
	CommandFactory _commandFactory;
};
