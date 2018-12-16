#ifndef _Cookie_H
#define _Cookie_H

#include <unordered_map>
#include <vector>

class Cookie
{
public:
	Cookie();
   // bool operator<(const Cookie& lhs) const;
    std::string Format();
    void Add(const std::string &c, const int &d);
    std::string Print(std::string &s);
    ~Cookie();
    
private:

    std::unordered_map<std::string, int> index;
    /* Members
    double shortbread;
    double sugarCookie;
    double brownButterBurbounSpice;
    double LemonCrinkle;
    double chestnut;
    double bananaOat;
    double dcp; */
};

#endif
