#ifndef _DiceCommand_H
#define _DiceCommand_H

#include "Command.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <sstream>
#include <limits>
#include <regex>
#include <exception>

class DiceCommand : Command
{
public:
    DiceCommand();
    ~DiceCommand();
    void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
    
};

#endif
