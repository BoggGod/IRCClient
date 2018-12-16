#include "Functions/SaveInv.h"

void SaveInv(std::map<std::string, Inventory> &themap, std::string &fname)
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
            stream << "##" <<  e.first << std::endl;
            stream << e.second.Format() << std::endl;
        }
        stream.close();
    }
}
