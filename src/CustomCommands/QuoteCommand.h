#ifndef _QuoteCommand_H
#define _QuoteCommand_H

#include "Command.h"
#include <fstream>
#include <vector>
#include <time.h>
#include <stdlib.h>

class QuoteCommand : Command
{
public:
    QuoteCommand();
    ~QuoteCommand();
    void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
