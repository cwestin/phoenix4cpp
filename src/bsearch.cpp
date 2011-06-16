/*
 */

#include "bsearch.h"

namespace phoenix4cpp
{

void *bsearch(
    const void *pkey,       /* pointer to key itself */
    const void *pbase,      /* pointer to base of array */
    size_t n,               /* number of items in array */
    size_t size,            /* size of one array element */
    size_t keyoffset,       /* offset of the key within an array element */
    int (*cmp)(const void *pk, const void *pd)
                            /* comparison routine */
    )
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
