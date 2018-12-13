#ifndef _EightBallCommand_H
#define _EightBallCommand_H

#include "Command.h"
#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 

class EightBallCommand : Command
{
public:
	EightBallCommand();
	~EightBallCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
