#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Optimizer.Cpp.List\Optimizer_Cpp_List.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CppListTest
{
	typedef int elementType;
	typedef opti::List<elementType> container;
	using namespace opti;
	TEST_CLASS(ListConstructors)
	{
	public:
		
		TEST_METHOD(List_Constructor)
		{
			container a;
		}

	};
}