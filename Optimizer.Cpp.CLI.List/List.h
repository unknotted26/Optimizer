#pragma once
#include <iostream>
#include <string>
#include <msclr/marshal.h>
#using <System.Core.dll>

//#include "..\Optimizer.Cpp.List\Optimizer_Cpp_List.h" // will cause LNK1104 cannot open file Optimizer.Cpp.List.lib
namespace opti
{
	namespace DS
	{
		//template <int>
		//class List<int>;
		
		//template class List<int>;

		// This is needed so the compiler can recognize instances of this class (C2039)
		template < typename T > class List; 
		template < typename T > class ListIterator;
		template < typename T > class ConstListIterator;

		namespace CLI
		{


			template < typename T > 
			public ref class List 
			{
				typedef T valueType;
				typedef DS::ListIterator< T > Iterator;
				typedef DS::ConstListIterator< T > ConstIterator;

			public:
				List() : _impl(new DS::List<valueType>()) { }
				// Implements/ overrides the IDisposable::Dispose method
				~List() { Destroy(); }				
				// implements/ overrides the Object::Finalize method
				!List() { Destroy(); } // finalizer (only applies to ref classes)
				void Destroy();
				System::String^ About();

				bool PushFront(const T t);
				bool PushBack(const T t);
				Iterator Insert(Iterator i, const T t); // insert t at position i
				ConstIterator Insert(ConstIterator i, const T t);
				Iterator Insert(const T t);
				List operator+= (const List list); // append to list an existing list

				bool PopFront();
				bool PopBack();				
				Iterator Remove(Iterator i);
				ConstIterator Remove(ConstIterator i);				
				size_t Remove(const T t); // remove all copies and return the total amount removed
				void Clear() { _impl->Clear(); }

				void Sort();
				void Merge(List<T> list);
				void Reverse();

				template< class Predicate >
				void Sort(Predicate p);

				template < class Predicate >
				void Merge(List<T> list, Predicate p);

				size_t Size();
				bool Empty();

				T Front();
				T Back() { return _impl->Back(); }

				Iterator Begin();
				Iterator End();
				Iterator rBegin();
				Iterator rEnd();
				Iterator Includes(const T t);
				/*
				ConstIterator Begin();
				ConstIterator End();
				ConstIterator rBegin();
				ConstIterator rEnd();
				ConstIterator Includes(const T t);
				*/
			

			protected:
				DS::List<valueType>* _impl;
			};

			// This is needed in order to use the methods of this ref class. The compiler will not recognize
			// methods for an instance of this class (of this exact type) if this is not instantiated. Example, 
			// _list object in testClass would not be complete...
			template ref class List<int>; // instantiate this specialization of the class 
			template ref class List<double>;
			//template ref class List<string>;

			// Managed Wrappers

			public ref class ListInt : List<int>
			{
			public:
				ListInt() { }
			};

			// ** End of managed wrappers
			
			// This works.
			public ref class testClass 
			{
			public:
				testClass() : _list(gcnew List<int>()){ }
				typename List<int>^ _list;
				~testClass() {}
				// This implicitly causes the class to inherit from IDisposable
				!testClass() {}
				static void InitializeLibrary(System::String^ path);
			};
			

			template < typename T >
			public ref class listContainer
			{
			public:
				listContainer() {}
				listContainer(List<T>^ l) : _l(l) {}
				List<T>^ _l;
			};

			// detail 

			namespace detail
			{
					generic < typename T >
					ref class is_instance_of_managed_helper sealed abstract
					{
					public:
						// assignment can only occur as part of declaration or in this class' static constructor
						static initonly System::Func<System::Object^, bool>^ is_instance_of = build();

					private:
						static System::Func<System::Object^, bool>^ build()
						{
							using System::Linq::Expressions::Expression;
							auto param = Expression::Parameter(System::Object::typeid);
							return Expression::Lambda< System::Func<System::Object^, bool> ^>(
								Expression::TypeIs(param, T::typeid), param)->Compile();
						}
					};

					template < typename T >
					struct is_instance_of_helper
					{
						static bool is_instance_of(System::Object^ obj)
						{
							return is_instance_of_managed_helper<T>::is_instance_of(obj);
						}
					};

					template < typename T >
					struct is_instance_of_helper<T^>
					{
						static bool is_instance_of(System::Object^ obj)
						{
							return dynamic_cast<T^>(obj) != nullptr;
						}
					};
			}

			template < typename T >
			bool is_instance_of(System::Object^ obj)
			{
				return detail::is_instance_of_helper<T>::is_instance_of(obj);
			}

			generic < typename T >
			public ref class TemplateWrapper : List<int>
			{
			public:
				TemplateWrapper() {}//: _list(gcnew List<>()) {}
				~TemplateWrapper() {}
				!TemplateWrapper() {}

				System::String^ About()
				{
					return this->GetType()->GetElementType()->ToString();
				}

				System::Boolean IsInt()
				{
					return is_instance_of<int>(_datatype); 
				}

				void SetList()//listContainer<int> lc)
				{
					if (this->IsInt())
					{
						//lc._l = gcnew List<int>();
					}
				}
			private:
				T _datatype;
				//typename List<T>^ _list;
			};


			
		}

	}
}

