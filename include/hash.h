/* Copyright (c) 2012 Chris Westin.  All Rights Reserved. */
/*
  NAME
    hash.h - hash functions usable with HashMap and other data structure
    classes
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

#ifndef PHOENIX4CPP_HASH_H
#define PHOENIX4CPP_HASH_H

namespace phoenix4cpp
{
class HashValue;

void hashUnsignedLong(HashValue *pHashValue, const unsigned long *pul);

} // namespace phoenix4cpp

#endif /* PHOENIX4CPP_COMPARE_H */
