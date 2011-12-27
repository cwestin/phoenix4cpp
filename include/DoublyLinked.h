/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    DoublyLinked.h - Doubly-linked list class

  SOURCE
    phoenix4cpp - https://github.com/cwestin/phoenix4cpp

  LICENSE
    See ../LICENSE.txt.

  NOTES
    The membership structure is embedded in a client data structure that is to
    belong to a doubly-linked list.  Operations are then performed on the
    member structures and head of the list.  The head of the list doubles as a
    sentinel on the list.

    Templates are used, but only for type safety.  The structure is such that
    it should not cause code instantiation, other than some inlined expressions
    to do element dereferences.

    In order to use this package with gcc, you must compile with the
    -Wno-invalid-offsetof option to prevent complaints about the use of
    offsetof().  It is unknown if this is an issue with other compilers.
 */

#pragma once

#ifndef PHOENIX4CPP_DOUBLYLINKED_H
#define PHOENIX4CPP_DOUBLYLINKED_H

#ifndef PHOENIX4CPP_CSTDDEF_H
#include <cstddef>
#define PHOENIX4CPP_CSTDDEF_H
#endif

namespace phoenix4cpp
{

    /*
      This class is an implementation artifact used by both DoublyLinkedHead and
      DoublyLinkedMembership, both of which derive from this.  See those classes
      for usage.
      $$$ make Base, List, and Membership classes be members of
        DoublyLinked<element, offset>
    */
    class DoublyLinkedBase
    {
    public:
	/*
	  initialize()
	  
	  Set the element links to point to the element.  In this state, the
	  destructor can do no damage, because the linking-around operation is
	  effectively idempotent.
	*/
	void initialize();
    
	/*
	  removeLeaveDirty()

	  Fix the links in the element before and after this one to point
	  around this one.  Note that if the elementship points to itself, as
	  after initialize(), there is no net effect.  The next and previous
	  pointers are left unaltered, so destruction from this state will
	  cause another attempt at removal and could damage the surviving list.
	  A complete remove(), uses this, followed by an initialize() in order
	  to to leave the element in a safe state for anything.
	*/
	void removeLeaveDirty();

	/*
	  isValid()
	  
	  Check to see if the link's contents are correct.  Checks the next and
	  previous links to see if they point at this link.

	  @returns true if this link is valid, false otherwise
	*/
	bool isValid() const;

	void addAfter(DoublyLinkedBase *pOther);
	void addBefore(DoublyLinkedBase *pOther);

	DoublyLinkedBase *getNext(const DoublyLinkedBase *pList) const;
	DoublyLinkedBase *getPrevious(const DoublyLinkedBase *pList) const;

    private:
	DoublyLinkedBase *pNext;
	DoublyLinkedBase *pPrevious;
    };

    class DoublyLinkedMembership :
        private DoublyLinkedBase
    {
    public:
	DoublyLinkedMembership();
	~DoublyLinkedMembership();

	void remove();
    };


    template<class element, size_t offset>
    class DoublyLinkedList :
	private DoublyLinkedBase
    {
    public:
	DoublyLinkedList();
	~DoublyLinkedList();

	void append(element *pElement);
	void prepend(element *pElement);
	void remove(element *pElement);

	void addAfter(element *pNew, element *pWhich);
	void addBefore(element *pNew, element *pWhich);

	element *getFirst() const;
	element *getLast() const;
	element *getNext(const element *pElement) const;
	element *getPrevious(const element *pElement) const;

	bool isEmpty() const;

    private:
	static element *toElement(const DoublyLinkedBase *pBase);
	static DoublyLinkedBase *toBase(const element *pElement);
    };


} // namespace phoenix4cpp


/* ======================== PRIVATE IMPLEMENTATION ========================= */

namespace phoenix4cpp
{

    inline void DoublyLinkedBase::initialize()
    {
	pNext = this;
	pPrevious = this;
    }

    inline void DoublyLinkedBase::removeLeaveDirty()
    {
	pNext->pPrevious = pPrevious;
	pPrevious->pNext = pNext;
    }

    inline void DoublyLinkedBase::addAfter(DoublyLinkedBase *pOther)
    {
	// removeLeaveDirty();

	// set up my links
	pNext = pOther->pNext;
	pPrevious = pOther;

	// set up links in the preceding and following items
	pOther->pNext = this;
	pNext->pPrevious = this;
    }

