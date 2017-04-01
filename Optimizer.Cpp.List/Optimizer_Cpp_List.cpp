#include <iostream>
#include "Optimizer_Cpp_List.h"
using namespace opti::DS;

template < typename T >
template < class P >
void List<T>::Merge(List<T>& y, P& p)
{
	if (this == &y) return;
	Link * xcurr = _head->_next;   // x = this list
	Link * ycurr = y._head->_next; // y = that list

								   // merge while both lists are not empty
	while (xcurr != _tail && ycurr != y._tail)
	{
		if (p(ycurr->Tval_, xcurr->Tval_)) // y < x
		{
			ycurr = ycurr->_next;
			LinkIn(xcurr, ycurr->_prev);
		}
		else // x <= y
		{
			xcurr = xcurr->_next;
		}
	}

	// splice in remainder of y
	if (ycurr != y._tail)
	{
		_tail->_prev->_next = ycurr;
		ycurr->_prev = _tail->_prev;
		_tail->_prev = (y._tail)->_prev;
		(y._tail)->_prev->_next = _tail;
	}

	// make y structurally correct for empty
	(y._head)->_next = y._tail;
	(y._tail)->_prev = y._head;
}

template < typename T >
void List<T>::Merge(List<T>& y)
{
	if (this == &y) return;
	Link * xcurr = _head->_next;   // x = this list
	Link * ycurr = y._head->_next; // y = that list

								   // merge while both lists are not empty
	while (xcurr != _tail && ycurr != y._tail)
	{
		if (ycurr->Tval_ < xcurr->Tval_) // y < x
		{
			ycurr = ycurr->_next;
			LinkIn(xcurr, ycurr->_prev);
		}
		else // x <= y
		{
			xcurr = xcurr->_next;
		}
	}

	// splice in remainder of y
	if (ycurr != y._tail)
	{
		_tail->_prev->_next = ycurr;
		ycurr->_prev = _tail->_prev;
		_tail->_prev = (y._tail)->_prev;
		(y._tail)->_prev->_next = _tail;
	}

	// make y structurally correct for empty
	(y._head)->_next = y._tail;
	(y._tail)->_prev = y._head;
}

template < typename T >
void List<T>::Reverse()
{
	if (!this->Empty())
	{
		Link * link = this->_tail->_prev;
		Link * temp = link->_prev;
		if (temp != this->_head)
		{
			this->_tail->_prev = this->_head->_next;
			this->_head->_next = link;
			link->_prev = this->_head;
			link->_next = temp;
			link = temp;
			temp = temp->_prev;
			while (temp != this->_head)
			{
				link->_prev = link->_next;
				link->_next = temp;
				temp = temp->_prev;
				link = link->_next;
			} // while loop 
			link->_prev = link->_next;
			link->_next = this->_tail;

		} // inner if 
	} // if
}//Reverse ()


 // stand-alone functions

template < typename T >
bool operator == (const List<T>& x1, const List<T>& x2)
{
	typename List<T>::ConstIterator i1, i2;
	for (
		i1 = x1.Begin(), i2 = x2.Begin();
		(i1 != x1.End()) && (i2 != x2.End());
		++i1, ++i2
		)
	{
		if (*(i1) != *(i2))
			return 0;
	}
	if (i1 != x1.End() || i2 != x2.End())
		return 0;
	return 1;
}

template < typename T >
bool operator != (const List<T>& x1, const List<T>& x2)
{
	return !(x1 == x2);
}

template < typename T >
std::ostream& operator << (std::ostream& os, const List<T>& x2)
{
	x2.Display(os);
	return os;
}

// end stand-alone functions */

// memory allocator and other private methods

template < typename T >
List<T>::Link::Link(const T& Tval) : Tval_(Tval), _prev(nullptr), _next(nullptr)
{}

template < typename T >
typename List<T>::Link* List<T>::NewLink(const T& t)
{
	Link * newLink = new(std::nothrow) Link(t);
	if (nullptr == newLink)
	{
		// exception handler
		std::cerr << "** List error: memory allocation failure\n";
		return nullptr;
	}
	return newLink;
}

template < typename T >
void List<T>::LinkIn(typename List<T>::Link * location, typename List<T>::Link * newLink)
{
	if (location == nullptr || newLink == nullptr) return;
	else
	{
		newLink->_prev = location->_prev;
		location->_prev->_next = newLink;
		newLink->_next = location;
		location->_prev = newLink;
	}
}

