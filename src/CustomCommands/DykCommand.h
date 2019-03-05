#ifndef _DykCommand_H
#define _DykCommand_H

#include "Command.h"
#include <fstream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "Functions/general.h"
#include "Functions/SaveVec.h"

class DykCommand : Command
{
public:
    DykCommand();
    ~DykCommand();
    void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
