#include "Functions/refMap.h"
#include "Vars.h"

using namespace Global;

void refMap()
{ 
   for (std::map<std::string, std::time_t>::iterator it=watchers.begin(); it!=watchers.end(); ++it)
    {
        if (currtime - it->second >= 43200)
            watchers.erase(it);
    }
        for (std::map<std::string, std::time_t>::iterator it=smokers.begin(); it!=smokers.end(); ++it)
    {
        if (currtime - it->second >= 43200)
            smokers.erase(it);
    }
        for (std::map<std::string, std::time_t>::iterator it=drinkers.begin(); it!=drinkers.end(); ++it)
    {
        if (currtime - it->second >= 43200)
            smokers.erase(it);
    }
    return;
}
