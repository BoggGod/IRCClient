#ifndef _Cookie_H
#define _Cookie_H

#include <map>
#include <vector>
#include <iterator>

class Cookie
{
public:
	Cookie();
   // bool operator<(const Cookie& lhs) const;
    std::string Format();
    void Add(const std::string &c, const int &d);
    std::string Print(std::string &s);
    ~Cookie();
    void Reset();
    
private:

    std::map<std::string, int> index;
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
