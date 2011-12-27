/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    Comparator.h - interface for comparing two objects
    
    Typically implemented by keys that go in data structures

    This package also contains a few utility classes that for comparing
    scalar types.

  SOURCE
    phoenix4cpp - https://github.com/cwestin/phoenix4cpp

  LICENSE
    See ../LICENSE.txt.

  NOTES
 */

#pragma once

#ifndef PHOENIX4CPP_COMPARATOR_H
#define PHOENIX4CPP_COMPARATOR_H

namespace phoenix4cpp
{

    class Comparator
    {
    public:
	virtual ~Comparator() {};
	virtual int compare(const void *pLeft, const void *pRight) const = 0;
    };

    class ComparatorUnsignedLong :
        public Comparator
    {
    public:
	// virtuals from Comparator
	virtual int compare(const void *pLeft, const void *pRight) const;
    };
}

#endif
