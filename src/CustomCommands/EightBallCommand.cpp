#include "CustomCommands/EightBallCommand.h"


void EightBallCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) 
{
    std::vector<std::string> responses = {
    {"YES. COMPLETELY, TOTALLY. ABSO-LUTELY!"},
    {"Yes."},
    {"Outlook good."},
    {"Signs point to yes."},
    {"Probably."},
    {"Life! Don't talk to me about life."},
    {"You haven't asked the right question, but I can tell you that the answer is 42."},
    {"I think you ought to know I'm feeling very depressed."},
    {"Do you want me to sit in a corner and rust or just fall apart where I'm standing?"},
    {"Life: loathe it or ignore it, you can't like it."},
    {"Probably not."},
    {"Doubt it."},
    {"Signs point to no."},
    {"Outlook bleak, but isn't it always?"},
    {"No."},
    {"Nope."},
    {"Definitely not."},
    {"Hell no."},
    {"Snowball's chance in Hell."},
    {"No! And fuck you, by the way."},
    {"I hope a pidgeon shits on the windshield of your life, bitchhh"}
    };
    srand(time(0));
    int i = (rand() % responses.size());
    client->SendPrivMsg(channel, responses[i]);
}

EightBallCommand::EightBallCommand()
{
}


EightBallCommand::~EightBallCommand()
{
}
