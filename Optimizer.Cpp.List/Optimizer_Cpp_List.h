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
#include <string>

namespace opti
{
	namespace DS
	{
		template < typename T > class List;
		template < typename T > class ListIterator;
		template < typename T > class ConstListIterator;

		/***********
			List
		 ***********/
		template < typename T >
		class Optimizer_Cpp_List_API List
		{

		public:

			typedef T                                      ValueType;
			typedef ListIterator < T >                     Iterator;
			typedef ConstListIterator < T >                ConstIterator;

			// constructors and assignment
			List();             
			virtual        ~List();             
			List(const List&);  
			List&          operator = (const List&); 
			virtual List * Clone() const;        // deep copy

			// mutators
			bool      PushFront(const T& t);   
			bool      PushBack(const T& t);   
			Iterator  Insert(Iterator i, const T& t);  
			ConstIterator  Insert(ConstIterator i, const T& t);  
			Iterator  Insert(const T& t);   
			List&     operator+= (const List& list); 

			bool      PopFront();          
			bool      PopBack();           
			Iterator  Remove(Iterator i);           
			ConstIterator  Remove(ConstIterator i);
			size_t    Remove(const T& t);    // Remove all copies of t
			void      Clear();             
											// NOTE: pop and remove operations may make some iterators illegitimate! 
			void      Sort();               // default order <
			void      Merge(List<T>& list);  
			void      Reverse();

			template < class Predicate > 
			void      Sort(Predicate& p);

			template < class Predicate > 
			void      Merge(List<T>& list, Predicate& p);

			// accessors
			size_t    Size() const;  
			bool      Empty() const;  
			T&        Front();        
			const T&  Front() const;  
			T&        Back();        
			const T&  Back() const;  

			Iterator  Begin(); 
			Iterator  End(); // points after the last valid element
			Iterator  rBegin(); 
			Iterator  rEnd(); // iterator starts at the invalid element after the last element
			Iterator  Includes(const T& t); // return End if (first) t not found

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

			class Link
			{
				friend class List<T>;
				friend class ConstListIterator<T>;
				friend class ListIterator<T>;

				Link(const T&);

				T       Tval_;        
				Link *  _prev;        
				Link *  _next;        									  
			};

			Link *  _head, *_tail;  

			void Init(); // setup the list
			void Append(const List& list); // append a deep copy

			static Link * NewLink(const T&);

			static void   LinkIn(Link * location, Link * newLink);
			static Link * LinkOut(Link * oldLink);

			// tight couplings
			friend class ListIterator<T>;
			friend class ConstListIterator<T>;
		};

		template class List<int>;
		template class List<double>;
		template class List<std::string>;

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

			typedef T                                      ValueType;
			typedef ConstListIterator < T >                ConstIterator;
			typedef ListIterator < T >                     Iterator;

			ConstListIterator();                         
			ConstListIterator(const ConstListIterator&); 
														 
			bool Valid() const;  
								 
			bool            operator == (const ConstIterator& i2) const;
			bool            operator != (const ConstIterator& i2) const;
			const T&        operator *  () const; 
			ConstIterator&  operator =  (const ConstIterator& i);
			ConstIterator&  operator ++ ();    
			ConstIterator   operator ++ (int); 
			ConstIterator&  operator -- ();    
			ConstIterator   operator -- (int); 

		protected:
		
			typename List<T>::Link * _current;

			ConstListIterator(typename List<T>::Link * linkPtr); // type converting constructor
			T& Retrieve() const; // conflicted Retrieve used by both versions of operator*

			// tight couplings
			friend class List<T>;
		};

		template class ConstListIterator<int>;
		template class ConstListIterator<double>;
		template class ConstListIterator<std::string>;

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

		template class ListIterator<int>;
		template class ListIterator<double>;
		template class ListIterator<std::string>;
	}
}
