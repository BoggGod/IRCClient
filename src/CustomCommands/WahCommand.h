#ifndef _WahCommand_H
#define _WahCommand_H

#include "Command.h"
#include <fstream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "Functions/general.h"
#include "Functions/SaveVec.h"

class WahCommand : Command
{
public:
    WahCommand();
    ~WahCommand();
    void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
