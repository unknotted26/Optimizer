#include "List.h"
#include "..\Optimizer.Cpp.List\Optimizer_Cpp_List.h"
#include <string>
#include <Windows.h>

using namespace std;

string ManagedStringToStdString(System::String^ str)
{
	cli::array<unsigned char>^ bytes = System::Text::Encoding::ASCII->GetBytes(str);
	pin_ptr<unsigned char> pinned = &bytes[0];
	std::string nativeString((char*)pinned, bytes->Length);
	return nativeString;
}

//template< typename T >
void opti::DS::CLI::testClass::InitializeLibrary(System::String^ path)
{
	string nativePath = ManagedStringToStdString(path);
	LoadLibrary(nativePath.c_str()); // Actually load the delayed library from specific location
}

template < typename T >
System::String^ opti::DS::CLI::List<T>::About()
{
	return this->ToString();
}

template < typename T >
void opti::DS::CLI::List<T>::Destroy()
{
	if (_impl != nullptr)
	{
		delete _impl;
		_impl = nullptr;
	}
}

template < typename T >
T opti::DS::CLI::List<T>::Front()
{
	return _impl->Front();
}


template < typename T >
bool opti::DS::CLI::List<T>::PushFront(const T t)
{
	return _impl->PushFront(t);
}

template < typename T >
bool opti::DS::CLI::List<T>::PushBack(const T t)
{
	return _impl->PushBack(t);
}

using namespace opti::DS::CLI;
template < typename T >
typename List<T>::Iterator List<T>::Remove(typename List<T>::Iterator i)
{
	return _impl->Remove(i);
}

template < typename T >
bool List<T>::PopFront()
{
	return _impl->PopFront();
}

template < typename T >
bool List<T>::PopBack()
{
	return _impl->PopBack();
}



/*
template < typename T >
//template <>
//opti::DS::CLI::List<int>::List() : _impl(new DS::List<int>())
opti::DS::CLI::List<T>::List() : _impl(new DS::List<T>())
//opti::DS::CLI::List::List() : _impl(new DS::List<int>())
{}

template < typename T >
//template <>
//void opti::DS::CLI::List<int>::Destroy()
void opti::DS::CLI::List<T>::Destroy()
//void opti::DS::CLI::List::Destroy()
{
	if (_impl != nullptr)
	{
		delete _impl;
		_impl = nullptr;
	}
}

template < typename T >
//template <>
//opti::DS::CLI::List<T>::~List()
//opti::DS::CLI::List<int>::~List()

opti::DS::CLI::List<T>::~List()
//opti::DS::CLI::List::~List()
{
	Destroy();
}

template < typename T >
//template <>
//opti::DS::CLI::List<int>::!List()
opti::DS::CLI::List<T>::!List()
//opti::DS::CLI::List::!List()
{
	Destroy();
}

*/
//template class opti::DS::List<int>;
//template class opti::DS::CLI::List<int>;
