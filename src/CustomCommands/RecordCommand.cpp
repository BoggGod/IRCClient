#include "CustomCommands/RecordCommand.h"
#include <iostream>

void RecordCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input == "" || input == " ") {
        client->SendPrivMsg(channel, "Use .record or .quote to record a message, and .quote to display one.");
    } else {
        client->treasure.push_back(input);
        client->SendPrivMsg(channel, client->Response("record"));
        SaveVec(client->treasure, client->quotes);
    }
}

RecordCommand::RecordCommand()
{
}

RecordCommand::~RecordCommand()
{
}
