#ifndef _SleepinCommand_H
#define _SleepinCommand_H

#include "Command.h"
#include "Vars.h"

class SleepinCommand : Command
{
public:
	SleepinCommand();
	~SleepinCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
