/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    testcompare.cpp - test compare.h

  SOURCE
    phoenix4cpp - https://github.com/cwestin/phoenix4cpp

  LICENSE
    See ../LICENSE.txt.

  IMPLEMENTATION
 */

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstdio>

#include "compare.h"

using namespace phoenix4cpp;

int main()
{
    const int five = 5;
    const int seven = 7;
    assert(compareInt(&five, &seven) < 0);

    const unsigned long twelve = 12;
    const unsigned long fifteen = 15;
    assert(compareUnsignedLong(&fifteen, &twelve) > 0);

    const char *pBfoo = "bfoo";
    const char *pBar = "bar";
    assert(compareCharStar(&pBfoo, &pBar) > 0);

    return 0;
}
