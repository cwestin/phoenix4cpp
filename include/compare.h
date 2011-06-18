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
    Each comparison function here takes the form

      int compareT(const T *pl, const T *pr);

    All of these functions return a value less than zero if (*pl < *pr), zero
    if (*pl == *pr), and greater than zero if (*pl > *pr).

    Because these are all the same except for the types of their arguments,
    they are not documented individually below.

    Note that for embedded strings, strcmp() already has the correct signature
    to use.  For pointers to strings, use compareCharStar().
 */

#pragma once

#ifndef PHOENIX4CPP_COMPARE_H
#define PHOENIX4CPP_COMPARE_H

namespace phoenix4cpp
{

int compareInt(const int *pl, const int *pr);
int compareUnsigned(const unsigned *pl, const unsigned *pr);
int compareLong(const long *pl, const long *pr);
int compareUnsignedLong(const unsigned long *pl, const unsigned long *pr);
int compareDouble(const double *pl, const double *pr);
int compareCharStar(const char **pl, const char **pr);

} // namespace phoenix4cpp


#endif /* PHOENIX4CPP_COMPARE_H */
