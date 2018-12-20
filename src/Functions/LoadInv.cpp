#include "LoadInv.h"

void LoadInv(std::map<std::string, Inventory> &themap,
const std::string &fname)
{
    cleanMap(themap);
    std::ifstream infile(fname);
    if (!infile) {
        // creating new file
    }
    std::string line;
    const std::string seperator = "#|";
    const std::string userDenom = "##";
    const std::string catDenom = "#+";
    const std::string itemDenom = "++";
    std::string user;
    Inventory inv;
    int category = 0; //(0 = none, 1 = cookie)
    while (getline(infile, line))
    {
        if (!line.empty() && (line.find(userDenom) != line.npos)) {
            eraseSubstr(line, userDenom);
            user = line;
            inv.Reset();
            category = 0;
        }
        else if (!line.empty() && (line.find(catDenom) != line.npos)) {
            std::string inp = line;
            eraseSubstr(inp, catDenom);
            if (inp == "Cookies:")
                category = 1;
            else
                category = 0;
        }
        else if (!line.empty()) {
            switch (category) {
                default: {break;}
                
                case 1: {
                    eraseSubstr(line, seperator);
                    std::string cookee = line.substr(0, line.find(itemDenom));
                    std::string quants = line.substr(line.find(itemDenom) + 2);
                    int quantd = std::stoi(quants);
                    //format lines
                    inv.Add("Cookies", cookee, quantd);
                    themap[user] = inv;
                    break;
                }
            }
        }
    }
    infile.close();
}
