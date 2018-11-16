#include "CustomCommands/ListeninCommand.h"

using namespace Global;

void ListeninCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input.find("-clear") != input.npos) {
        listeners.erase(user);
        client->SendIRC("PRIVMSG " + channel + " :" + user +
        ", you have been removed from .listenin");
        return;
    }
    listeners.insert(std::pair<std::string, std::time_t>(user, currtime));
    std::string out;
    std::string joins;
    std::string ends;
    if (listeners.size() == 1)
    {
        out = listeners.begin()->first + " is";
    }
    else if (listeners.size() == 2)
    {
        std::string w2 = std::next(listeners.begin())->first;
        out = listeners.begin()->first + " and " + w2 + " are";
    }
    else{
        for (std::map<std::string, std::time_t>::iterator it=listeners.begin(); it!=listeners.end(); ++it)
        {
            ends = " are";
            if (!(it == std::prev(listeners.end(), 2)))
                joins = ", ";
            else 
                joins = " and ";
            if (it != std::prev(listeners.end()))
                out += it->first + joins;
            else
                out += it->first + ends;
        }

    }
    client ->SendIRC("PRIVMSG " + channel + " :" + user + " turns up the volume.");
    client ->SendIRC("PRIVMSG " + channel + " :" + out + " doing an independent study of music appreciation.");
}

ListeninCommand::ListeninCommand()
{
}


ListeninCommand::~ListeninCommand()
{
}
