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
            stream << kv.first << "hi " << kv.second << '\n';
            std::cout << "kv.first = " << kv.first << " and kv.second = " << kv.second << std::endl;
        }
        std::cout << "Copied map to file" << std::endl;
        stream.close();
    }
}
