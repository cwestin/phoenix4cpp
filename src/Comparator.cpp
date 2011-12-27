/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    Comparator.cpp - see ../include/Comparator.h

  SOURCE
    phoenix4cpp - https://github.com/cwestin/phoenix4cpp

  LICENSE
    See ../LICENSE.txt.

  IMPLEMENTATION
 */

#ifndef PHOENIX4CPP_COMPARATOR_H
#include "Comparator.h"
#endif


namespace phoenix4cpp
{

    int ComparatorUnsignedLong::compare(
	const void *pLeft, const void *pRight) const
    {
	if (*(const unsigned long *)pLeft < *(const unsigned long *)pRight)
	    return -1;
	if (*(const unsigned long *)pLeft > *(const unsigned long *)pRight)
	    return 1;

	return 0;
    }

}
