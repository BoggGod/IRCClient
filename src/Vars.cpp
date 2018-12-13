#include "Vars.h"
namespace Global
{
    std::time_t lastact;
    int annoyance = 0;
    bool joinedChannel = false;
    std::string chan = "";
    const std::vector<std::string> commandList {
    "You've asked for help and help you shall receive.", 
    "-------------------------------------------------", 
    "'!' and '.' are used as command modifiers. Use either to call any command, ", 
    " "
    "For example, \".choose cats or dogs\" is a valid command.", 
    "And depending on how I feel I'll reply with either 'dog' or 'cat'.", 
    " ", 
    "I recognize the following commands as of 12/11/2018 (non-american date notation):", 
    "choose <input> or <input>", 
    "shouldi <input>", 
    "d <faces on the dice>", 
    "drinkin", 
    "smokin", 
    "watchin", 
    "setinfo", 
    "namaste", 
    "shittaste", 
    "help", 
    };
    
}
