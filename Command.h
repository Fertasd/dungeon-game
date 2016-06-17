#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Controller.h"

class Command
{
public:
	explicit Command(const std::string& name);
	virtual ~Command();
	inline const std::string& name() const { return _name; }
	virtual void execute(std::shared_ptr<Controller> sender, const std::vector<std::string>& args) = 0;
private:
	std::string _name;
};
