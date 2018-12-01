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
