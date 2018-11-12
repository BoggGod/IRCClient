#include "Vars.h"
namespace Global
{
	std::map<std::string, std::string> setinfos;
    std::string setinfoFile = "UserInfoMap";
    std::map<std::string, std::time_t> smokers;
    std::map<std::string, std::time_t> chefs;
    std::map<std::string, std::time_t> drinkers;
    std::map<std::string, std::time_t> poppers;
    std::map<std::string, std::time_t> watchers;
    std::map<std::string, std::time_t> listeners;
    std::time_t lastact;
    std::time_t currtime;
    std::time_t daystart;
    std::time_t sixhcycle;
    int annoyance = 0;
    bool joinedChannel = false;
    std::string chan = "";
}
