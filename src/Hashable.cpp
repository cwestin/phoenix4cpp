/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    Hashable.cpp - see ../include/Hashable.h

  SOURCE
    phoenix4cpp - https://github.com/cwestin/phoenix4cpp

  LICENSE
    See ../LICENSE.txt.

  IMPLEMENTATION
 */

#ifndef PHOENIX4CPP_HASHABLE_H
#include "Hashable.h"
#endif

#ifndef PHOENIX4CPP_HASHAVLUE_H
#include "HashValue.h"
#endif


namespace phoenix4cpp
{
    void HashableString::hash(HashValue *pHashValue) const
    {
	pHashValue->blend(pS);
    }

    const void *HashableString::getRawPointer() const
    {
	return (const void *)&pS;
    }

    void HashableUnsignedLong::hash(HashValue *pHashValue) const
    {
	pHashValue->blend(ul);
    }

    const void *HashableUnsignedLong::getRawPointer() const
    {
	return (const void *)&ul;
    }
}
