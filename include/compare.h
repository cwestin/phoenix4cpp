/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    compare.h - comparison functions usable with bsearch(), qsort(), and
    various data structure classes

  SOURCE
    phoenix4cpp - https://github.com/cwestin/phoenix4cpp

  LICENSE
    See ../LICENSE.txt.

  NOTES
    One of the goals of this library is to only use templating in a way that
    is analogous to type erasure in Java.  This assumes that all pointers
    are the same size, and can at least go through a conversion to (void *)
    and back.
 */

#pragma once

#ifndef PHOENIX4CPP_COMPARE_H
#define PHOENIX4CPP_COMPARE_H

namespace phoenix4cpp
{

/**
  Compare two values and return a value less than zero, equal to zero,
  or greater than zero if the left value is less than the right, equal to
  the right, or greater than the right, respectively.

  @param pl pointer to left value
  @param pr pointer to right value
  @returns a value less than zero if (*pl < *pr), zero if (*pl == *pr), and
    greater than zero if (*pl > *pr).
 */
int compareCharArray(const char *pl, const char *pr);
int compareCharStar(const char *const *ppl, const char *const *ppr);
int compareInt(const int *pl, const int *pr);
int compareUnsigned(const unsigned *pl, const unsigned *pr);
int compareUnsignedLong(const unsigned long *pl, const unsigned long *pr);


} // namespace phoenix4cpp

#endif /* PHOENIX4CPP_COMPARE_H */
