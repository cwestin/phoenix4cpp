/*
  Phoenix utilities
 */

#pragma once

#ifndef PHOENIX4CPP_BSEARCH_H
#define PHOENIX4CPP_BSEARCH_H

#include <cstddef>

namespace phoenix4cpp
{

    void *bsearch(
	const void *pKey,       /* pointer to key */
	const void *pBase,      /* pointer to base of array */
	size_t n,               /* number of items in array */
	size_t size,            /* size of one array element */
	size_t keyOffset,       /* offset of the key within an array element */
	int (*cmp)(const void *pk, const void *pd)
                                /* comparison routine */
	);

    template<class T, class K, size_t keyOffset>
    inline const T *bsearch(const K *pKey, const T *pArray, size_t n,
			    int (*cmp)(const K *pk1, const K *pk2))
    {
	return (const T *)bsearch(
	    (const void *)pKey, (const void *)pArray, n, sizeof(T),
	    keyOffset, cmp);
    }

};

#endif /* PHOENIX4CPP_BSEARCH_H */
