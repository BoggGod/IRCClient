#ifndef _Inventory_H
#define _Inventory_H

#include <string>
#include <map>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 
#include <utility>
#include <string>
#include "Functions/Cookie.h"

class Inventory
{
public:
    Inventory();
    //bool operator<(const Inventory& lhs) const;
	~Inventory();
    void Add(const std::string &c, const std::string &i, const int &d);
    void Reset();
    std::string Format();
    std::string Print(const std::string &c);

private:
    Cookie cookies;

};

#endif

