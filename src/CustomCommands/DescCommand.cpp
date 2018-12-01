#include "CustomCommands/DescCommand.h"

using namespace Global;

typedef std::map<std::string, std::string> stringMap;

void DescCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) 
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
    if (usrInp != "")
    {
        if (!validUser) {
            client->SendIRC("PRIVMSG " + channel + " :" + "Sorry, you're not authorized to change describes.");
        }else if ((validUser) && (usrInp.find("-clear") != usrInp.npos)) {
            describes.erase(target);
            client->SendIRC("PRIVMSG " + channel + " :" + "Describe removed for " + target + ".");
        }else if ((validUser) && (usrInp.find("-append") != usrInp.npos)) {
            ltrim(usrInp);
            eraseSubstr(usrInp, "-append");
            describes[target] += usrInp;
            client->SendIRC("PRIVMSG " + channel + " :" + "Appended to " + target + ".");
        }else{
            ltrim(usrInp);
            describes[target] = usrInp;
            client->SendIRC("PRIVMSG " + channel + " :" + "Added/updated " + target + "'s describe.");
        }
    }else{
        
        std::map<std::string, std::string>::iterator it = describes.find(target);
        if (target == "-list") {
            std::string outList = "";
            for (auto &w : describes) {
                if (outList.size() < (outList.max_size() - 200)) {
                outList += w.first + " ";
                }else{
                    client->SendIRC("PRIVMSG " + channel +
                    " :Oops, there are two many Describes for me to fit into"
                    + "a single string. Try annoying cesar a bit to give me an update.");
                    return;
                }
            }
            rtrim(outList);
            client->SendIRC("PRIVMSG " + channel + " :" + "Existing Describes: "
            + outList);
        }else if (it != describes.end()) {
            client->SendIRC("PRIVMSG " + channel + " :" + "[" + it->first + 
            "]" + ": " + it->second);
        }else{
            client->SendIRC("PRIVMSG " + channel + " :No describes for [" + target + "].");
        }
    }
    printMap(describes, descFile);
}


DescCommand::DescCommand()
{
}

DescCommand::~DescCommand()
{
}
