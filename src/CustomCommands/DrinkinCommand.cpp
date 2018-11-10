#include "CustomCommands/DrinkinCommand.h"

using namespace Global;

void DrinkinCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    drinkers.insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (drinkers.size() == 1)
    {
        out = drinkers.begin()->first;
    }
    else if (drinkers.size() == 2)
    {
        std::string w2 = std::next(drinkers.begin())->first;
        out = drinkers.begin()->first + " and " + w2;
    }
    else{
        for (std::map<std::string, std::time_t>::iterator it=drinkers.begin(); it!=drinkers.end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(drinkers.end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(drinkers.end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    client->SendIRC("PRIVMSG " + channel + " :" + user + " is hitting the liquor.");
    std::string addon = (drinkers.size() > 4) ? " Please treat my relatives kindly." : "";
    client ->SendIRC("PRIVMSG " + channel + " :Another round for " + out + ". Cheers!" + addon);
}

DrinkinCommand::DrinkinCommand()
{
}


DrinkinCommand::~DrinkinCommand()
{
}
