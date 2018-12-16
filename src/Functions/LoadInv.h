#ifndef _LoadInv_H
#define _LoadInv_H

#include <string>
#include "Functions/Inventory.h"
#include "Functions/Cookie.h"
#include "Functions/cleanMap.h"
#include "Functions/general.h"
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <fstream>
#include <iostream>


void LoadInv(std::map<std::string, Inventory> &themap,
const std::string &fname);

#endif

