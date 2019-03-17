#include "CustomCommands/WahCommand.h"
#include <iostream>

void WahCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) 
{
    if (input == "" || input == " ") {
        srand(time(0));
        int i = (rand() % client->wahs.size());
        std::string output = client->wahs[i];
        client->SendPrivMsg(channel, output);
    } else {
        client->wahs.push_back(input);
        std::string output = "There, there";
        client->SendPrivMsg(channel, output);
        SaveVec(client->wahs, client->wahsFile);
    }
}

WahCommand::WahCommand()
{
}

WahCommand::~WahCommand()
{
}
