#include "CustomCommands/ShouldiCommand.h"


void ShouldiCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    std::string answer;
    srand(time(0));
    int i = (rand()%2);
    if (i == 0)
        answer = "Yes.";
    else
        answer = "No.";
    client ->SendPrivMsg(channel, answer);
}

ShouldiCommand::ShouldiCommand()
{
}


ShouldiCommand::~ShouldiCommand()
{
}