    inline void DoublyLinkedBase::addBefore(DoublyLinkedBase *pOther)
    {
	// removeLeaveDirty();

	// set up my links
	pNext = pOther;
	pPrevious = pOther->pPrevious;

	// set up links in the preceding and following items
	pOther->pPrevious = this;
	pPrevious->pNext = this;
    }

    inline DoublyLinkedBase *DoublyLinkedBase::getNext(
	const DoublyLinkedBase *pList) const
    {
	return (pNext == pList ? NULL : pNext);
    }

    inline DoublyLinkedBase *DoublyLinkedBase::getPrevious(
	const DoublyLinkedBase *pList) const
    {
	return (pPrevious == pList ? NULL : pPrevious);
    }

    inline DoublyLinkedMembership::DoublyLinkedMembership()
    {
	initialize();
    }

    inline DoublyLinkedMembership::~DoublyLinkedMembership()
    {
	removeLeaveDirty();
    }

    inline void DoublyLinkedMembership::remove()
    {
	removeLeaveDirty();
	initialize();
    }


    template<class element, size_t offset>
    inline DoublyLinkedList<element, offset>::DoublyLinkedList()
    {
	initialize();
    }

    template<class element, size_t offset>
    inline DoublyLinkedList<element, offset>::~DoublyLinkedList()
    {
	element *pElement;
	while((pElement = getFirst()))
	    delete pElement;
    }

    template<class element, size_t offset>
    inline void DoublyLinkedList<element, offset>::prepend(element *pElement)
    {
	toBase(pElement)->addAfter(this);
    }

    template<class element, size_t offset>
    inline void DoublyLinkedList<element, offset>::append(element *pElement)
    {
	toBase(pElement)->addBefore(this);
    }

    template<class element, size_t offset>
    inline void DoublyLinkedList<element, offset>::remove(element *pElement)
    {
	DoublyLinkedBase *pBase = toBase(pElement);
	pBase->removeLeaveDirty();
	pBase->initialize();
    }
    
    template<class element, size_t offset>
    inline element *DoublyLinkedList<element, offset>::getFirst() const
    {
	DoublyLinkedBase *pFirst = DoublyLinkedBase::getNext(this);
	if (pFirst)
	    return toElement(pFirst);
	return NULL;
    }

    template<class element, size_t offset>
    inline element *DoublyLinkedList<element, offset>::getLast() const
    {
	DoublyLinkedBase *pLast = DoublyLinkedBase::getPrevious(this);
	if (pLast)
	    return toElement(pLast);
	return NULL;
    }

    template<class element, size_t offset>
    inline element *DoublyLinkedList<element, offset>::getNext(
	const element *pElement) const
    {
	DoublyLinkedBase *pNext = toBase(pElement)->getNext(this);
	if (pNext)
	    return toElement(pNext);
	return NULL;
    }

    template<class element, size_t offset>
    inline element *DoublyLinkedList<element, offset>::getPrevious(
	const element *pElement) const
    {
	DoublyLinkedBase *pPrevious = toBase(pElement)->getPrevious(this);
	if (pPrevious)
	    return toElement(pPrevious);
	return NULL;
    }

    template<class element, size_t offset>
    inline void DoublyLinkedList<element, offset>::addAfter(
	element *pNew, element *pWhich)
    {
	toBase(pNew)->addAfter(toBase(pWhich));
    }

    template<class element, size_t offset>
    inline void DoublyLinkedList<element, offset>::addBefore(
	element *pNew, element *pWhich)
    {
	toBase(pNew)->addBefore(toBase(pWhich));
    }

    template<class element, size_t offset>
    inline element *DoublyLinkedList<element, offset>::toElement(
	const DoublyLinkedBase *pBase)
    {
	return (element *)(((char *)pBase) - offset);
    }

    template<class element, size_t offset>
    inline DoublyLinkedBase
	*DoublyLinkedList<element, offset>::toBase(const element *pElement)
    {
	return (DoublyLinkedBase *)(((char *)pElement) + offset);
    }

} // namespace phoenix4cpp

#endif /* PHOENIX4CPP_DOUBLYLINKED_H */
