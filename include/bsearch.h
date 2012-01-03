/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    bsearch.h - bsearch() with offsets

  SOURCE
    phoenix4cpp - https://github.com/cwestin/phoenix4cpp

  LICENSE
    See ../LICENSE.txt.
 */

#pragma once

#ifndef PHOENIX4CPP_BSEARCH_H
#define PHOENIX4CPP_BSEARCH_H

#ifndef PHOENIX4CPP_CSTDDEF_H
#include <cstddef>
#define PHOENIX4CPP_CSTDDEF_H
#endif


namespace phoenix4cpp
{

/*
  bsearch() - binary search

  bsearch() searches an array for an element with a specified key using a
  binary search.  The function returns a pointer to the matching array element,
  or NULL if no match is found.  If the key appears more than once, any one of
  the matching elements may be returned.

  Unlike classic C bsearch(), this version takes an offset which is used to
  find the key within each array member.  That makes it possible to use a
  single set of comparison functions (e.g. see compare.h) for any structures
  that are to be searched by a scalar key.  Use offsetof() (or an equivalent)
  to find the value of the keyOffset parameter.

  If you have a search based on a concatenated key, you will still have to
  write your own comparison function.

  This is the vanilla bsearch() based on (void *).  For a type-safe version,
  see the templated function below.

  @param pKey pointer to the key to search for
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
void *bsearch(const void *pKey, const void *pArray, size_t n, size_t size,
	      size_t keyOffset, int (*cmp)(const void *pl, const void *pr));

/*
  bsearch() - type-safe binary search

  See the description of the type-unsafe bsearch() above.

  @params T the type of the array elements to be searched
  @params K the type of the key
  @param keyOffset offset of the key within an array element
  @param pKey pointer to the key to search for
  @param pArray pointer to base of array to be searched
  @param n number of items in array to be searched
  @param cmp comparison function used to compare keys; returns a value less
    than zero if (*pl < *pr), zero if (*pl == *pr), or a value greater than zero
    if (*pl > *pr); see compare.h for candidate functions
  @returns pointer to the array element which matches key, if found, NULL
    otherwise
*/
template<class T, class K, size_t keyOffset>
const T *bsearch(const K *pKey, const T *pArray, size_t n,
		 int (*cmp)(const K *pk1, const K *pk2));

} // namespace phoenix4cpp


/* ========================= PRIVATE IMPLEMENTATION ========================= */

namespace phoenix4cpp
{

template<class T, class K, size_t keyOffset>
inline const T *bsearch(const K *pKey, const T *pArray, size_t n,
			int (*cmp)(const K *pl, const K *pr))
{
    /*
      This inlined template function is meant to function as a macro that
      provides type safety.  The only thing that could cause a problem here
      is if the sizes of pointers vary; see test/testbsearch.cpp.
     */
    return (const T *)bsearch(
	(const void *)pKey, (const void *)pArray, n, sizeof(T),
	keyOffset, (int (*)(const void *, const void *))cmp);
}

} // namespace phoenix4cpp

#endif /* PHOENIX4CPP_BSEARCH_H */
