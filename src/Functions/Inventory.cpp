#include "Functions/Inventory.h"

std::string Inventory::Format()
{
    std::string output = this->cookies.Format();
    return output;
}

void Inventory::Reset()
{
    this->cookies.Reset();
}

void Inventory::Add(const std::string &c, const std::string &i, const int &d)
{
    if (c == "Cookies")
        this->cookies.Add(i, d);
    else
        return;
}

std::string Inventory::Print(const std::string &c)
{
    if (c == "Cookies") {
        std::string out = "Cookies: ";
        this->cookies.Print(out);
        return out;
    } else if (c == "Inventory") {
        std::string out = "Inventory: Cookies: ";
        this->cookies.Print(out);
        return out;
    } else
        return c;
}
    
/*bool Inventory::operator<(const Inventory& lhs) const
{
    return this.cookie < lhs.cookie;
    //return std::tie(a, s, w) < std::tie(lhs.e, lhs.s, lhs.w);
}
*/
Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}

