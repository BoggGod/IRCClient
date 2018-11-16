#ifndef _SmsCommand_H
#define _SmsCommand_H

#include "Vars.h"
#include "Functions/smsMapToFile.h"
#include "Command.h"
#include <memory>
#include <ctime>

class SmsCommand : Command
{
public:
    SmsCommand();
    ~SmsCommand();
    void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
