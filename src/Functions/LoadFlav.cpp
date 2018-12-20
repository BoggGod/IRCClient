#include "LoadFlav.h"

void LoadFlav(std::map<std::string, std::vector<std::string>> &themap,
const std::string &fname)
{
    cleanMap(themap);
    std::ifstream infile(fname);
    if (!infile) {
            // creating new file;
    }
    std::string line;
    const std::string catDenom = "#+";
    const std::string itemDenom = "++";
    std::string category;
    while (getline(infile, line))
    {
        if (!line.empty() && (line.find(catDenom) != line.npos)) {
            eraseSubstr(line, catDenom);
            category = line;
        } else if (!line.empty()) {
            themap[category].push_back(line);
        }
    }
    infile.close();
}
