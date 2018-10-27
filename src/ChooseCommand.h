#pragma once
#ifndef _ChooseCommand_H
#define _ChooseCommand_H

#include "Command.h"
#include <time.h>

class ChooseCommand : Command
{
public:
	ChooseCommand();
	~ChooseCommand();
	void Execute(IRCClient* ircClient, std::string input, std::string channel);
};

#endif