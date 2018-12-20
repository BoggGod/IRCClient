#include "CustomCommands/ReadinCommand.h"

void ReadinCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input.find("-clear") != input.npos) {
        if (client->flavMap.find("readers") != client->flavMap.end())
            client->flavMap["readers"].erase(user);
        client->SendIRC("PRIVMSG " + channel + " :" + user +
        ", you have been removed from .readin");
        return;
    }
    
    std::time_t currtime = std::time(nullptr);
    client->flavMap["readers"].insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (client->flavMap["readers"].size() == 1)
    {
        out = client->flavMap["readers"].begin()->first + " is";
    }
    else if (client->flavMap["readers"].size() == 2)
    {
        std::string w2 = std::next(client->flavMap["readers"].begin())->first;
        out = client->flavMap["readers"].begin()->first + " and " + w2 + " are";
    }
    else {
        for (std::map<std::string, std::time_t>::iterator it=client->flavMap["readers"].begin(); it!=client->flavMap["readers"].end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(client->flavMap["readers"].end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(client->flavMap["readers"].end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    std::string finals = user + " forgot to bookmark the page. " +  out + " " +
    client->Response("readin");
    client->SendPrivMsg(channel, finals);
}

ReadinCommand::ReadinCommand()
{
}


ReadinCommand::~ReadinCommand()
{
}
