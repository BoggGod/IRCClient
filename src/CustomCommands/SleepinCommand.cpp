#include "CustomCommands/SleepinCommand.h"

void SleepinCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input.find("-clear") != input.npos) {
        if (client->flavMap.find("sleepers") != client->flavMap.end())
            client->flavMap["sleepers"].erase(user);
        client->SendIRC("PRIVMSG " + channel + " :" + user +
        ", you have been removed from .sleepin");
        return;
    }
    
    std::time_t currtime = std::time(nullptr);
    client->flavMap["sleepers"].insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (client->flavMap["sleepers"].size() == 1)
    {
        out = client->flavMap["sleepers"].begin()->first + " is";
    }
    else if (client->flavMap["sleepers"].size() == 2)
    {
        std::string w2 = std::next(client->flavMap["sleepers"].begin())->first;
        out = client->flavMap["sleepers"].begin()->first + " and " + w2 + " are";
    }
    else if (client->flavMap.find("sleepers") != client->flavMap.end()) {
        for (std::map<std::string, std::time_t>::iterator it=client->flavMap["sleepers"].begin(); it!=client->flavMap["sleepers"].end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(client->flavMap["sleepers"].end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(client->flavMap["sleepers"].end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    std::string finals = user + " is hitting the hay. " + out + " " +
    client->Response("sleepin");
    client->SendPrivMsg(channel, finals);
}

SleepinCommand::SleepinCommand()
{
}


SleepinCommand::~SleepinCommand()
{
}
