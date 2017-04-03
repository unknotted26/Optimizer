#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Optimizer.Cpp.List\Optimizer_Cpp_List.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CppListTest
{
	using namespace opti::DS;
	TEST_CLASS(ListMutators)
	{
	public:

		TEST_METHOD(PushFront)
		{
			List<int> _l;
			bool success = _l.PushFront(1);

			Assert::AreEqual(1, _l.Front(), L"PushFront() was not successful");
		}

		// modifiers
		TEST_METHOD(PushBack)
		{
			List<int> l;
			l.PushBack(1);
			int test = l.Size();
			Assert::AreEqual(1, test);
			Assert::AreEqual(1, l.Front());

			
		}

		// accessors

	};
}