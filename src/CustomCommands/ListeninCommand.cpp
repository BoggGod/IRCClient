#include "CustomCommands/ListeninCommand.h"

void ListeninCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input.find("-clear") != input.npos) {
        if (client->flavMap.find("listeners") != client->flavMap.end())
        client->flavMap["listeners"].erase(user);
        client->SendIRC("PRIVMSG " + channel + " :" + user +
        ", you have been removed from .listenin");
        return;
    }
    std::time_t currtime = std::time(nullptr);
    client->flavMap["listeners"].insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (client->flavMap["listeners"].size() == 1)
    {
        out = client->flavMap["listeners"].begin()->first + " is";
    }
    else if (client->flavMap["listeners"].size() == 2)
    {
        std::string w2 = std::next(client->flavMap["listeners"].begin())->first;
        out = client->flavMap["listeners"].begin()->first + " and " + w2 + " are";
    }
    else {
        for (std::map<std::string, std::time_t>::iterator it=client->flavMap["listeners"].begin(); it!=client->flavMap["listeners"].end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(client->flavMap["listeners"].end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(client->flavMap["listeners"].end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    std::string finals = user + " turns up the volume. " + out + " "
    + client->Response("listenin");
    client->SendPrivMsg(channel, finals);
}

ListeninCommand::ListeninCommand()
{
}


ListeninCommand::~ListeninCommand()
{
}
