#include "CustomCommands/BikinCommand.h"


void BikinCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input.find("-clear") != input.npos) {
        if (client->flavMap.find("bikers") != client->flavMap.end())
            client->flavMap["bikers"].erase(user);
        client->SendIRC("PRIVMSG " + channel + " :" + user +
        ", you have been removed from .bikin");
        return;
    }
    std::time_t currtime = std::time(nullptr);
    client->flavMap["bikers"].insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (client->flavMap["bikers"].size() == 1)
    {
        out = client->flavMap["bikers"].begin()->first + " is";
    }
    else if (client->flavMap["bikers"].size() == 2)
    {
        std::string w2 = std::next(client->flavMap["bikers"].begin())->first;
        out = client->flavMap["bikers"].begin()->first + " and " + w2 + " are";
    }
    else {
        for (std::map<std::string, std::time_t>::iterator it=client->flavMap["bikers"].begin(); it!=client->flavMap["bikers"].end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(client->flavMap["bikers"].end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(client->flavMap["bikers"].end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    std::string finals = user + " knows that the road goes ever ever on. "
    + out + " " + client->Response("bikin");
    client->SendPrivMsg(channel, finals);
}

BikinCommand::BikinCommand()
{
}


BikinCommand::~BikinCommand()
{
}
