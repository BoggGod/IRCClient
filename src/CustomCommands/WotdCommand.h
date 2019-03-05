#ifndef _WotdCommand_H
#define _WotdCommand_H

#include "Command.h"
#include <fstream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "Functions/general.h"
#include "Functions/SaveVec.h"

class WotdCommand : Command
{
public:
    WotdCommand();
    ~WotdCommand();
    void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
