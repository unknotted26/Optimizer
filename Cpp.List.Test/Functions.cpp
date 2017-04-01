#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Optimizer.Cpp.List\Optimizer_Cpp_List.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CppListTest
{
	using namespace opti;
	TEST_CLASS(ListMutators)
	{
	public:

		TEST_METHOD(List_Push)
		{
			List<int> l;
			l.PushBack(1);
			l.PushBack(2);
			l.PushBack(3);
			int test = l.Size();
			Assert::AreEqual(3, test);
			
			for (int i = 1; i < 4; ++i)
			{
				Assert::AreEqual(i, l.Front());
				l.PopFront();
			}
			
		}

	};
}