#include "CustomCommands/QuoteCommand.h"
#include <iostream>

void QuoteCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) 
{
    srand(time(0));
    int i = (rand() % client->treasure.size());
    std::string output = "\"" + client->treasure[i] + "\"";
    client->SendPrivMsg(channel, output);
}

QuoteCommand::QuoteCommand()
{
}

QuoteCommand::~QuoteCommand()
{
}
