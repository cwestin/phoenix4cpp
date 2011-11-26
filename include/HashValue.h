/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    HashValue - utility class for computing hash values
    
    Often used with the Hashable interface

  SOURCE
    phoenix4cpp - https://github.com/cwestin/phoenix4cpp

  LICENSE
    See ../LICENSE.txt.

  NOTES
    Unlike Java's Object.hashCode(), this is formulated in such a way that it
    is easy to combine values for concatenated keys; the HashValue provides
    methods for blending in data.  Those methods can be used any number of times
    on a single HashValue to compute a hash for a composite.
 */

#pragma once

#ifndef PHOENIX4CPP_HASHVALUE_H
#define PHOENIX4CPP_HASHVALUE_H

namespace phoenix4cpp
{

    class HashValue
    {
    public:
	HashValue();

	unsigned long get() const;

	/*
	  Blend the given value into the accumulated hash value.

	  @param v the value to blend in
	 */
	void blend(short v);
	void blend(unsigned long v);

	/*
	  Blend the string into the accumulated hash value.

	  @param pS pointer to the null-terminated string to blend in
	 */
	void blend(const char *pS);

    private:
	static const unsigned long byteTable[256];

	void rotate();

	unsigned long value;
    };

}

/* ========================== PRIVATE IMPLEMENTATION ======================== */

namespace phoenix4cpp
{

    inline HashValue::HashValue():
	value(0x5a3c96e7) /* non-zero seed value for hash values */
    {
    }

    inline unsigned long HashValue::get() const
    {
	return value;
    }

}

#endif
