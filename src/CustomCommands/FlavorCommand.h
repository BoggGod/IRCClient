#ifndef _FlavorCommand_H
#define _FlavorCommand_H

#include "Command.h"
#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 
#include "Functions/SaveFlav.h"

class FlavorCommand : Command
{
public:
	FlavorCommand();
	~FlavorCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
