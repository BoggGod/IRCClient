#include "CustomCommands/GaminCommand.h"

using namespace Global;

void GaminCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input.find("-clear") != input.npos) {
        gamers.erase(user);
        client->SendIRC("PRIVMSG " + channel + " :" + user +
        ", you have been removed from .gamin");
        return;
    }
    gamers.insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (gamers.size() == 1)
    {
        out = gamers.begin()->first + " is";
    }
    else if (gamers.size() == 2)
    {
        std::string w2 = std::next(gamers.begin())->first;
        out = gamers.begin()->first + " and " + w2 + " are";
    }
    else{
        for (std::map<std::string, std::time_t>::iterator it=gamers.begin(); it!=gamers.end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(gamers.end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(gamers.end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    client ->SendIRC("PRIVMSG " + channel + " :" + user + " wants to play.");
    client ->SendIRC("PRIVMSG " + channel + " :" + out + " escaping from reality into vidya games.");
}

GaminCommand::GaminCommand()
{
}


GaminCommand::~GaminCommand()
{
}
