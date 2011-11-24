/* Copyright (c) 2002 by Chris Westin.  All rights reserved. */
/*
	NAME
        pxlibDoublyLinked.cpp - Intrusive doubly linked list

	NOTES

	    Part of The Phoenix Library, from The Book of Brilliant Things
	    http://www.speakeasy.org/~cwestin/bobt

	PERFORCE
	    $Id: //depot/pxlib/src/pxlibDoublyLinked.cpp#1 $
	    $Author: Chris $ $DateTime: 2003/10/25 11:32:52 $
	
	HISTORY
        09/28/03 - cwestin - created
  */

#ifndef PHOENIX4CPP_DOUBLYLINKED_H
#include <DoublyLinked.h>
#endif

namespace phoenix4cpp
{

    bool DoublyLinkedBase::isValid() const
    {
	if (pNext->pPrevious != this)
	    return false;
	if (pPrevious->pNext != this)
	    return false;

	return true;
    }

} // namespace phoenix4cpp
