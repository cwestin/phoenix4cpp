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

template<>
int compare<char>(const char *pl, const char *pr)
{
    return strcmp(pl, pr);
}

template<>
int compare<charstar>(const charstar *pl, const charstar *pr)
{
    return strcmp(*pl, *pr);
}

} // namespace phoenix4cpp
