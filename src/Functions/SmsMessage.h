#ifndef _SmsMessage_H
#define _SmsMessage_H

#include <string>
#include <iostream>
class SmsMessage 
{
public:
    SmsMessage();
    SmsMessage(std::string &send, std::string &dest, std::string &msg, std::string &recip, std::string &tm);
    std::string printMessageContent() const;
    std::string printMessageHeader() const;
    ~SmsMessage();
    
    std::string sender;
    std::string destination;
    std::string message;
    std::string recipient;
    std::string timestamp;

};

#endif
