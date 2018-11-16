#ifndef _smsMapToFile_H
#define _smsMapToFile_H

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <memory>
#include "Functions/SmsMessage.h"

void smsMapToFile(std::map<std::string, std::vector<std::shared_ptr<SmsMessage>>> &themap, std::string &fname);

#endif
