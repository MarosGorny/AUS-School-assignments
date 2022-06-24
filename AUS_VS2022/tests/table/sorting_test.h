#pragma once

#include "../test.h"
#include "../../structures/table/sorting/sort.h"

namespace tests
{
	class SortTest
		: public SimpleTest
	{
	public:
		SortTest(std::string name, structures::Sort<int, int>* sort);
		void test() override;

	private:
		structures::Sort<int, int>* sort_;
	};

	class SortsTest
		: public ComplexTest
	{
	public:
		SortsTest();
	};
}