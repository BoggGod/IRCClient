#include "Functions/cleanSmsMap.h"

void cleanSmsMap(std::map<std::string, std::vector<std::shared_ptr<SmsMessage>>> &themap)
{
    for (std::map<std::string, std::vector<std::shared_ptr<SmsMessage>>>::iterator itr = themap.begin();
      itr != themap.end(); ++itr)
    {
        themap.erase(itr);
    }
}
