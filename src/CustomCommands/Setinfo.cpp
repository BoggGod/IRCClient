#include "CustomCommands/Setinfo.h"
#include <iostream>

typedef std::map<std::string, std::string> stringMap;

void SetinfoCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input == "" || input == " ") {
        if (client->setMap.find(user) != client->setMap.end()) {
            client->SendIRC("PRIVMSG " + channel + " :" + user + "'s setinfo: " + client->setMap[user]);
            return;
        }
    }else if (input.find("-clear") != input.npos) {
        client->setMap.erase(user);
        client->SendIRC("PRIVMSG " + channel + " :Your setinfo has been removed.");
    }else{
        std::map<std::string, std::string>::iterator it = client->setMap.find(user);
        //std::string filename = "UserInfoMap";
        if (it != client->setMap.end()) {
            ltrim(input);
            it->second = input;
            client->SendIRC("PRIVMSG " + channel + " :Your setinfo is updated.");
        }else{
            ltrim(input);
            client->setMap.insert (std::pair<std::string, std::string>(user, input));
            client->SendIRC("PRIVMSG " + channel + " :Your very first setinfo with me is added. How delightful for one of us.");
        }
    }
    printMap(client->setMap, client->setFile);
}


SetinfoCommand::SetinfoCommand()
{
}

SetinfoCommand::~SetinfoCommand()
{
}
