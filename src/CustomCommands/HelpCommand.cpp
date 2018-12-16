#include "CustomCommands/HelpCommand.h"

void HelpCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    std::string out = "URL HERE";
    client->SendPrivMsg(channel, out);
}

HelpCommand::HelpCommand()
{
}


HelpCommand::~HelpCommand()
{
}
