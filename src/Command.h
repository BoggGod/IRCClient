#ifndef _Command_H
#define _Command_H

#include "IRCClient.h"
#include <string>

class Command
{
	public:
		virtual void Execute(IRCClient* ircClient, std::string input, std::string channel) = 0;
		Command();
		~Command();

};

#endif