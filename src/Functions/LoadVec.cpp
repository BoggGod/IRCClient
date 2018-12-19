#include "Functions/LoadVec.h"

void LoadVec(std::vector<std::string> &thevec, std::string &fname)
{
    thevec.clear();
    std::ifstream infile(fname);
    if (!infile) {
    }
    std::string line;
    while (getline(infile, line))
    {
        if (!line.empty()) {
            thevec.push_back(line);
        }
    }
    infile.close();
}
