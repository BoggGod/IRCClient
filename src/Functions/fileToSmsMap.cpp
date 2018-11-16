#include "fileToSmsMap.h"

void fileToSmsMap(std::map<std::string, std::vector<std::shared_ptr<SmsMessage>>> &themap, std::string &fname)
{
    cleanSmsMap(themap);
    std::ifstream infile(fname);
    if (!infile) {
        std::cout << "Couldn't open UserInfoMap for writeMap(setinfomap, filename)." << std::endl;
    }
    std::cout << "passed cleanmap and fileopening" << std::endl;
    std::string line;
    const int fileValues = 5;
    const std::string seperator = "#|";
    int valCnt = 0;
    while (getline(infile, line))
    {
        valCnt = 0;
        if ((!line.empty()) && (line.find(seperator) != line.npos)) {
            size_t sepIndex = line.at(0);
            size_t sepIndex2 = sepIndex;
            std::string output = "";
            std::vector<std::string> smsVec;
            while ((valCnt < fileValues) && (sepIndex != line.npos)) {
                sepIndex = line.find(seperator);
                sepIndex2 = line.find(seperator, sepIndex + 2);
                if (valCnt == (fileValues - 1)) {
                    output = line.substr(sepIndex + 2);
                    smsVec.push_back(output);
                    ++valCnt;
                    continue;
                } else {
                    output = line.substr(sepIndex + 2, sepIndex2 - 2);
                    output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
                }
                std::cout << output << std::endl;
                smsVec.push_back(output);
                sepIndex = sepIndex2;
                line = line.substr(sepIndex);
                ++valCnt;
            }
            if (smsVec.size() != fileValues) {
                std::cout << "Elements in file doesn't match elements required"
                << " by the program" << std::endl;
                std::cout << "Elements: " << smsVec.size() << std::endl;
            } else {
            std::cout << "Creating messages" << std::endl;
            std::shared_ptr<SmsMessage> letter = std::make_shared<SmsMessage> 
            (smsVec.at(0), smsVec.at(1), smsVec.at(2), smsVec.at(3), smsVec.at(4));
            themap[smsVec.at(3)] = {letter};
            }
         }
    }   
    infile.close();
}
