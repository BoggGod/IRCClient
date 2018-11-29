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
    
    /*
    if (std::find(descTargets.begin(), descTargets.end(), target) != descTargets.end())
    {
        validTarget = true;

    }else{ 
        client->SendIRC("PRIVMSG " + channel + " :" + "Fool, you've gotta give me one of Sir Dr. Worm's nicks");
        client->SendIRC("PRIVMSG " + channel + " :" + target);
        return;
    }
    if (std::find(descTargets.begin(), descTargets.end(), user) != descTargets.end())
    {
        validUser = true;
    }
    
    if (validTarget)
    {*/
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
        if (it != describes.end()) {
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
