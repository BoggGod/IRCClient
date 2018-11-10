#ifndef _ShittasteCommand_H
#define _ShittasteCommand_H
#include "Command.h"

class ShittasteCommand : Command
{
public:
	ShittasteCommand();
	~ShittasteCommand();
	void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
