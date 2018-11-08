#ifndef _SETINFO_H
#define _SETINFO_H

#include "Vars.h"
#include "Command.h"
#include <fstream>
#include <map>

class SetinfoCommand : Command
{
public:
    SetinfoCommand();
    ~SetinfoCommand();
    void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
