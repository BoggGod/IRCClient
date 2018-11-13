#include "CustomCommands/Setinfo.h"

using namespace Global;

typedef std::map<std::string, std::string> stringMap;

void SetinfoCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    if (input == "") {
        if (setinfos.find(user) != setinfos.end()) {
            client->SendIRC("PRIVMSG " + channel + " :" + user + "'s setinfo: " + setinfos[user]);
            return;
        }
    }else{
        std::map<std::string, std::string>::iterator it = setinfos.find(user);
        //std::string filename = "UserInfoMap";
        if (it != setinfos.end()) {
            it->second = input;
            client->SendIRC("PRIVMSG " + channel + " :Your setinfo is updated.");
        }else{
            setinfos.insert (std::pair<std::string, std::string>(user, input));
            client->SendIRC("PRIVMSG " + channel + " :Your very first setinfo with me is added. How delightful for one of us.");
        }
        printMap(setinfos, setinfoFile);
    }
}


SetinfoCommand::SetinfoCommand()
{
}

SetinfoCommand::~SetinfoCommand()
{
}
