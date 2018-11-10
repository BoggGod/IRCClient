#include "CustomCommands/SmokinCommand.h"

using namespace Global;

void SmokinCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    
    smokers.insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (smokers.size() == 1)
    {
        out = smokers.begin()->first + " is";
    }
    else if (smokers.size() == 2)
    {
        std::string w2 = std::next(smokers.begin())->first;
        out = smokers.begin()->first + " and " + w2 + " are";
    }
    else{
        for (std::map<std::string, std::time_t>::iterator it=smokers.begin(); it!=smokers.end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(smokers.end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(smokers.end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    client->SendIRC("PRIVMSG " + channel + " :Mmmmmh my favorite.");
    client->SendIRC("PRIVMSG " + channel + " :" + out + " baked.");
}

SmokinCommand::SmokinCommand()
{
}


SmokinCommand::~SmokinCommand()
{
}
