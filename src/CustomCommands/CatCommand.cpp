#include "CustomCommands/CatCommand.h"

void CatCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) 
{
    std::vector<std::string> responses = {
    {"meow"},
    {"meooooooooow"},
    {"nyan"},
    {"meowdy"}
    };
    std::string code = "\x01";

    std::string couch = code + "ACTION" + " scratches couch" + code;
    std::string purr = code + "ACTION" + " purrs" + code;
    std::string hiss = code + "ACTION" + " hisses" + code;
    std::string swat = code + "ACTION" + " swats at nose" + code;
    responses.push_back(couch);
    responses.push_back(purr);
    responses.push_back(hiss);
    responses.push_back(swat);
    
    srand(time(0));
    int i = (rand() % responses.size());
    client->SendPrivMsg(channel, responses[i]);
}

CatCommand::CatCommand()
{
}


CatCommand::~CatCommand()
{
}
