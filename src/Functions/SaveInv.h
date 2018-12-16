#ifndef _SaveInv_H
#define _SaveInv_H

#include <map>
#include <string>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include "Functions/Inventory.h"

void SaveInv(std::map<std::string, Inventory> &themap, std::string &fname);

#endif
