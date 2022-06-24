#include "sorting_test.h"

#include "../../structures/table/unsorted_sequence_table.h"
#include "../../structures/table/sorting/bubble_sort.h"
#include "../../structures/table/sorting/heap_sort.h"
#include "../../structures/table/sorting/insert_sort.h"
#include "../../structures/table/sorting/merge_sort.h"
#include "../../structures/table/sorting/quick_sort.h"
#include "../../structures/table/sorting/radix_sort.h"
#include "../../structures/table/sorting/select_sort.h"
#include "../../structures/table/sorting/shell_sort.h"

#include <algorithm>
#include <random>

namespace tests
{
// SortTest:

	SortTest::SortTest(std::string name, structures::Sort<int, int>* sort) :
		SimpleTest(std::move(name)),
		sort_(sort)
	{
	}

	void SortTest::test()
	{
		using namespace structures;

		const int NumElems = 1'000;
		std::vector<int> data;
		for (int i = 0; i < NumElems; ++i)
		{
			data.emplace_back(i);
		}
		std::default_random_engine rngData;
		std::shuffle(data.begin(), data.end(), rngData);

		UnsortedSequenceTable<int, int> table;

		for (const int item : data)
		{
			const int key = item;
			table.insert(key, item);
		}

		sort_->sort(table);

		for (int i = 0; i < table.size() - 1; ++i)
		{
			if (table.getItemAtIndex(i).getKey() > table.getItemAtIndex(i + 1).getKey())
			{
				this->fail("Table not sorted.");
				return;
			}
		}

		this->succeed("Table is sorted.");
	}

// SortsTest:

	SortsTest::SortsTest() :
		 ComplexTest("SortingAlgorithms")
	{
		using namespace structures;
		addTest(new SortTest("SelectSort", new SelectSort<int, int,int>()));
		addTest(new SortTest("InsertSort", new InsertSort<int, int>()));
		addTest(new SortTest("BubbleSort", new BubbleSort<int, int>()));

		addTest(new SortTest("HeapSort", new HeapSort<int, int>()));
		addTest(new SortTest("MergeSort", new MergeSort<int, int>()));
		addTest(new SortTest("QuickSort", new QuickSort<int, int>()));
		addTest(new SortTest("RadixSort", new RadixSort<int, int>()));
		addTest(new SortTest("ShellSort", new ShellSort<int, int>()));
	}
}
