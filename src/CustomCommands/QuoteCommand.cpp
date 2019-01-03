#include "CustomCommands/QuoteCommand.h"
#include <iostream>

void QuoteCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) 
{
    if (input == "" || input == " ") {
        srand(time(0));
        int i = (rand() % client->treasure.size());
        std::string output = client->treasure[i];
        client->SendPrivMsg(channel, output);
    } else {
        client->treasure.push_back(input);
        client->SendPrivMsg(channel, client->Response("record"));
        SaveVec(client->treasure, client->quotes);
    }
}

QuoteCommand::QuoteCommand()
{
}

QuoteCommand::~QuoteCommand()
{
}
