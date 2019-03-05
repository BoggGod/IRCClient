#ifndef _NomminCommand_H
#define _NomminCommand_H

#include "Command.h"

class NomminCommand : Command
{
public:
	NomminCommand();
	~NomminCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
