/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    compare.cpp - see ../include/compare.h

  SOURCE
    phoenix4cpp - https://github.com/cwestin/phoenix4cpp

  LICENSE
    See ../LICENSE.txt.

  IMPLEMENTATION
    In order to avoid typing the text of the scalar comparisons over and over
    again, a macro is used to define the implementations for the scalar types.
 */

#include "compare.h"

#include <cstring>

namespace phoenix4cpp
{

#define PHOENIX4CPP_COMPARE_FUNC(type, typeToken) \
int compare##typeToken(const type *pl, const type *pr) \
{ \
    if (*pl < *pr) \
	return -1; \
    if (*pl == *pr) \
	return 0; \
\
    return 1; \
}

PHOENIX4CPP_COMPARE_FUNC(int, Int)
PHOENIX4CPP_COMPARE_FUNC(unsigned, Unsigned)
PHOENIX4CPP_COMPARE_FUNC(long, Long)
PHOENIX4CPP_COMPARE_FUNC(unsigned long, UnsignedLong)
PHOENIX4CPP_COMPARE_FUNC(double, Double)

int compareCharStar(const char **pl, const char **pr)
{
    return strcmp(*pl, *pr);
}

} // namespace phoenix4cpp
