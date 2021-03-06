#ifndef _SmsCommand_H
#define _SmsCommand_H

#include "Functions/smsMapToFile.h"
#include "Command.h"
#include <memory>
#include <ctime>
#include <algorithm>

class SmsCommand : Command
{
public:
    SmsCommand();
    ~SmsCommand();
    virtual void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
