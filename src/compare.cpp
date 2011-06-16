

#include "compare.h"

namespace phoenix4cpp
{

    int compareInt(const int *p1, const int *p2)
    {
	if (*p1 < *p2)
	    return -1;
	if (*p1 == *p2)
	    return 0;

	return 1;
    }

};
