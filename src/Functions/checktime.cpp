#include "Functions/refMap.h"
#include "Functions/checktime.h"

using namespace Global;

void checktime(/* void */)
{
    currtime = std::time(nullptr);
    if (currtime - daystart >= 86400)
        daystart = currtime;
    if (currtime - sixhcycle >= 43200) //43200
    {
        sixhcycle = currtime;
        refMap();
    }
    return;
}
