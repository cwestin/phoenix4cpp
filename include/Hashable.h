/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    Hashable.h - interface for objects that support computing hash values
    
    Typically implemented by keys that go in data structures

    This package also contains a few utility classes that make it convenient
    to hash local values in preparation for a lookup in classes such as the
    HashMap.

  SOURCE
    phoenix4cpp - https://github.com/cwestin/phoenix4cpp

  LICENSE
    See ../LICENSE.txt.

  NOTES
    Templated functions are used to cover scalars.
 */

#pragma once

#ifndef PHOENIX4CPP_HASHABLE_H
#define PHOENIX4CPP_HASHABLE_H

namespace phoenix4cpp
{
    class HashValue;

    class Hashable
    {
    public:
	virtual ~Hashable() {};

	/*
	  Hash this.

	  @param pHashValue a hash value accumulator
	 */
	virtual void hash(HashValue *pHashValue) const = 0;

	/*
	  Get a raw pointer to the value being hashed.

	  Useful for external Comparators.

	  @returns pointer to the raw value
	*/
	virtual const void *getRawPointer() const = 0;
    };

    /*
      Convenient utility for hashing a string.

      This class is meant to be used locally, and does not make a copy of the
      string, but depends on the string outlasting the class.
     */
    class HashableString :
        public Hashable
    {
    public:
	// virtuals from Hashable
	virtual void hash(HashValue *pHashValue) const;
	virtual const void *getRawPointer() const;

	/*
	  Hold a string pointer for hashing

	  The string must outlive this object.

	  @param pS pointer to the string to be hashed
	 */
	HashableString(const char *pS);

    private:
	const char *pS;
    };

    /*
      Convenient utility for hashing an unsigned long.
     */
    class HashableUnsignedLong :
        public Hashable
    {
    public:
	// virtuals from Hashable
	virtual void hash(HashValue *pHashValue) const;
	virtual const void *getRawPointer() const;

	/*
	  Copy an unsigned long for hashing

	  @param ul the value to be hashed
	 */
	HashableUnsignedLong(unsigned long ul);

    private:
	unsigned long ul;
    };

}


/* ======================== PRIVATE IMPLEMENTATION ========================== */

namespace phoenix4cpp
{

    inline HashableString::HashableString(const char *pString):
	pS(pString)
    {
    }

    inline HashableUnsignedLong::HashableUnsignedLong(unsigned long x):
	ul(x)
    {
    }

}

#endif