template < typename T >
typename List<T>::Link* List<T>::LinkOut(typename List<T>::Link * oldLink)
{
	oldLink->_prev->_next = oldLink->_next;
	oldLink->_next->_prev = oldLink->_prev;

	return oldLink;
}

template < typename T >
void List<T>::Init()
{
	_head = NewLink(T());
	_tail = NewLink(T());
	_head->_next = _tail;
	_tail->_prev = _head;
}

template < typename T >
void List<T>::Append(const List<T>& list)
{
	for (ConstIterator i = list.Begin(); i != list.End(); ++i)
		PushBack(*i);
}

// end private methods */

// constructors and assignment

template < typename T >
List<T>::List() : _head(nullptr), _tail(nullptr)
{
	Init();
}

template < typename T >
List<T>::List(const List<T>& x) : _head(nullptr), _tail(nullptr)
{
	Init();
	Append(x);
}

template < typename T >
List<T>::~List()
{
	Clear();
	delete _head;
	delete _tail;
}

template < typename T >
List<T>& List<T>::operator = (const List<T>& rhs)
{
	if (this != &rhs)   // it would be a disaster to assign to self!
	{
		// First, destroy the existing list.
		Clear();
		// then build a copy as *this
		Append(rhs);
	}
	return *this;
}

template < typename T >
List<T>& List<T>::operator += (const List<T>& list)
// append operator
{
	if (this != &list)
		Append(list);
	return *this;
}

template < typename T >
bool List<T>::PushFront(const T& t)
// Insert t at the front (first) position.
{
	Link* newLink = NewLink(t);
	if (newLink == nullptr) return 0;
	LinkIn(_head->_next, newLink);
	return 1;
}

template < typename T >
bool List<T>::PushBack(const T& t)
// Insert t at the back (last) position.
{
	Link* newLink = NewLink(t);
	if (newLink == nullptr) return 0;
	LinkIn(_tail, newLink);
	return 1;
}

template < typename T >
ListIterator<T> List<T>::Insert(ListIterator<T> i, const T& t)
// Insert t at (in front of) i; return i at new element
{
	if (Empty())  // always insert
	{
		i = End();
	}
	if (!i.Valid() || i == rEnd()) // null or off-the-front
	{
		std::cerr << " ** cannot insert at position -1\n";
		return End();
	}
	Link* newLink = NewLink(t);
	if (newLink == nullptr) return End();
	LinkIn(i._current, newLink);
	// leave i at new entry and return
	i._current = newLink;
	return i;
}

template < typename T >
ListIterator<T> List<T>::Insert(const T& t)
// Insert t at default location (back)
{
	return Insert(End(), t);
}

template < typename T >
bool List<T>::PopFront()
{
	if (Empty())
	{
		std::cerr << "** List error: PopFront() called on empty list\n";
		return 0;
	}
	Link * oldLink = LinkOut(_head->_next);
	delete oldLink;
	return 1;
} // end PopFront()

template < typename T >
bool List<T>::PopBack()
{
	if (Empty())
	{
		std::cerr << "** List error: PopBack() called on empty list\n";
		return 0;
	}
	Link* oldLink = LinkOut(_tail->_prev);
	delete oldLink;
	return 1;
} // end PopBack()

template < typename T >
ListIterator<T> List<T>::Remove(Iterator i)
// Remove item at i
{
	// first deal with the impossible cases
	if (i._current == nullptr || i._current == _head || i._current == _tail)
	{
		std::cerr << "** List error: Remove(i) called with vacuous iterator\n";
		return i;
	}
	i._current = i._current->_next;                  // advance iterator
	Link * oldLink = LinkOut(i._current->_prev);  // unlink element to be removed
	delete oldLink;                            // delete
	return i;                                  // return i at new position
} // end Remove(Iterator)

template < typename T >
size_t  List<T>::Remove(const T& t)
// Remove all copies of t
// This doesn't use member priviledge, so could be an external function
// It gives the archetype for interaction between Remove(i) and ++i
{
	size_t count(0);
	Iterator i = Begin();
	while (i != End())
	{
		if (t == *i)
		{
			i = Remove(i);
			++count;
		}
		else
		{
			++i;
		}
	}
	return (count);
}  // end Remove(t)

