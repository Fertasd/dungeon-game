#pragma once

#include <asio.hpp>

class Server
{
public:
	explicit Server(asio::io_service& ioService);
private:
	asio::io_service& _ioService;
};
