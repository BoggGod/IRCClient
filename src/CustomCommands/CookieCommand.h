#ifndef _CookieCommand_H
#define _CookieCommand_H 

#include "Command.h"
#include <string>
#include "Functions/SaveInv.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>

class CookieCommand : Command
{
public:
	CookieCommand();
	~CookieCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
