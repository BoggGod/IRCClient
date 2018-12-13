#ifndef _ReadinCommand_H
#define _ReadinCommand_H

#include "Command.h"

class ReadinCommand : Command
{
public:
	ReadinCommand();
	~ReadinCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
