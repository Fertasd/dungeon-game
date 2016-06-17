#pragma once

#include <memory>

class Controller : public std::enable_shared_from_this<Controller>
{
public:
	virtual ~Controller();
};
