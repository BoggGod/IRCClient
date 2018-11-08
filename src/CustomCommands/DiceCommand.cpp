#include "CustomCommands/DiceCommand.h"

void DiceCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    std::stringstream trans(input);
    int x = 0;
    trans >> x;
    if ((!trans.fail()) && (x > 0)) 
    {
        x = round(x);
        srand(time(0));
        int result = (1+(rand()%x));
        std::string rresult = std::to_string(result);
        std::string output = user + " has rolled a " + rresult + ".";
        client->SendPrivMsg(channel, output);
        if (result == 420) {
            client->SendPrivMsg(channel, "FOUR TWENTY blaze it fgt!");
            client->SendPrivMsg(channel, "I think I might like you.");
        }
    }
    if ((trans.fail()) || (x <= 0))
    {
    trans.clear();
    trans.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    client->SendPrivMsg(channel, user + ", fuck you!");
    }
}

DiceCommand::DiceCommand()
{
}

DiceCommand::~DiceCommand()
{
}
