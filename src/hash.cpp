/* Copyright (c) 2012 Chris Westin.  All Rights Reserved. */
/*
  NAME
    hash.cpp - see ../include/hash.h

  SOURCE
    phoenix4cpp - https://github.com/cwestin/phoenix4cpp

  LICENSE
    See ../LICENSE.txt.

  IMPLEMENTATION
 */

#ifndef PHOENIX4CPP_HASH_H
#include "hash.h"
#endif


#ifndef PHOENIX4CPP_CSTRING_H
#include <cstring>
#define PHOENIX4CPP_CSTRING_H
#endif

#ifndef PHOENIX4CPP_HASHVALUE_H
#include <HashValue.h>
#endif


namespace phoenix4cpp
{

    void hashUnsignedLong(HashValue *pHashValue, const unsigned long *p)
    {
	pHashValue->blend(p, sizeof(*p));
    }

} // namespace phoenix4cpp
