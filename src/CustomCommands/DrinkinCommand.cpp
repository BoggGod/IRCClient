#include "CustomCommands/DrinkinCommand.h"

void DrinkinCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input.find("-clear") != input.npos) {
        if (client->flavMap.find("drinkers") != client->flavMap.end())
            client->flavMap["drinkers"].erase(user);
        client->SendIRC("PRIVMSG " + channel + " :" + user +
        ", you have been removed from .drinkin");
        return;
    }
    
    std::time_t currtime = std::time(nullptr);
    client->flavMap["drinkers"].insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (client->flavMap["drinkers"].size() == 1)
    {
        out = client->flavMap["drinkers"].begin()->first;
    }
    else if (client->flavMap["drinkers"].size() == 2)
    {
        std::string w2 = std::next(client->flavMap["drinkers"].begin())->first;
        out = client->flavMap["drinkers"].begin()->first + " and " + w2;
    }
    else {
        for (std::map<std::string, std::time_t>::iterator it=client->flavMap["drinkers"].begin(); it!=client->flavMap["drinkers"].end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(client->flavMap["drinkers"].end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(client->flavMap["drinkers"].end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }
    }
    std::string finals = user + " is hitting the liquor." +
    " Another round for " + out + ". Cheers!";
    client ->SendPrivMsg(channel, finals);
}

DrinkinCommand::DrinkinCommand()
{
}


DrinkinCommand::~DrinkinCommand()
{
}
