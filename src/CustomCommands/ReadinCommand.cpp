#include "CustomCommands/ReadinCommand.h"

using namespace Global;

void ReadinCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input.find("-clear") != input.npos) {
        readers.erase(user);
        client->SendIRC("PRIVMSG " + channel + " :" + user +
        ", you have been removed from .readin");
        return;
    }
    readers.insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (readers.size() == 1)
    {
        out = readers.begin()->first + " is";
    }
    else if (readers.size() == 2)
    {
        std::string w2 = std::next(readers.begin())->first;
        out = readers.begin()->first + " and " + w2 + " are";
    }
    else{
        for (std::map<std::string, std::time_t>::iterator it=readers.begin(); it!=readers.end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(readers.end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(readers.end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    client ->SendIRC("PRIVMSG " + channel + " :" + user + " forgot to bookmark the page.");
    client ->SendIRC("PRIVMSG " + channel + " :" + out + " nose-deep in tomes of their choosing.");
}

ReadinCommand::ReadinCommand()
{
}


ReadinCommand::~ReadinCommand()
{
}
