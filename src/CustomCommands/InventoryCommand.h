#ifndef _InventoryCommand_H
#define _InventoryCommand_H 

#include "Command.h"
#include <string>

class InventoryCommand : Command
{
public:
	InventoryCommand();
	~InventoryCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
