#ifndef _LoadFlav_H
#define _LoadFlav_H

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


void LoadFlav(std::map<std::string, std::vector<std::string>> &themap,
const std::string &fname);

#endif

