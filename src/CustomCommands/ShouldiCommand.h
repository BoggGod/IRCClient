#ifndef _ShouldiCommand_H
#define _ShouldiCommand_H

#include "Command.h"
#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 

class ShouldiCommand : Command
{
public:
	ShouldiCommand();
	~ShouldiCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