template < typename T >
void List<T>::Clear()
// Deletes all elements of the list
{
	while (!Empty())
		PopFront();
} // end Clear()


template < typename T >
List<T> * List<T>::Clone() const
// returns pointer to a copy of *this
{
	List * clone = new List;
	clone->Append(*this);
	return clone;
}

template < typename T >
size_t List<T>::Size()  const
{
	size_t  size(0);
	Link * curr(_head->_next);
	while (curr != _tail)
	{
		curr = curr->_next;
		++size;
	}
	return size;
}

template < typename T >
bool List<T>::Empty()  const
{
	return (_head->_next == _tail);
}

template < typename T >
T& List<T>::Front()
{
	if (Empty())
	{
		std::cerr << "** List error: Front() called on empty list\n";
	}
	return *Begin();
}

template < typename T >
const T& List<T>::Front() const
{
	if (Empty())
	{
		std::cerr << "** List error: Front() called on empty list\n";
	}
	return *Begin();
}

template < typename T >
T& List<T>::Back()
{
	if (Empty())
	{
		std::cerr << "** List error: Back() called on empty list\n";
	}
	return *rBegin();
}

template < typename T >
const T& List<T>::Back() const
{
	if (Empty())
	{
		std::cerr << "** List error: Back() called on empty list\n";
	}
	return *rBegin();
}

template <typename T>
ListIterator<T>  List<T>::Includes(const T& t)
// sequential search
{
	Iterator i;
	for (i = Begin(); i != End(); ++i)
	{
		if (t == *i)
			return i;
	}
	return End();
} // Includes()

  // output methods

template < typename T >
void List<T>::Display(std::ostream& os, char ofc) const
{
	ConstIterator i;
	if (ofc == '\0')
		for (i = Begin(); i != End(); ++i)
			os << *i;
	else
		for (i = Begin(); i != End(); ++i)
			os << *i << ofc;
} // Display()

  // debug/developer methods

template < typename T >
void List<T>::Dump(std::ostream& os, char ofc) const
{
	Display(os, ofc);
	os << '\n';
} // Dump()

template < typename T >
void List<T>::CheckLinks(std::ostream& os) const
{
	typename List<T>::ConstIterator i, j, k;
	// bool ok = 1;
	size_t n = 0;
	for (i = this->Begin(), n = 0; i != this->End(); ++i, ++n)
	{
		j = i; --j; ++j;
		k = i; ++k; --k;
		if (!i.Valid() || !j.Valid() || !k.Valid() || i != j || i != k)
		{
			os << " ** forward reciprocity failure at position " << n << '\n';
			// ok = 0;
			break;
		}
	}
	// if (ok) os << " ** passed forward reciprocity check\n";

	for (i = this->rBegin(), n = Size(); i != this->rEnd(); --i, --n)
	{
		j = i; --j; ++j;
		k = i; ++k; --k;
		if (!i.Valid() || !j.Valid() || !k.Valid() || i != j || i != k)
		{
			os << " ** reverse reciprocity failure at position " << n << '\n';
			// ok = 0;
			break;
		}
	}
	// if (ok) os << " ** passed reverse reciprocity check\n";
} // CheckLinks()

  // Iterator support

template < typename T >
ListIterator<T>  List<T>::Begin()
{
	Iterator i(_head->_next);
	return i;
}

template < typename T >
ListIterator<T>  List<T>::End()
{
	Iterator i(_tail);
	return i;
}

template < typename T >
ListIterator<T>  List<T>::rBegin()
{
	Iterator i(_tail->_prev);
	return i;
}

template < typename T >
ListIterator<T>  List<T>::rEnd()
{
	Iterator i(_head);
	return i;
}

// ConstIterator support

template < typename T >
typename List<T>::ConstIterator  List<T>::Begin() const
{
	ConstIterator i(_head->_next);
	return i;
}

template < typename T >
typename List<T>::ConstIterator  List<T>::End() const
{
	ConstIterator i(_tail);
	return i;
}

template < typename T >
typename List<T>::ConstIterator  List<T>::rBegin() const
{
	ConstIterator i(_tail->_prev);
	return i;
}

template < typename T >
typename List<T>::ConstIterator  List<T>::rEnd() const
{
	ConstIterator i(_head);
	return i;
}

