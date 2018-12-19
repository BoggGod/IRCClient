#include "Functions/SaveVec.h"

void SaveVec(std::vector<std::string> &thevec, std::string &fname)
{
    std::remove(fname.c_str());
    if (!thevec.empty())
    {
        std::ofstream stream(fname);
        if (!stream)
        {
            // new file
        }
        for (auto &kv : thevec)
        {
            stream << kv << '\n';
        }
        stream.close();
        }
}
