#ifndef _ChooseCommand_H
#define _ChooseCommand_H

#include "Command.h"
#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 

class ChooseCommand : Command
{
public:
	ChooseCommand();
	~ChooseCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
