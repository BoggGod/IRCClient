#include "CustomCommands/FlavorCommand.h"

void FlavorCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    
    bool validUser = true;
    std::string target = input.substr(0, input.find(" "));
    std::string usrInp;
    try {
        usrInp = input.substr(input.find(" "));
    }
    catch (const std::out_of_range& oor) {
        std::string usrInp = "";
    }
    
    if (input == "" || input == " ")
    {
        std::string helpmsg = "Live response line editing! Long Live cesar! Type in something like \".flavor sleepin counting sheep\" and your alternative response for 'sleepin' will go into rotation alatoul! For a list of valid commands to edit, type \".flavors -list\". Even ficitious commands will be saved and considered for the future.";
        client->SendPrivMsg(channel, helpmsg);
    }
    else if (input == "-list")
    {
        std::string listargs = "Commands with editable response lines: bikin, gamin, listenin, poopin, record, readin, sleepin, smokin, watchin, namaste, flavor.";
        client->SendPrivMsg(channel, listargs);
    }
    else if (!target.empty() && !usrInp.empty() && usrInp != " ")
    {
        ltrim(usrInp);
        client->flavs[target].push_back(usrInp);
        SaveFlav(client->flavs, client->flavFile);
        std::string resp = client->Response("flavor");
        client->SendPrivMsg(channel, resp);
    }
}

FlavorCommand::FlavorCommand()
{
}


FlavorCommand::~FlavorCommand()
{
}
