#include "CustomCommands/RecordCommand.h"
#include <iostream>

void RecordCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input == "" || input == " ") {
        client->SendPrivMsg(channel, "Use .record to record a message, and .quote to grab one to display.");
    } else {
        client->treasure.push_back(input);
        client->SendPrivMsg(channel, "Words of wisdom for the young?");
        SaveVec(client->treasure, client->quotes);
    }
}

RecordCommand::RecordCommand()
{
}

RecordCommand::~RecordCommand()
{
}
