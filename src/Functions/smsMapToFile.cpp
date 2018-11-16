#include "Functions/smsMapToFile.h"

void smsMapToFile(std::map<std::string, std::vector<std::shared_ptr<SmsMessage>>> &themap, std::string &fname)
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
            stream << kv.second.front()->recipient << '\n'; 
            std::cout << kv.second.front()->recipient << std::endl;
            for (auto &v : kv.second) {
                stream << "#|" << v->sender << "#|" << v->destination
                << "#|" << v->message << "#|" << v->recipient << "#|" << v->timestamp
                << '\n';
            } 
                
        }
        stream.close();
    }
}
