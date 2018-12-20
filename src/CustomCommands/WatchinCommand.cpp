#include "CustomCommands/WatchinCommand.h"

void WatchinCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input.find("-clear") != input.npos) {
        client->flavMap["watchers"].erase(user);
        client->SendIRC("PRIVMSG " + channel + " :" + user +
        ", you have been removed from .watchin");
        return;
    }
    std::time_t currtime = std::time(nullptr);
    client->flavMap["watchers"].insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (client->flavMap["watchers"].size() == 1)
    {
        out = client->flavMap["watchers"].begin()->first + " is";
    }
    else if (client->flavMap["watchers"].size() == 2)
    {
        std::string w2 = std::next(client->flavMap["watchers"].begin())->first;
        out = client->flavMap["watchers"].begin()->first + " and " + w2 + " are";
    }
    else{
        for (std::map<std::string, std::time_t>::iterator it=client->flavMap["watchers"].begin(); it!=client->flavMap["watchers"].end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(client->flavMap["watchers"].end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(client->flavMap["watchers"].end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    std::size_t found = input.find("anime");
    std::string beg = "";
    if (found != std::string::npos) {
        beg = user + " is staring into the glassy 2d eyes.";
    }else{
        beg = user + " turned on the flickerbox.";
    }
    std::string finals = beg + " " + out + " " + client->Response("watchin");
    client->SendPrivMsg(channel, finals);
}

WatchinCommand::WatchinCommand()
{
}


WatchinCommand::~WatchinCommand()
{
}
