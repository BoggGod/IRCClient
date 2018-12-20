#include "CustomCommands/GaminCommand.h"

void GaminCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input.find("-clear") != input.npos) {
        if (client->flavMap.find("gamers") != client->flavMap.end())
            client->flavMap["gamers"].erase(user);
        client->SendIRC("PRIVMSG " + channel + " :" + user +
        ", you have been removed from .gamin");
        return;
    }
    
    std::time_t currtime = std::time(nullptr);
    client->flavMap["gamers"].insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (client->flavMap["gamers"].size() == 1)
    {
        out = client->flavMap["gamers"].begin()->first + " is";
    }
    else if (client->flavMap["gamers"].size() == 2)
    {
        std::string w2 = std::next(client->flavMap["gamers"].begin())->first;
        out = client->flavMap["gamers"].begin()->first + " and " + w2 + " are";
    }
    else {
        for (std::map<std::string, std::time_t>::iterator it=client->flavMap["gamers"].begin(); it!=client->flavMap["gamers"].end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(client->flavMap["gamers"].end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(client->flavMap["gamers"].end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    std::string finals = user + " wants to play. " + out + " " + client->Response("gamin");
    client->SendPrivMsg(channel, finals);
}

GaminCommand::GaminCommand()
{
}


GaminCommand::~GaminCommand()
{
}
