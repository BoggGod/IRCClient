#include "CustomCommands/SmsCommand.h"


typedef std::map<std::string, std::pair<std::string, std::pair<std::string, std::string>>> stringPairMap;
//(sender, recipient), (message, destination)
void SmsCommand::Execute(IRCClient* client, std::string input, std::string user, std::string channel) {
    std::string recipient = input.substr(0, input.find(" "));
    if (recipient == "" || input.find(" ") == std::string::npos)
    {
        client->SendIRC("PRIVMSG " + channel + " :Here's how this works: "
        + ".sms <recipient> <message> (optionally '-p' anywhere in the message to make it private)");
        return;
    }
    std::time_t now = time(0);
    char* dt = ctime(&now);
    std::tm *gmtm = gmtime (&now);
    dt = asctime(gmtm);
    std::string timestamp = dt;
    timestamp.erase(std::remove(timestamp.begin(), timestamp.end(), '\n'), timestamp.end());
    
    std::string message = input.substr(input.find(" ") + 1);
    std::string sender = user;
    std::string destination = channel;
    std::string output = "Input accepted, packet received, content acknowledged, message ready for destr- livery!";
    
    bool privat = false;
    std::string t = " -p";
    std::string::size_type i = message.find(t);
    
    if (i != std::string::npos) {
        message.erase(i, t.length());
        privat = true;
    }
    if (privat == true || user == channel) {
        destination = recipient;
        std::cout << channel << " " << user << " " << privat << std::endl;
        output = "I'll keep this confidential, lol.";
    }
    
    client->SendIRC("PRIVMSG " + channel + " :" + output);
    std::shared_ptr<SmsMessage> letter = std::make_shared<SmsMessage> (sender, destination, message, recipient, timestamp);
    
    client->smsMap[recipient].push_back(letter);
    for (auto &kv : client->smsMap)
    {
            std::cout << kv.second.front()->recipient << '\n'; 
            for (auto &v : kv.second) {
                std::cout << "#|" << v->sender << "#|" << v->destination
                << "#|" << v->message << "#|" << v->recipient << "#|" << v->timestamp
                << '\n';
            } 
                
    }
    
    smsMapToFile(client->smsMap, client->smsFile);
}

SmsCommand::SmsCommand()
{
}


SmsCommand::~SmsCommand()
{
}
