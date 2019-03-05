#include "CustomCommands/DykCommand.h"
#include <iostream>

void DykCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) 
{
    if (input == "" || input == " ") {
        srand(time(0));
        int i = (rand() % client->dyks.size());
        std::string output = client->dyks[i];
        client->SendPrivMsg(channel, output);
    } else {
        client->dyks.push_back(input);
        std::string output = "DYK entry added.";
        client->SendPrivMsg(channel, output);
        SaveVec(client->dyks, client->dyksFile);
    }
}

DykCommand::DykCommand()
{
}

DykCommand::~DykCommand()
{
}
