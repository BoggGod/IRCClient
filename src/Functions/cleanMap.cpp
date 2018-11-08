#include "Functions/cleanMap.h"

void cleanMap(std::map<std::string, std::string> &themap)
{
    for (std::map<std::string, std::string>::iterator itr = themap.begin();
      itr != themap.end(); ++itr)
    {
        themap.erase(itr);
    }
}
