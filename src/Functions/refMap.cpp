#include "Functions/refMap.h"
#include "Vars.h"
#include <iostream>

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
            drinkers.erase(it);
    }
    for (std::map<std::string, std::time_t>::iterator
        it=poopers.begin(); it!=poopers.end(); ++it)
    {
        if (currtime - it->second >= 43200)
            poopers.erase(it);
    }
    for (std::map<std::string, std::time_t>::iterator
    it=bikers.begin(); it!=bikers.end(); ++it)
    {
        if (currtime - it->second >= 43200)
            bikers.erase(it);
    }
    for (std::map<std::string, std::time_t>::iterator
    it=sleepers.begin(); it!=sleepers.end(); ++it)
    {
        if (currtime - it->second >= 43200)
            sleepers.erase(it);
    }
    for (std::map<std::string, std::time_t>::iterator
    it=gamers.begin(); it!=gamers.end(); ++it)
    {
        if (currtime - it->second >= 43200)
            gamers.erase(it);
    }
    for (std::map<std::string, std::time_t>::iterator
    it=listeners.begin(); it!=listeners.end(); ++it)
    {
        if (currtime - it->second >= 43200)
            listeners.erase(it);
    }
    for (std::map<std::string, std::time_t>::iterator
    it=readers.begin(); it!=readers.end(); ++it)
    {
        if (currtime - it->second >= 43200)
            readers.erase(it);
    }
    
    return;
}
