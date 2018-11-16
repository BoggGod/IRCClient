#ifndef _fileToSmsMap_H
#define _fileToSmsMap_H

#include <string>
#include <vector>
#include <map>
#include "Functions/SmsMessage.h"
#include "Functions/cleanSmsMap.h"
#include <memory>
#include <algorithm>
#include <fstream>
#include <iostream>

void fileToSmsMap(std::map<std::string, std::vector<std::shared_ptr<SmsMessage>>> &themap, std::string &fname);

#endif
