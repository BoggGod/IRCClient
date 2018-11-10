#include "CustomCommands/ShittasteCommand.h"


void ShittasteCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    std::string code = "\x03";
    std::string color = "30";
    std::string color2 = "04";
    std::string color3 = "09";
    client->SendIRC("PRIVMSG " + channel + " :" + code + color + "SHIT" + code +  color2 + "TASTE" + code + color3 + "ONLINE");
}

ShittasteCommand::ShittasteCommand()
{
}


ShittasteCommand::~ShittasteCommand()
{
}
