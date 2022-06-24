#pragma once

#include "sort.h"
#include "../kriterium/Kriterium.h"

/// <summary> Triedenie Quick sort. </summary>
/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
/// <typeparam name = "R"> Typ parametra na zaklade ktoreho sa triedi </typepram>
template <typename K, typename T,typename R>
class QuickSort : public Sort<K, T,R>
{
public:
	/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
	/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
	void sort(structures::UnsortedSequenceTable<K, T>& table) override;
	void utriedCezKriterium(structures::UnsortedSequenceTable<K, T>& table, Kriterium<R>& criterium, bool vzostupne= true) override;

private:
	void quick(structures::UnsortedSequenceTable<K, T>& table, int startIndex, int endIndex);
	void quickKriterium(structures::UnsortedSequenceTable<K, T>& table, int startIndex, int endIndex, Kriterium<R>& kriterium, bool vzostupne = true);
};

template <typename K, typename T, typename R>
inline void QuickSort<K, T,R>::sort(structures::UnsortedSequenceTable<K, T>& table)
{
	this->quick(table, 0, static_cast<int>(table.size() - 1));
}

template<typename K, typename T, typename R>
inline void QuickSort<K, T, R>::utriedCezKriterium(structures::UnsortedSequenceTable<K, T>& table, Kriterium<R>& kriterium, bool vzostupne)
{
	this->quickKriterium(table, 0, static_cast<int>(table.size() - 1), kriterium, vzostupne);
}



template <typename K, typename T, typename R>
inline void QuickSort<K, T,R>::quick(structures::UnsortedSequenceTable<K, T>& table, int startIndex, int endIndex)
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

template<typename K, typename T, typename R>
inline void QuickSort<K, T, R>::quickKriterium(structures::UnsortedSequenceTable<K, T>& table, int startIndex, int endIndex, Kriterium<R>& kriterium, bool vzostupne)
{
	R pivot = kriterium.urobKriterium(table.getItemAtIndex(startIndex + (endIndex - startIndex) / 2).accessData());
	int left = startIndex;
	int right = endIndex;

	while (left < right) {
		if (vzostupne) {
			while (kriterium.urobKriterium(table.getItemAtIndex(left).accessData()) < pivot) {
				left++;
			}
			while (kriterium.urobKriterium(table.getItemAtIndex(right).accessData()) > pivot) {
				right--;
			}
		}
		else {
			while (kriterium.urobKriterium(table.getItemAtIndex(left).accessData()) > pivot) {
				left++;
			}
			while (kriterium.urobKriterium(table.getItemAtIndex(right).accessData()) < pivot) {
				right--;
			}
		}

		if (left <= right) {
			table.swap(left, right);
			left++;
			right--;
		}
	}
	if (startIndex < right) {
		this->quickKriterium(table, startIndex, right,kriterium,vzostupne);
	}
	if (left < endIndex) {
		this->quickKriterium(table, left, endIndex,kriterium,vzostupne);
	}

}