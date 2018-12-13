#include "Functions/general.h"

// trim from start (in place)
void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
}));
}

// trim from end (in place)
void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}
/*
void rtrim(std::string &s) {
    s.erase(s.rbegin(), std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }));
}
*/

void eraseSubstr(std::string &str, const std::string &toErase)
{
    size_t pos = std::string::npos;
    while ((pos = str.find(toErase)) != std::string::npos)
    {
        str.erase(pos, toErase.length());
    }
}


bool isNumber(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

bool stringSort(const std::string& lhs, const std::string &rhs)
{
    size_t sz = rhs > lhs ? lhs.size() : rhs.size();
    for (size_t i  = 0; i < sz; ++i)
    {
        if (std::tolower(lhs[i]) < std::tolower(rhs[i]))
            return true;
        else if (std::tolower(lhs[i]) > std::tolower(rhs[i]))
            return false;
    }
    return true; //totally unneeded
}
