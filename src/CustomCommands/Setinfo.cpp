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
        client->setMap2[user] = client->setMap[user];
        client->setMap.erase(user);
        client->SendIRC("PRIVMSG " + channel + " :Your setinfo has been removed.");
    }else if (input.find("-restore") != input.npos) {
        if (!client->setMap2[user].empty()) {
            std::string tempstr = client->setMap2[user];
            client->setMap2[user] = client->setMap[user];
            client->setMap[user] = tempstr;
            client->SendIRC("PRIVMSG " + channel + " :Setinfo restored to previous entry.");
        }else{
            client->SendIRC("PRIVMSG "+ channel + " :Looks like there are no backups for your setinfo.");
        }
    }else{
        std::map<std::string, std::string>::iterator it = client->setMap.find(user);
        if (it != client->setMap.end()) {
            ltrim(input);
            client->setMap2[user] = client->setMap[user];
            it->second = input;
            client->SendIRC("PRIVMSG " + channel + " :Your setinfo is updated.");
        }else{
            ltrim(input);
            client->setMap.insert (std::pair<std::string, std::string>(user, input));
            client->SendIRC("PRIVMSG " + channel + " :Setinfo Created!");
        }
    }
    printMap(client->setMap, client->setFile);
    printMap(client->setMap2, client->setFile2);
}


SetinfoCommand::SetinfoCommand()
{
}

SetinfoCommand::~SetinfoCommand()
{
}
