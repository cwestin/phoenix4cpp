/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    bsearch.cpp - see ../include/bsearch.h

  SOURCE
    phoenix4cpp - https://github.com/cwestin/phoenix4cpp

  LICENSE
    See ../LICENSE.txt.

  IMPLEMENTATION
    Classic binary search, with the minor optimization that we take advantage
    of the three-valued return from the comparison function, and stop
    immediately if we get back a zero.
 */

#ifndef PHOENIX4CPP_BSEARCH_H
#include "bsearch.h"
#endif


namespace phoenix4cpp
{

void *bsearch(const void *pKey, const void *pArray, size_t n, size_t size,      
	      size_t keyOffset, int (*cmp)(const void *pl, const void *pr))
{
    size_t mid;       /* the middle array element's index */
    const char *pMid; /* a pointer to the middle array element */
    int cmpval;   /* the result of comparing the middle element with the key */

    /* keep dividing the array in half until we find a matching item */
    while(n)
    {
	mid = n / 2;
	pMid = ((const char *)pArray) + mid * size;
	cmpval = (*cmp)(pKey, (const void *)(pMid + keyOffset));

	/* do a three way comparison */
	if (!cmpval)
	    return (void *)pMid;  /* we found a match */
	if (cmpval < 0)
	    n = mid;  /* search an array one smaller than half size */
	else
	{
	    /*
	      Search an array one smaller than half the size, and starting one
	      element after the midpoint.
	    */ 
	    n -= mid + 1;
	    pArray = pMid + size;
	}
    }

    /* a matching item could not be found */
    return NULL;
}

} // namespace phoenix4cpp
