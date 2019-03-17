#ifndef _CatCommand_H
#define _CatCommand_H

#include "Command.h"
#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 

class CatCommand : Command
{
public:
	CatCommand();
	~CatCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
