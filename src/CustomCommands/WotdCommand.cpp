#include "CustomCommands/WotdCommand.h"
#include <iostream>

void WotdCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) 
{
    if (input == "" || input == " ") {
        srand(time(0));
        int i = (rand() % client->wotds.size());
        std::string output = client->wotds[i];
        client->SendPrivMsg(channel, output);
    } else {
        client->wotds.push_back(input);
        std::string output = "WOTD entry added.";
        client->SendPrivMsg(channel, output);
        SaveVec(client->wotds, client->wotdsFile);
    }
}

WotdCommand::WotdCommand()
{
}

WotdCommand::~WotdCommand()
{
}
