#ifndef _ListeninCommand_H
#define _ListeninCommand_H

#include "Command.h"
#include <ctime>

class ListeninCommand : Command
{
public:
	ListeninCommand();
	~ListeninCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
