#include "CustomCommands/ChooseCommand.h"


void ChooseCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    const std::string orPattern = " or ";

    std::vector <std::string > options;
    int orIndex = 1;
    std::string option = "";
    orIndex = input.find(orPattern);

    while (orIndex > 0) {
        option = input.substr(0, orIndex);
        options.push_back(option);
        if (input.length() < orIndex + 4) {
            continue;
        }
        input = input.substr(orIndex + 4);
        orIndex = input.find(orPattern);
    }

    if (input != "") {
        options.push_back(input);
    }

    srand(time(0));
    int i = (rand() % options.size());

    client->SendPrivMsg(channel, options.at(i));
}

ChooseCommand::ChooseCommand()
{
}


ChooseCommand::~ChooseCommand()
{
}
