#include "CustomCommands/PoopinCommand.h"

using namespace Global;

void PoopinCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input.find("-clear") != input.npos) {
        poopers.erase(user);
        client->SendIRC("PRIVMSG " + channel + " :" + user +
        ", you have been removed from .poopin." +
        " I hope the experience has been palatable.");
        return;
    }
    poopers.insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    std::string adds;
    if (poopers.size() == 1)
    {
        out = poopers.begin()->first + " is";
    }
    else if (poopers.size() == 2)
    {
        std::string w2 = std::next(poopers.begin())->first;
        out = poopers.begin()->first + " and " + w2 + " are";
    }
    else{
        for (std::map<std::string, std::time_t>::iterator it=poopers.begin(); it!=poopers.end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(poopers.end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(poopers.end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    client ->SendIRC("PRIVMSG " + channel + " :" + user + " is taking a dump!");
    if (poopers.size() == 1) {
        client->SendIRC("PRIVMSG " + channel + " :【ＬＥＴ ＩＴ ＡＬＬ ＯＵＴ】");
    }else{
    client ->SendIRC("PRIVMSG " + channel + " :" + out + " taking a collective dump.");
    }
}

PoopinCommand::PoopinCommand()
{
}


PoopinCommand::~PoopinCommand()
{
}
