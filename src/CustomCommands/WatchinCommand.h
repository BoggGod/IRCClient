#ifndef _WatchinCommand_H
#define _WatchinCommand_H

#include "Command.h"
#include "Vars.h"
#include <map>
#include <iterator>

class WatchinCommand : Command
{
public:
	WatchinCommand();
	~WatchinCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
