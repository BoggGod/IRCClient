#include "CustomCommands/DescCommand.h"

typedef std::map<std::string, std::string> stringMap;

void DescCommand::Execute(IRCClient* client, std::string input,
std::string user, std::string channel)
{
    bool validUser = true;
    std::string target = input.substr(0, input.find(" "));
    std::string usrInp;
    try {
        usrInp = input.substr(input.find(" "));
    }
    catch (const std::out_of_range& oor) {
        std::string usrInp = "";
    }
    if (usrInp == "-list") {
        client->SendIRC("PRIVMSG " + channel + " :" + "Oh no, you don't!");
        return;
    }
    std::string appStr = "";
    bool appFlag = false;
    if (usrInp.find("-append") != usrInp.npos) {
        appFlag = true;
        appStr = "-append";
    }else if (usrInp.find("+=") != usrInp.npos) {
        appFlag = true;
        appStr = "+=";
    }else if (usrInp.find("=+") != usrInp.npos) {
        appFlag = true;
        appStr = "=+";
    }
    if ((usrInp != "" && usrInp != " ") && ( target != " " && target != "" ))
    {
        if (!validUser) {
            client->SendIRC("PRIVMSG " + channel + " :" + "Sorry, you're not authorized to change descriptions.");
        }else if ((validUser) && (usrInp.find("-clear") != usrInp.npos)) {
            client->descMap2[target] = client->descMap[target];
            client->descMap.erase(target);
            client->SendIRC("PRIVMSG " + channel + " :" + "Description removed for " + target + ".");
        }else if (validUser && appFlag) {
            ltrim(usrInp);
            eraseSubstr(usrInp, appStr);
            client->descMap2[target] = client->descMap[target];
            client->descMap[target] += usrInp;
            client->SendIRC("PRIVMSG " + channel + " :" + "Appended to " + target + ".");
        }else if ((validUser) && (usrInp.find("-restore") != usrInp.npos)) {
            if (!client->descMap2[target].empty()) {
                std::string tempstr = client->descMap[target];
                client->descMap[target] = client->descMap2[target];
                client->descMap2[target] = tempstr;
                client->SendIRC("PRIVMSG " + channel + " :" + "Restored " + target + "'s description to previous entry.");
            }else{
                client->SendIRC("PRIVMSG " + channel + " :" + "There is no previous entry for this description. Use -clear if you want to remove the existing one.");
            }
        }else{
            ltrim(usrInp);
            client->descMap2[target] = client->descMap[target];
            client->descMap[target] = usrInp;
            client->SendIRC("PRIVMSG " + channel + " :" + "Added/updated " + target + "'s description.");
        }
    }else{
        
        std::map<std::string, std::string>::iterator it = client->descMap.find(target);
        if (target == "-list") 
        {
            std::vector<std::string> outList;
            std::size_t msg_size = 30;
            for (auto i = client->descMap.begin(); i != client->descMap.end()
                ; ++i) 
            {
                if (((std::distance(client->descMap.begin(), i) % msg_size != 0)
                    || (i == client->descMap.begin()))
                && (i != std::prev(client->descMap.end()))) 
                {
                    outList.push_back(i->first);
                } else {
                    outList.push_back(i->first);
                    sort(outList.begin(), outList.end(),
                    stringSort);
                    std::string foutput = "Descriptions: ";
                    for (auto &w : outList)
                        foutput += w + " ";
                    rtrim(foutput);
                    client->SendPrivMsg(channel, foutput);
                    outList.clear();
                }
            }
        }else if (it != client->descMap.end()) {
            client->SendIRC("PRIVMSG " + channel + " :" + "[" + it->first + 
            "]" + ": " + it->second);
        }else{
            client->SendIRC("PRIVMSG " + channel + " :No descriptions for [" + target + "].");
        }
    }
    printMap(client->descMap, client->descFile);
    printMap(client->descMap2, client->descFile2);
}


DescCommand::DescCommand()
{
}

DescCommand::~DescCommand()
{
}
