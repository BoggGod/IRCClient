#include "Functions/writeMap.h"

void writeMap(std::map<std::string, std::string> &themap, std::string &fname)
{
    cleanMap(themap);
    std::ifstream infile(fname);
    if (!infile) {
        std::cout << "couldn't open file" << std::endl;
    }
    std::string line;
    while (getline(infile, line))
    {
        if (!line.empty()) {
            std::string key = line.substr(0, line.find(" ") - 1);
            std::string value = line.substr(line.find(" ") + 1);
            themap.insert(std::pair<std::string, std::string>(key, value));
        }
    }
    infile.close();
}
