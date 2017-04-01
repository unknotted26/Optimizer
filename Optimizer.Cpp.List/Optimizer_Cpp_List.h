#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the Optimizer_Cpp_List_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// Optimizer_Cpp_List_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef Optimizer_Cpp_List_EXPORTS
#define Optimizer_Cpp_List_API __declspec(dllexport)
#else
#define Optimizer_Cpp_List_API __declspec(dllimport)
#endif

#include <iostream>
#include <cstdlib>

namespace opti
{
	namespace DS
	{
		template < typename T > class List;
		template < typename T > class ListIterator;
		template < typename T > class ConstListIterator;

		//template class List<int>;
		//template class ConstListIterator<int>;
		//template class ListIterator<int>;
		/***********
			List
		 ***********/
		template < typename T >
		class Optimizer_Cpp_List_API List
		{

		public:
			// terminology support: 
			// some scope List<T>:: type definitions to facilitate clients
			typedef T                                      ValueType;
			typedef ListIterator < T >                     Iterator;
			typedef ConstListIterator < T >                ConstIterator;

			// constructors and assignment
			List();              // default constructor
			virtual        ~List();              // destructor
			List(const List&);  // copy constructor
			List&          operator = (const List&);  // assignment
			virtual List * Clone() const;        // returns ptr to deep copy of this list [13]

												 // modifying List structure - mutators
			bool      PushFront(const T& t);   // Insert t at front of list [3] [4]
			bool      PushBack(const T& t);   // Insert t at back of list
			Iterator  Insert(Iterator i, const T& t);  // Insert t at i  [5]
			ConstIterator  Insert(ConstIterator i, const T& t);  // ConstIterator version
			Iterator  Insert(const T& t);   // Insert t                  [6]
			List&     operator+= (const List& list); // append list

			bool      PopFront();              // Remove the Tval at front
			bool      PopBack();              // Remove the Tval at back 
			Iterator  Remove(Iterator i);    // Remove item at I          [7]
			ConstIterator  Remove(ConstIterator i);    // ConstIterator version
			size_t    Remove(const T& t);    // Remove all copies of t    [8]
			void      Clear();              // Empty the list, deleting all elements
											// NOTE: pop and remove operations may make some iterators illegitimate! 

											// macroscopic (whole list) mutators
			void      Sort();               // default order <
			void      Merge(List<T>& list);  // merges "list" into this list
			void      Reverse();

			template < class Predicate > // Predicate object used to determine order
			void      Sort(Predicate& p);

			template < class Predicate > // Predicate object used to determine order
			void      Merge(List<T>& list, Predicate& p);

			// information about the list - accessors
			size_t    Size() const;  // return the number of elements on the list
			bool      Empty() const;  // true iff list has no elements

									  // accessing values on the list - more accessors
			T&        Front();        // return reference to Tval at front of list
			const T&  Front() const;  // const version
			T&        Back();        // return reference to Tval at back of list
			const T&  Back() const;  // const version

									 // Iterator support - locating places on the list
			Iterator  Begin(); // return iterator to front        [9]
			Iterator  End(); // return iterator "1 past the back"
			Iterator  rBegin(); // return iterator to back
			Iterator  rEnd(); // return iterator "1 past the front" in reverse
			Iterator  Includes(const T& t); // returns position of first occurrence of t, or End()

											// ConstIterator support
			ConstIterator  Begin() const;
			ConstIterator  End() const;
			ConstIterator  rBegin() const;
			ConstIterator  rEnd() const;
			ConstIterator  Includes(const T& t) const;

			// generic display methods
			void Display(std::ostream& os, char ofc = '\0') const;
			void Dump(std::ostream& os, char ofc = '\0') const;

			// structural integrity check
			void CheckLinks(std::ostream& os = std::cout) const;

		protected:
			// A scope List<T>:: class usable only by its friends (all members are private)
			class Link
			{
				friend class List<T>;
				friend class ConstListIterator<T>;
				friend class ListIterator<T>;

				// Link variables
				T       Tval_;        // data
				Link *  _prev;        // ptr to predecessor Link
				Link *  _next;        // ptr to successor Link

									  // Link constructor - parameter required
				Link(const T&);
			};

			Link *  _head,  // node representing "one before the first"
				*_tail;  // node representing "one past the last"

			// Set up list
			void Init();
			// append deep copy of list
			void Append(const List& list);

			// protected method isolates memory allocation and associated exception handling
			static Link * NewLink(const T&);

			// standard link-in and link-out processes
			static void   LinkIn(Link * location, Link * newLink);
			static Link * LinkOut(Link * oldLink);

			// tight couplings
			friend class ListIterator<T>;
			friend class ConstListIterator<T>;
		};

		template class List<int>;

		template <typename T>
		bool operator == (const List<T>& list1, const List<T>& list2);

		template <typename T>
		bool operator != (const List<T>& list1, const List<T>& list2);

		template <typename T>
		std::ostream& operator << (std::ostream& os, const List<T>& list);

		template <typename T>
		class Optimizer_Cpp_List_API ConstListIterator
		{
		public:
			// terminology support
			typedef T                                      ValueType;
			typedef ConstListIterator < T >                ConstIterator;
			typedef ListIterator < T >                     Iterator;

			// constructors
			ConstListIterator();                          // default constructor
			ConstListIterator(const ConstListIterator&); // copy constructor

														 // information/access
			bool Valid() const;  // cursor is valid element           [11]

								 // various operators
			bool            operator == (const ConstIterator& i2) const;
			bool            operator != (const ConstIterator& i2) const;
			const T&        operator *  () const; // Return const reference to current Tval
			ConstIterator&  operator =  (const ConstIterator& i);
			ConstIterator&  operator ++ ();    // prefix
			ConstIterator   operator ++ (int); // postfix
			ConstIterator&  operator -- ();    // prefix
			ConstIterator   operator -- (int); // postfix

		protected:
			//template class List<int>;
			//template class ConstListIterator<int>;
			//template class ListIterator<int>;

			// data
			typename List<T>::Link * _current;

			// methods
			ConstListIterator(typename List<T>::Link * linkPtr); // type converting constructor
			T& Retrieve() const; // conflicted Retrieve used by both versions of operator*

								 // tight couplings
			friend class List<T>;
		};

		template class ConstListIterator<int>;

		template < typename T >
		class Optimizer_Cpp_List_API ListIterator : public ConstListIterator<T>
		{
		public:
			// terminology support
			typedef T                                      ValueType;
			typedef ConstListIterator < T >                ConstIterator;
			typedef ListIterator < T >                     Iterator;

			// constructors
			ListIterator();                       // default constructor
			ListIterator(List<T>&);              // initializing constructor
			ListIterator(const ListIterator&);   // copy constructor

												 // information/access
												 // bool Valid         () const;

			// bool       operator == (const Iterator& i2) const;
			// bool       operator != (const Iterator& i2) const;
			T&         operator *  ();
			const T&   operator *  () const;
			Iterator&  operator =  (const Iterator& i);
			Iterator&  operator ++ ();
			Iterator   operator ++ (int);
			Iterator&  operator -- ();
			Iterator   operator -- (int);

		protected:
			// type converting constructor
			ListIterator(typename List<T>::Link * linkPtr);
			// T& Retrieve () const; // conflicted Retrieve used by both versions of operator*

			// tight couplings
			friend class List<T>;
		};

		//template class List<int>;
		//template class ConstListIterator<int>;
		template class ListIterator<int>;
	}
}
