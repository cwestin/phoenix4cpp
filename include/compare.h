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
    Templated functions are used to cover scalars.
 */

#pragma once

#ifndef PHOENIX4CPP_COMPARE_H
#define PHOENIX4CPP_COMPARE_H

namespace phoenix4cpp
{

/*
  compare<> - compare two values

  Template specializations below cover compare<char> as an embedded string, and
  compare<charstar> as a pointer to a string.

  @param pl pointer to left value
  @param pr pointer to right value
  @returns a value less than zero if (*pl < *pr), zero if (*pl == *pr), and
    greater than zero if (*pl > *pr).
 */
template<class T>
int compare(const T *pl, const T *pr)
{
    if (*pl < *pr)
	return -1;
    if (*pl == *pr)
	return 0;

    return 1;
}

/*
  compareReverse<> - compare two values, reversed

  Same as compare<>, but useful for situations where items are sorted in a
  descending order.

  @param pl pointer to left value
  @param pr pointer to right value
  @returns a value greater than zero if (*pl < *pr), zero if (*pl == *pr), and
    less than zero if (*pl > *pr).
*/
template<class T>
int compareReverse(const T *pl, const T *pr)
{
    return -1*compare<T>(pl, pr);
}


/* --------------------- template specializations -------------------------- */

template<>
int compare<char>(const char *pl, const char *pr);

#ifdef NEVER
/*
  Unfortunately, this template specialization doesn't match as you would
  expect, so we have to use the typedef for the one below for pointers to
  strings.
 */
template<>
int compare<char *>(const char **pl, const char **pr)
{
    return strcmp(*pl, *pr);
}
#endif


typedef const char *charstar;

template<>
int compare<charstar>(const charstar *pl, const charstar *pr);

} // namespace phoenix4cpp

#endif /* PHOENIX4CPP_COMPARE_H */
