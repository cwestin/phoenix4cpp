/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    compare.cpp - see ../include/compare.h

  SOURCE
    phoenix4cpp - https://github.com/cwestin/phoenix4cpp

  LICENSE
    See ../LICENSE.txt.

  IMPLEMENTATION
 */

#ifndef PHOENIX4CPP_COMPARE_H
#include "compare.h"
#endif

#ifndef PHOENIX4CPP_CSTRING_H
#include <cstring>
#define PHOENIX4CPP_CSTRING_H
#endif


namespace phoenix4cpp
{

int compareCharArray(const char *pl, const char *pr)
{
    return strcmp(pl, pr);
}

int compareCharStar(const char *const *ppl, const char *const *ppr)
{
    return strcmp(*ppl, *ppr);
}

int compareInt(const int *pl, const int *pr)
{
    if (*pl < *pr)
	return -1;
    if (*pl > *pr)
	return 1;
    return 0;
}

int compareUnsigned(const unsigned *pl, const unsigned *pr)
{
    if (*pl < *pr)
	return -1;
    if (*pl > *pr)
	return 1;
    return 0;
}

int compareUnsignedLong(const unsigned long *pl, const unsigned long *pr)
{
    if (*pl < *pr)
	return -1;
    if (*pl > *pr)
	return 1;
    return 0;
}

} // namespace phoenix4cpp
