#ifndef _PoopinCommand_H
#define _PoopinCommand_H

#include "Command.h"
#include "Vars.h"

class PoopinCommand : Command
{
public:
	PoopinCommand();
	~PoopinCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
