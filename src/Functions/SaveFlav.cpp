#include "Functions/SaveFlav.h"

void SaveFlav(std::map<std::string, std::vector<std::string>> &themap, std::string &fname)
{
    std::remove(fname.c_str());
    if (!themap.empty())
    {
        std::ofstream stream(fname);
        if (!stream)
        {
            // creating new file
        }
        for (auto &e : themap)
        {
            stream << "#+" <<  e.first << std::endl;
            for (auto &i : e.second)
            {
                stream << i << std::endl;
            }
        }
        stream.close();
    }
}
