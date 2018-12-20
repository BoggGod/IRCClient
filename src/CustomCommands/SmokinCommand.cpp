#include "CustomCommands/SmokinCommand.h"

void SmokinCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) 
{
    std::time_t currtime = std::time(nullptr);
    client->flavMap["smokers"].insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (client->flavMap["smokers"].size() == 1)
    {
        out = client->flavMap["smokers"].begin()->first + " is";
    }
    else if (client->flavMap["smokers"].size() == 2)
    {
        std::string w2 = std::next(client->flavMap["smokers"].begin())->first;
        out = client->flavMap["smokers"].begin()->first + " and " + w2 + " are";
    }
    else{
        for (std::map<std::string, std::time_t>::iterator it=client->flavMap["smokers"].begin(); it!=client->flavMap["smokers"].end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(client->flavMap["smokers"].end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(client->flavMap["smokers"].end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    std::string finals = user + " is hitting the reefer. " + out + " " +
    client->Response("smokin");
    client->SendPrivMsg(channel, finals);
}

SmokinCommand::SmokinCommand()
{
}


SmokinCommand::~SmokinCommand()
{
}
