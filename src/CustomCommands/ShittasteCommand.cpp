#include "CustomCommands/ShittasteCommand.h"


void ShittasteCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    std::string code = "\x03";
    std::string color = "30";
    std::string color2 = "04";
    std::string color3 = "09";
    std::string color4 = "00";
    std::string output1 = code + color + "SHIT" + code + color2 + "TASTE" + code + color3 + "ONLINE" + code + color4;
    client->SendIRC("PRIVMSG " + channel + " :" + output1 +
    " ---> https://boards.420chan.org/irc/src/1525140531275.gif");
}

ShittasteCommand::ShittasteCommand()
{
}


ShittasteCommand::~ShittasteCommand()
{
}
