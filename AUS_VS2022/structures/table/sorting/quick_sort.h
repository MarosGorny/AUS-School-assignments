#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"

namespace structures
{
	/// <summary> Triedenie Quick sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class QuickSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
	private:
		void quick(UnsortedSequenceTable<K, T>& table, int startIndex, int endIndex);
	};

	template<typename K, typename T>
	inline void QuickSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		this->quick(table, 0, table.size() - 1);
	}

	template<typename K, typename T>
	inline void QuickSort<K, T>::quick(UnsortedSequenceTable<K, T>& table, int startIndex, int endIndex)
	{
		K pivot = table.getItemAtIndex(startIndex + (endIndex - startIndex) / 2).getKey();
		int left = startIndex;
		int right = endIndex;
		while (left <= right) {
			while (table.getItemAtIndex(left).getKey() < pivot) {
				left++;
			}
			while (table.getItemAtIndex(right).getKey() > pivot) {
				right--;
			}
			if (left <= right) {
				table.swap(left, right);
				left++;
				right--;
			}
		}
		if (startIndex < right) {
			this->quick(table, startIndex, right);
		}
		if (left < endIndex) {
			this->quick(table, left, endIndex);
		}

	}

}