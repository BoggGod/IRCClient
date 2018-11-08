#ifndef _writeMap_H
#define _writeMap_H

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Functions/cleanMap.h"

void writeMap(std::map<std::string, std::string> &themap, std::string &fname);

#endif
