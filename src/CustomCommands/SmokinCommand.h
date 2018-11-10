#ifndef _SmokinCommand_H
#define _SmokinCommand_H

#include "Command.h"
#include "Vars.h"
#include <map>
#include <iterator>

class SmokinCommand : Command
{
public:
	SmokinCommand();
	~SmokinCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
