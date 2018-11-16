#include "CustomCommands/WatchinCommand.h"

using namespace Global;

void WatchinCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input.find("-clear") != input.npos) {
        watchers.erase(user);
        client->SendIRC("PRIVMSG " + channel + " :" + user +
        ", you have been removed from .watchin");
        return;
    }

    watchers.insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (watchers.size() == 1)
    {
        out = watchers.begin()->first + " is";
    }
    else if (watchers.size() == 2)
    {
        std::string w2 = std::next(watchers.begin())->first;
        out = watchers.begin()->first + " and " + w2 + " are";
    }
    else{
        for (std::map<std::string, std::time_t>::iterator it=watchers.begin(); it!=watchers.end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(watchers.end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(watchers.end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    std::size_t found = input.find("anime");
    if (found != std::string::npos) {
        client ->SendIRC("PRIVMSG " + channel + " :" + user + " is staring into the glassy 2d eyes.");
    }else{
        client ->SendIRC("PRIVMSG " + channel + " :" + user + " turned on the flickerbox.");
    }
    client ->SendIRC("PRIVMSG " + channel + " :" + out + " watching stuff, probably nothing good.");
}

WatchinCommand::WatchinCommand()
{
}


WatchinCommand::~WatchinCommand()
{
}
