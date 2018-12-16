#include "Functions/Cookie.h"

Cookie::Cookie()
{
} 
/*
bool Inventory::operator<(const Cookie& lhs) const
{
    return this.index < lhs.index;
}
*/
void Cookie::Reset()
{
    this->index.clear();
}

void Cookie::Add(const std::string &c, const int &d)
{
    this->index[c] += d;
}
    
std::string Cookie::Format()
{
    std::string output = "#+Cookies:\n";
    for (auto &i : this->index)
            output += "#|" + i.first + "++" + std::to_string(i.second) + "\n";
    return output;

}

std::string Cookie::Print(std::string &s)
{
    std::string ending = " | ";
    for (auto it = this->index.begin(); it != this->index.end();
    ++it)
    {
        if (it != std::prev(this->index.end()))
            ending = " | ";
        else
            ending = "";
        s += it->first + " x" + std::to_string(it->second) + ending;
    }
    return s;
}

Cookie::~Cookie()
{
}
