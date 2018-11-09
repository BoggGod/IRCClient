#include "Functions/printMap.h"

void printMap(std::map<std::string, std::string> &themap, std::string &fname)
{
    std::remove(fname.c_str());
    if (!themap.empty())
    {
        std::ofstream stream(fname);
        if (!stream)
        {
            std::cout << "Couldn't open the file" << std::endl;
        }
        for (auto &kv : themap)
        {
            stream << kv.first << " " << kv.second << '\n';
        }
        stream.close();
        }
}
