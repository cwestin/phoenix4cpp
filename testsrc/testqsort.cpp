/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    testqsort.cpp - test qsort.h

  SOURCE
    phoenix4cpp - https://github.com/cwestin/phoenix4cpp

  LICENSE
    See ../LICENSE.txt.

  IMPLEMENTATION
 */

#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>

#include "qsort.h"
#include "compare.h"

using namespace phoenix4cpp;

struct Foo
{
    int dummy;
    int value;
};

static bool sortCheck(const void *pA, size_t n, size_t size, size_t keyOffset,
		      int (*cmp)(const void *pl, const void *pr))
{
    const char *pLast = ((const char *)pA) + keyOffset;
    const char *pNext;
    for(size_t i = n - 1; i; pLast = pNext, --i)
    {
	pNext = pLast + size;
	int cmpval = (*cmp)(pLast, pNext);
	if (cmpval > 0)
	    return false;
    }

    return true;
}

static bool testOnce()
{
#define A_SIZE 256
    Foo a[A_SIZE + 1];
    Foo b[A_SIZE + 1];
    const size_t n = (rand() % A_SIZE) + 1;

    /* populate the arrays */
    for(size_t i = 0; i < n; ++i)
    {
	a[i].value = rand() % (A_SIZE / 2);
	b[i].value = a[i].value;
    }
    
    /* sort the arrays */
    qsort(a, n, sizeof(Foo), offsetof(Foo, value),
	  (int (*)(const void *, const void *))compareInt);
    qsort<Foo, int, offsetof(Foo, value)>(b, n, compareInt);

    /* check that the arrays are sorted */
    if (!sortCheck(a, n, sizeof(Foo), offsetof(Foo, value),
		   (int (*)(const void *, const void *))compareInt))
	return false;
    if (!sortCheck(b, n, sizeof(Foo), offsetof(Foo, value),
		   (int (*)(const void *, const void *))compareInt))
	return false;

    return true;
}

int main()
{
    /*
      The templated version of this function cases the comparision function
      so that it will match the generic signature used by the untemplated
      bsearch() function.  This will cause problems if the size of pointers
      varies, because we expect to treat a pointer to any comparison key
      the same way (as a (void *)).  We'll check here that this is ok.
     */
    assert(sizeof(char *) == sizeof(void *));
    assert(sizeof(int *) == sizeof(void *));
    assert(sizeof(long *) == sizeof(void *));
    assert(sizeof(double *) == sizeof(void *));
    assert(sizeof(Foo *) == sizeof(void *));

    /* seed the random number generator so we get repeatable runs */
    srand(0xdeadbeef);

    for(unsigned i = 0; i < 10000; ++i)
    {
	if (!testOnce())
	{
	    fprintf(stdout, "%s failure iteration %u\n", __FILE__, i);
	    fflush(stdout);
	    exit(1);
	}
    }

    return 0;
}

