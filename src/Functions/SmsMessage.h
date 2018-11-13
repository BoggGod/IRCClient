#ifndef _SmsMessage_H
#define _SmsMessage_H

#include <string>
#include <iostream>
class SmsMessage 
{
public:
    SmsMessage();
    SmsMessage(std::string &send, std::string &dest, std::string &msg, std::string &recip);
    std::string printFormat() const;
    std::string printFormat2() const;
    ~SmsMessage();
    
    std::string sender;
    std::string destination;
    std::string message;
    std::string recipient;

};

#endif
