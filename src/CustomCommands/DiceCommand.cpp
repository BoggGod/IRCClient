#include "CustomCommands/DiceCommand.h"

void DiceCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    std::stringstream trans(input);
    int x = 0;
    int result = 0;
    std::string rresult = "";
    int dubs = 0;
    
    
   // std::regex multi {"[0-9][0-9][0-9]"};
    trans >> x;

    // simple throw
    if ((!trans.fail()) && (x > 0)) //&& (!std::regex_match (input, multi))) 
    {
        x = round(x);
        srand(time(0));
        result = (1+(rand()%x));
        rresult = std::to_string(result);
        std::string grammar = "a ";
        if (rresult[0] == '8')
            grammar = "an ";
        std::string output = user + " has rolled " + grammar + rresult + ".";
        client->SendPrivMsg(channel, output);
    // regex logic
    /*
    }else if (std::regex_match (input, multi)) 
    {
        std::string::size_type sz = 1;
        std::string a = "";
        if ((input.find("d") ) != sz)
            a = input.substr(0, input.find("d"));
        else
            a = *input.begin();
        std::string b = input.substr(input.find("d") + 1);
        int dies = 0;
        int faces = 0;
        try {
            dies = std::stoi (a);
            faces = std::stoi (b);
        } catch (const std::out_of_range& oor) {
            client->SendIRC("PRIVMSG " + channel + " :" +
            "TOO BIG!!");
            return;
        }
        for (int i = 0; i != dies; ++i) {
            srand(time(0));
            if (!((result + faces) >= 2147483647)) {
                result += (1+(rand()%faces));
            }else{
                client->SendIRC("PRIVMSG " + channel + " :" + "TOO BIG!");
                return;
            }
        }
        rresult = std::to_string(result);
        std::string grammar = "a ";
        if (rresult[0] == '8')
            grammar = "an ";
        client->SendIRC("PRIVMSG " + channel + " :" +
        user + " has thrown " + std::to_string(dies) + " die" +
        " with " + std::to_string(faces) + " faces each, rolling "
        + grammar + rresult + "!");
      */
    
    // invalid input part
    }else if ((trans.fail()) || (x <= 0))
    {
    trans.clear();
    trans.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    client->SendPrivMsg(channel, user + ", fuck you!");
    }
    
    // dubs determination
    for (auto it = rresult.rbegin(); it != rresult.rend(); ++it)
    {
        if (*it == *(it+1))
            dubs += 1;
    }
    if (dubs == 1)
        client->SendPrivMsg(channel, "DUBS!");
    if (dubs == 2) 
        client->SendPrivMsg(channel, "ＴＲＩＰＳ！");
    if (dubs == 3)
        client->SendPrivMsg(channel, "ＱＵＡＤＳ！");
    if (dubs == 4)
    
    if (result == 420) {
    client->SendPrivMsg(channel, "ＦＯＵＲＴＷＥＮＴＹ");
    client->SendPrivMsg(channel, "ＢＬＡＺＥ　ＩＴ　ＦＧＴ！");
    }
}

DiceCommand::DiceCommand()
{
}

DiceCommand::~DiceCommand()
{
}
