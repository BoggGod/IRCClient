#include "CustomCommands/InventoryCommand.h"

void InventoryCommand::Execute(IRCClient* client, std::string input,
std::string user, std::string channel)
{
    if (client->invMap.find(user) == client->invMap.end())
    {
        std::string out = "Sorry, you have no possessions.";
        client->SendPrivMsg(channel, out);
    } else {
        std::string out = "All your items: ";
        out += client->invMap[user].Print("Cookies");
        client->SendPrivMsg(channel, out);
    }
}

InventoryCommand::InventoryCommand()
{
}

InventoryCommand::~InventoryCommand()
{
}
