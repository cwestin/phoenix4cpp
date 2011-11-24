/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    qsort.cpp - see ../include/qsort.h

  SOURCE
    phoenix4cpp - https://github.com/cwestin/phoenix4cpp

  LICENSE
    See ../LICENSE.txt.

  IMPLEMENTATION
    The algorithm was taken from Aho, Hopcroft, and Ullman's "Data Structures
    and Algorithsm," pp. 263-265.

    Some internal methods are declared inline to minimize the number of
    function calls.

    The internal implemenation switches from using (void *) to (char *) in order
    to avoid having to cast everywhere we need to do simple bytewise arithmetic
    on pointers.
 */

#ifndef PHOENIX4CPP_QSORT_H
#include "qsort.h"
#endif


namespace phoenix4cpp
{

static inline const char *qsortFindPivot(
    const char *pA, size_t n, size_t size, size_t keyOffset,
    int (*cmp)(const void *, const void *))
{
    const void *const pFirstKey = pA + keyOffset;
    const char *pPivot = pA + size;

    for(size_t k = n - 1; k; pPivot += size, --k)
    {
	int cmpval = (*cmp)(pPivot + keyOffset, pFirstKey);
	if (cmpval > 0)
	    return pPivot;
	else if (cmpval < 0)
	    return pA;
    }

    return NULL;
}

static inline void qsortSwapBytes(char *pl, char *pr, size_t size)
{
    for(; size; --size)
    {
        char temp = *pl;
        *pl++ = *pr;
        *pr++ = temp;
    }
}

static inline size_t qsortPartition(
    char *pA, size_t n, size_t size, const char *pPivot, size_t keyOffset,
    int (*cmp)(const void *pl, const void *pr))
{
    char *pl = pA;
    size_t l = 0;
    char *pr = pA + (n - 1)*size;
    const char *pPivotKey = pPivot + keyOffset;

    do
    {
        qsortSwapBytes(pl, pr, size);

	/*
	  On paper, the quicksort algorithm keeps track of the pivot by value;
	  because we don't know the size of the pivot, we keep a reference
	  to it.  But this means that we might move it during one of the
	  swaps above.  If we do, we need to track it's movement.
	*/
	if (pPivot == pl)
	{
	    pPivot = pr;
	    pPivotKey = pPivot + keyOffset;
	}
	else if (pPivot == pr)
	{
	    pPivot = pl;
	    pPivotKey = pPivot + keyOffset;
	}

	while((*cmp)(pl + keyOffset, pPivotKey) < 0)
	{
	    pl += size;
	    ++l;
	}

	while((*cmp)(pr + keyOffset, pPivotKey) >= 0)
	    pr -= size;

    } while(pl <= pr);

    return l;
}

void qsort(
    void *pArray, size_t n, size_t size, size_t keyOffset,
    int (*cmp)(const void *pl, const void *pr))
{
    /*
      The loop here is used for tail recursion.  The condition is the
      negation of the recursion termination condition; see the end of the
      loop body.
     */
    while(n > 1)
    {
	const char *pPivot = qsortFindPivot(
	    (char *)pArray, n, size, keyOffset, cmp);
	if (!pPivot)
	    return;

	size_t q = qsortPartition(
	    (char *)pArray, n, size, pPivot, keyOffset, cmp);
	qsort(pArray, q, size, keyOffset, cmp);

	/*
	  This would be the recursive call for the top end of the array, but we
	  use a loop to achieve tail recursion without a function call.

	  qsort(((char *)pArray) + q*size, n - q, size, keyOffset, cmp);
	 */
	pArray = ((char *)pArray) + q*size;
	n -= q;
    }
}


} // namespace phoenix4cpp
