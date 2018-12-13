#ifndef _GaminCommand_H
#define _BikinCommand_H

#include "Command.h"
#include <ctime>

class GaminCommand : Command
{
public:
	GaminCommand();
	~GaminCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
