#include <asio.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include "Server.h"

int main()
{
	try
	{
		asio::io_service ioService;

		Server server{ioService};

		auto threadPoolSize = std::thread::hardware_concurrency();
		std::vector<std::unique_ptr<std::thread>> threadPool{threadPoolSize};
		for (auto& thread : threadPool)
			thread = std::make_unique<std::thread>([&]{ ioService.run(); });
		ioService.run();
		for (auto& thread : threadPool)
			thread->join();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
