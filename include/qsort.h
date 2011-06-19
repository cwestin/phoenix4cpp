/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    qsort.h - qsort() with offsets

  SOURCE
    phoenix4cpp - https://github.com/cwestin/phoenix4cpp

  LICENSE
    See ../LICENSE.txt.
 */

#pragma once

#ifndef PHOENIX4CPP_QSORT_H
#define PHOENIX4CPP_QSORT_H

#include <cstddef>

namespace phoenix4cpp
{

/*
  qsort() - quicksort

  qsort() sorts an array using the quicksort algorithm.

  Unlike classic C qsort(), this version takes an offset which is used to
  find the key within each array member.  That makes it possible to use a
  single set of comparison functions (e.g. see compare.h) for any structures
  that are to be searched by a scalar key.  Use offsetof() (or an equivalent)
  to find the value of the keyOffset parameter.

  If you need to sort based on a concatenated key, you will still have to
  write your own comparison function.

  This is the vanilla qsort() based on (void *).  For a type-safe version,
  see the templated function below.

  @param pArray pointer to base of array to be searched
  @param n number of items in array to be searched
  @param size size of an array element
  @param keyOffset offset of the key within an array element
  @param cmp comparison function used to compare keys; returns a value less
    than zero if (*pl < *pr), zero if (*pl == *pr), or a value greater than zero
    if (*pl > *pr); see compare.h for candidate functions
  @returns pointer to the array element which matches key, if found, NULL
    otherwise
*/
void qsort(void *pArray, size_t n, size_t size, size_t keyOffset,
	   int (*cmp)(const void *pl, const void *pr));

/*
  qsort() - type-safe quicksort

  See the description of the type-unsafe qsort() above.

  @params T the type of the array elements to be searched
  @params K the type of the key
  @param keyOffset offset of the key within an array element
  @param pArray pointer to base of array to be searched
  @param n number of items in array to be searched
  @param cmp comparison function used to compare keys; returns a value less
    than zero if (*pl < *pr), zero if (*pl == *pr), or a value greater than zero
    if (*pl > *pr); see compare.h for candidate functions
  @returns pointer to the array element which matches key, if found, NULL
    otherwise
*/
template<class T, class K, size_t keyOffset>
void qsort(T *pArray, size_t n, int (*cmp)(const K *pl, const K *pr));

} // namespace phoenix4cpp


/* ========================= PRIVATE IMPLEMENTATION ========================= */

namespace phoenix4cpp
{

template<class T, class K, size_t keyOffset>
inline void qsort(T *pArray, size_t n, int (*cmp)(const K *pl, const K *pr))
{
    /*
      This inlined template function is meant to function as a macro that
      provides type safety.  The only thing that could cause a problem here
      is if the sizes of pointers vary; see test/testqsort.cpp.
     */
    qsort((void *)pArray, n, sizeof(T), keyOffset,
	  (int (*)(const void *, const void *))cmp);
}

} // namespace phoenix4cpp

#endif /* PHOENIX4CPP_QSORT_H */
