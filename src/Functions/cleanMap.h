#ifndef _cleanMap_H
#define _cleanMap_H

#include <map>
#include <string>
#include <iterator>
#include "Functions/Inventory.h"
#include <vector>

void cleanMap(std::map<std::string, std::string> &themap);
void cleanMap(std::map<std::string, Inventory> &themap);
void cleanMap(std::map<std::string, std::vector<std::string>> &themap);
#endif
