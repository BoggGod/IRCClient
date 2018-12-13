#ifndef _Inventory_H
#define _Inventory_H

#include <string>
#include <iostream>


class Inventory 
{
friend Cookies::PrintCookies();

public:
    Inventory();
    Inventory(std::string &send, std::string &dest, std::string &msg, std::string &recip, std::string &tm);
    std::string PrintInventory() const;
    for 
    std::string AddToInventory();


    ~Inventory();
    
    Cookies cookies;
    
    std::map<
    std::string destination;
    std::string message;
    std::string recipient;
    std::string timestamp;

};

#endif
