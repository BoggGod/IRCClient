#include "CustomCommands/CookieCommand.h"

void CookieCommand::Execute(IRCClient* client, std::string input,
std::string user, std::string channel)
{
    std::string target = input.substr(0, input.find(" "));
    std::string usrInp;
    try {
        usrInp = input.substr(input.find(" "));
    }
    catch (const std::out_of_range& oor) {
        std::string usrInp = "";
    }
    std::cout << "Target :" << target << "usrInp: " << usrInp << "input:" << input << std::endl;
    if (target != "" && target != " ")
    {
        ltrim(target);
        rtrim(target);
        if (target == user)
        {
            client->SendPrivMsg(channel, "Get your hands *out* of the cookie jar!");
            return;
        }
        srand(time(0));
        int sz = client->cookieVec.size();
        std::string cookie = client->cookieVec[rand() % sz];
        int quant = rand() % 3;
        std::cout << target << std::endl;
        
        if (client->invMap.find(target) == client->invMap.end()) 
        {
            Inventory inv;
            inv.Add("Cookies" ,cookie, quant);
            client->invMap[target] = inv;
        } else {
            client->invMap[target].Add("Cookies", cookie, quant);
        }
        std::string quantstr = std::to_string(quant);
        std::string out1 = user + " created" + quantstr + " " + cookie +
        (quant > 1 ? "'s " : " ") + "for " + target + ".";
        std::string out2 = user + (user.back() == 's' ? "'" : "'s") + 
        " generosity and goodwill has resulted in " 
        + target + (target.back() == 's' ? "'" : "'s") + " acquisition of " +
        quantstr + " " + cookie + (quant > 1 ? "'s." : ".");
        std::vector<std::string> options = {out1, out2};
        srand(time(0));
        client->SendPrivMsg(channel, options[rand() % options.size()]);
        
    } else {
        if (client->invMap.find(user) == client->invMap.end()) {
            client->SendPrivMsg(channel, "Whoops, you don't own anything!");
        } else {
            std::string outstr;
            outstr = client->invMap[user].Print("Cookies");
            client->SendPrivMsg(channel, outstr);
        }
    }
    SaveInv(client->invMap, client->invFile);
}


CookieCommand::CookieCommand()
{
}

CookieCommand::~CookieCommand()
{
}
