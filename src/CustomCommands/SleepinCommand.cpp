#include "CustomCommands/SleepinCommand.h"

using namespace Global;

void SleepinCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input.find("-clear") != input.npos) {
        sleepers.erase(user);
        client->SendIRC("PRIVMSG " + channel + " :" + user +
        ", you have been removed from .sleepin");
        return;
    }
    sleepers.insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (sleepers.size() == 1)
    {
        out = sleepers.begin()->first + " is";
    }
    else if (sleepers.size() == 2)
    {
        std::string w2 = std::next(sleepers.begin())->first;
        out = sleepers.begin()->first + " and " + w2 + " are";
    }
    else{
        for (std::map<std::string, std::time_t>::iterator it=sleepers.begin(); it!=sleepers.end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(sleepers.end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(sleepers.end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    client ->SendIRC("PRIVMSG " + channel + " :" + user + " is hitting the hay");
    client ->SendIRC("PRIVMSG " + channel + " :" + out + " too bloody tired to chat.");
}

SleepinCommand::SleepinCommand()
{
}


SleepinCommand::~SleepinCommand()
{
}
