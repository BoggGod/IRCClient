#ifndef _RecordCommand_H
#define _RecordCommand_H

#include "Command.h"
#include <fstream>
#include <map>
#include "Functions/general.h"
#include "Functions/SaveVec.h"

class RecordCommand : Command
{
public:
    RecordCommand();
    ~RecordCommand();
    void Execute(IRCClient* client, std::string input, std::string user, std::string channel);
};

#endif