template <typename T>
typename List<T>::ConstIterator  List<T>::Includes(const T& t) const
{
	ConstIterator i;
	for (i = Begin(); i != End(); ++i)
	{
		if (t == *i)
			return i;
	}
	return End();
} // Includes()

  //-------------------------------------------
  //     ConstListIterator<T>:: Implementations
  //-------------------------------------------

  // default constructor
template < typename T >
ConstListIterator<T>::ConstListIterator() : _current(nullptr)
// construct a null ConstListIterator
{}

// protected constructor
template < typename T >
ConstListIterator<T>::ConstListIterator(typename List<T>::Link* link) : _current(link)
// construct an iterator around a link pointer (not available to client programs)
{}

// copy constructor
template < typename T >
ConstListIterator<T>::ConstListIterator(const ConstListIterator<T>& i)
	: _current(i._current)
{}

// assignment operator
template < typename T >
ConstListIterator<T>& ConstListIterator<T>::operator = (const ConstListIterator <T> & i)
{
	_current = i._current;
	return *this;
}

// protected method
template < typename T >
T&  ConstListIterator<T>::Retrieve() const
// Return reference to current t
// note conflicted signature - const method returns non-const reference
{
	if (_current == nullptr)
	{
		std::cerr << "** Error: ConstListIterator<T>::Retrieve() invalid dereference\n";
		exit(EXIT_FAILURE);
	}
	return _current->Tval_;
}

template < typename T >
bool ConstListIterator<T>::Valid() const
// test cursor for legal dereference
{
	return _current != nullptr;
}

template < typename T >
bool ConstListIterator<T>::operator == (const ConstListIterator<T>& i2) const
{
	if (_current == i2._current)
		return 1;
	return 0;
}

template < typename T >
bool ConstListIterator<T>::operator != (const ConstListIterator<T>& i2) const
{
	return !(*this == i2);
}

template < typename T >
const T&  ConstListIterator<T>::operator * () const
{
	return Retrieve();
}

template < typename T >
ConstListIterator<T>& ConstListIterator<T>::operator ++ ()
// prefix increment
{
	if (_current != nullptr)
		_current = _current->_next;
	return *this;
}

template < typename T >
ConstListIterator<T> ConstListIterator<T>::operator ++ (int)
{
	ConstListIterator <T> clone = *this;
	this->operator++();
	return clone;
}

template < typename T >
ConstListIterator<T>& ConstListIterator<T>::operator -- ()
// prefix decrement
{
	if (_current != nullptr)
		_current = _current->_prev;
	return *this;
}

template < typename T >
ConstListIterator<T> ConstListIterator<T>::operator -- (int)
// postfix decrement
{
	ConstListIterator <T> clone = *this;
	this->operator--();
	return clone;
}

//-------------------------------------------
//     ListIterator<T>:: Implementations
//-------------------------------------------

// default constructor
template < typename T >
ListIterator<T>::ListIterator() : ConstListIterator<T>()
// construct a null ListIterator
{}

// protected constructor
template < typename T >
ListIterator<T>::ListIterator(typename List<T>::Link* link) : ConstListIterator<T>(link)
// construct an iterator around a link pointer (not available to client programs)
{}

// copy constructor
template < typename T >
ListIterator<T>::ListIterator(const ListIterator<T>& i)
	: ConstListIterator<T>(i)
{}

// assignment operator
template < typename T >
ListIterator<T>& ListIterator<T>::operator = (const ListIterator <T> & i)
{
	ConstListIterator<T>::operator=(i);
	return *this;
}

template < typename T >
const T&  ListIterator<T>::operator * () const
{
	return ConstListIterator<T>::Retrieve();
}

template < typename T >
T&  ListIterator<T>::operator * ()
{
	return ConstListIterator<T>::Retrieve();
}

template < typename T >
ListIterator<T>& ListIterator<T>::operator ++ ()
// prefix increment
{
	ConstListIterator<T>::operator++();
	return *this;
}

template < typename T >
ListIterator<T> ListIterator<T>::operator ++ (int)
// postfix increment
{
	ListIterator <T> clone = *this;
	this->operator++();
	return clone;
}

template < typename T >
ListIterator<T>& ListIterator<T>::operator -- ()
// prefix decrement
{
	ConstListIterator<T>::operator--();
	return *this;
}

template < typename T >
ListIterator<T> ListIterator<T>::operator -- (int)
{
	ListIterator <T> clone = *this;
	this->operator--();
	return clone;
}
