#ifndef _SETINFO_H
#define _SETINFO_H

#include "Command.h"
#include <fstream>
#include <map>
#include "Functions/general.h"

class SetinfoCommand : Command
{
public:
    SetinfoCommand();
    ~SetinfoCommand();
    void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
