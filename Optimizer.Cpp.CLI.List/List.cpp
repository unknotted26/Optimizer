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
