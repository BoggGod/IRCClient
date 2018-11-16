#ifndef _cleanSmsMap_H
#define _cleanSmsMap_H

#include <map>
#include <string>
#include <iterator>
#include <vector>
#include <memory>
#include "Functions/SmsMessage.h"

void cleanSmsMap(std::map<std::string, std::vector<std::shared_ptr
<SmsMessage>>> &themap);

#endif
