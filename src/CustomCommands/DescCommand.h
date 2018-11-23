#ifndef _DescCommand_H
#define _DescCommand_H

#include "Vars.h"
#include "Command.h"
#include <fstream>
#include <map>
#include <iostream>
#include <stdexcept>

class DescCommand : Command
{
public:
    DescCommand();
    ~DescCommand();
    void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
