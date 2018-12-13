#ifndef _DrinkinCommand_H
#define _DrinkinCommand_H

#include "Command.h"
#include <map>
#include <iterator>
#include <ctime>

class DrinkinCommand : Command
{
public:
	DrinkinCommand();
	~DrinkinCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
