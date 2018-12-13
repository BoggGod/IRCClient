#ifndef _general_H
#define _general_H

#include <algorithm> 
#include <cctype>
#include <locale>
#include <string>

void ltrim(std::string &s);
void rtrim(std::string &s);
void eraseSubstr(std::string &str, const std::string &toErase);
bool isNumber(const std::string& s);
bool stringSort(const std::string& lhs, const std::string &rhs);

#endif
