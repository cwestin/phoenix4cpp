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

#include "bsearch.h"

namespace phoenix4cpp
{

void *bsearch(const void *pkey, const void *pbase, size_t n, size_t size,      
	      size_t keyoffset, int (*cmp)(const void *pl, const void *pr))
{
    size_t mid;       /* the middle array element's index */
    const char *pmid; /* a pointer to the middle array element */
    int cmpval;   /* the result of comparing the middle element with the key */

    /* keep dividing the array in half until we find a matching item */
    while(n)
    {
	mid = n / 2;
	pmid = ((const char *)pbase) + mid * size;
	cmpval = (*cmp)(pkey, (const void *)(pmid + keyoffset));

	/* do a three way comparison */
	if (!cmpval)
	    return (void *)pmid;  /* we found a match */
	if (cmpval < 0)
	    n = mid;  /* search an array one smaller than half size */
	else
	{
	    /*
	      Search an array one smaller than half the size, and starting one
	      element after the midpoint.
	    */ 
	    n -= mid + 1;
	    pbase = pmid + size;
	}
    }

    /* a matching item could not be found */
    return NULL;
}

} // namespace phoenix4cpp
