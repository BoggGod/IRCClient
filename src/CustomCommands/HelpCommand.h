#ifndef _HelpCommand_H
#define _HelpCommand_H 

#include "Command.h"
#include <vector>
#include <string>
#include <iterator>
#include "Vars.h"

class HelpCommand : Command
{
public:
	HelpCommand();
	~HelpCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
