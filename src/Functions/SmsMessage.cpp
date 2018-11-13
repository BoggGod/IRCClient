#include "Functions/SmsMessage.h"

SmsMessage::SmsMessage()
{
}

SmsMessage::SmsMessage(std::string &send, std::string &dest, std::string &msg, std::string &recip) 
: sender(send), destination(dest), message(msg), recipient(recip)
{
}

std::string SmsMessage::printFormat() const
{
    std::string output = "PRIVMSG " + this->destination + " :" + this->recipient
    + "! " + this->sender + " has left me a message for you. It reads: ";
    return output;
}

std::string SmsMessage::printFormat2() const
{
    std::string output = "PRIVMSG " + this->destination + " :" + "\"" + 
    this->message + "\"";
    return output;
}

SmsMessage::~SmsMessage()
{
}
