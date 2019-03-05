#include "CustomCommands/NomminCommand.h"

void NomminCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input.find("-clear") != input.npos) {
        if (client->flavMap.find("nommers") != client->flavMap.end())
            client->flavMap["nommers"].erase(user);
        client->SendIRC("PRIVMSG " + channel + " :" + user +
        ", you have been removed from .nommin");
        return;
    }
    
    std::time_t currtime = std::time(nullptr);
    client->flavMap["nommers"].insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (client->flavMap["nommers"].size() == 1)
    {
        out = client->flavMap["nommers"].begin()->first + " is";
    }
    else if (client->flavMap["nommers"].size() == 2)
    {
        std::string w2 = std::next(client->flavMap["nommers"].begin())->first;
        out = client->flavMap["nommers"].begin()->first + " and " + w2 + " are";
    }
    else {
        for (std::map<std::string, std::time_t>::iterator it=client->flavMap["nommers"].begin(); it!=client->flavMap["nommers"].end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(client->flavMap["nommers"].end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(client->flavMap["nommers"].end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    std::string finals = user + " is stuffing their face.";
    client->SendPrivMsg(channel, finals);
}

NomminCommand::NomminCommand()
{
}


NomminCommand::~NomminCommand()
{
}
