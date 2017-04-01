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
		template < typename T > class List; // This works!

		namespace CLI
		{
			template < typename T > // This works!
			public ref class List 
			{
			public:
				List() : _impl(new DS::List<T>()) { }
				~List() { Destroy(); }
				
				!List() { Destroy(); } // finalizer (only applies to ref classes)

				void Destroy()
				{
					if (_impl != nullptr)
					{
						delete _impl;
						_impl = nullptr;
					}
				}
				
				 System::String^ About() { return "Hello from C++/CLI template List"; }
				 System::Int32 Front() { return  _impl->Front(); }
				 void InitTestValues()
				 {
					 _impl->PushBack(1);
					 _impl->PushBack(2);
					 _impl->PushBack(3);
				 }

			protected:
				DS::List<T>* _impl;
			};

			// This is needed in order to use the methods of this ref class. The compiler will not recognize
			// methods for an instance of this class (of this exact type) if this is not instantiated. Example, 
			// _list object in testClass would not be complete...
			//template ref class List<int>; // instantiate this specialization of the class 
			//template ref class List;
			public ref class ListInt : List<int>
			{
			public:
				ListInt() { }//this->_impl = new DS::List<int>(); }// This will cause error: C2027 - use of undefined. } 
			};
			
			
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
				listContainer() {
					//ListInt ob; 
				}
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
			//template < typename T >
			public ref class TemplateWrapper 
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
					System::Int32 num = 32;
					// detail::is_instance_of_managed_type<int>::is_instance_of(_datatype);
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

