#include "Functions/writeMap.h"

void writeMap(std::map<std::string, std::string> &themap, std::string &fname)
{
    cleanMap(themap);
    std::ifstream infile(fname);
    if (!infile) {
        std::cout << "Couldn't open file to read from" << std::endl;
        std::cout << "Creating new file" << std::endl;
    }
    std::string line;
    while (getline(infile, line))
    {
        if (!line.empty()) {
            std::string key = line.substr(0, line.find(" "));
            std::string value = line.substr(line.find(" ") + 1);
            themap.insert(std::pair<std::string, std::string>(key, value));
        }
    }
    infile.close();
}
