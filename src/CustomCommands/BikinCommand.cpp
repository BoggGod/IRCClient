#include "CustomCommands/BikinCommand.h"

using namespace Global;

void BikinCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input.find("-clear") != input.npos) {
        bikers.erase(user);
        client->SendIRC("PRIVMSG " + channel + " :" + user +
        ", you have been removed from .bikin");
        return;
    }
    bikers.insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (bikers.size() == 1)
    {
        out = bikers.begin()->first + " is";
    }
    else if (bikers.size() == 2)
    {
        std::string w2 = std::next(bikers.begin())->first;
        out = bikers.begin()->first + " and " + w2 + " are";
    }
    else{
        for (std::map<std::string, std::time_t>::iterator it=bikers.begin(); it!=bikers.end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(bikers.end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(bikers.end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    client ->SendIRC("PRIVMSG " + channel + " :" + user + " knows that the road goes ever ever gon.");
    client ->SendIRC("PRIVMSG " + channel + " :" + out + " two wheels good.");
}

BikinCommand::BikinCommand()
{
}


BikinCommand::~BikinCommand()
{
}
