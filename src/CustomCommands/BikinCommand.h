#ifndef _BikinCommand_H
#define _BikinCommand_H

#include "Command.h"
#include <ctime>

class BikinCommand : Command
{
public:
	BikinCommand();
	~BikinCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
