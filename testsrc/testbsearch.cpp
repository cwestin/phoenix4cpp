/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    testbsearch.cpp - test bsearch.h

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

#include "bsearch.h"
#include "compare.h"

using namespace phoenix4cpp;

struct Foo
{
    int dummy;
    int value;
};

static int cmpFoo(const void *pl, const void *pr)
{
    if (((const Foo *)pl)->value < ((const Foo *)pr)->value)
	return -1;
    if (((const Foo *)pl)->value == ((const Foo *)pr)->value)
	return 0;
    return 1;
}

static bool testOnce()
{
#define A_SIZE 256
    Foo a[A_SIZE + 1];
    const size_t n = (rand() % A_SIZE) + 1;
    size_t i;

    /* populate the array */
    for(i = 0; i < n; ++i)
	a[i].value = rand() % (A_SIZE / 2);
    
    /* sort the array */
    qsort(a, n, sizeof(Foo), cmpFoo);

    /* search for every element in the array */
    for(i = 0; i < n; ++i)
    {
	const Foo *pFound =
	    bsearch<Foo, int, offsetof(Foo, value)>(&(a[i].value), a,
						    n, compare<int>);
	if (!pFound)
	    return false;
	if (pFound->value != a[i].value)
	    return false;

	const Foo *pFound2 =
	    bsearch<Foo, int, offsetof(Foo, value)>(&(a[i].value), a, n);
	if (pFound2 != pFound)
	    return false;
    }

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
	    fprintf(stderr, "%s failure iteration %u\n", __FILE__, i);
	    exit(1);
	}
    }

    /*
      Some type-matching compilation tests.  If the above passed, we
      assume the algorithm works fine, so no need to check the results here.
      This is just to make sure these compile.
    */
    unsigned u[3];
    u[0] = 17;
    u[1] = 42;
    u[2] = 2010;
    bsearch<unsigned, unsigned, 0>(&u[1], u, 3, compare<unsigned>);
    bsearch<unsigned int, unsigned int, 0>(&u[1], u, 3);

    unsigned long ul[3];
    ul[0] = 17;
    ul[1] = 42;
    ul[2] = 2010;
    bsearch<unsigned long, unsigned long, 0>(&ul[1], ul, 3);

    const char *const ps[3] = {"alpha", "bravo", "charlie"};
    bsearch<charstar, charstar, 0>(&ps[2], ps, 3);

    return 0;
}

