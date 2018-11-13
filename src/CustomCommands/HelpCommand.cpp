#include "CustomCommands/HelpCommand.h"

using namespace Global;

void HelpCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    std::string output;
    int charCount;
    for (int t = 0; t != commandList.size(); ++t) {
        std::string curstr = commandList[t];
        output += curstr + "\r\n";
        for (int j = 0; j != curstr.size(); ++j) {
            ++charCount;
        }
        if ((charCount >= 400) || (t = commandList.size() -1)) {
            client->SendPrivMsg(channel, output);
            output = "";
        }
    }
}

HelpCommand::HelpCommand()
{
}


HelpCommand::~HelpCommand()
{
}
