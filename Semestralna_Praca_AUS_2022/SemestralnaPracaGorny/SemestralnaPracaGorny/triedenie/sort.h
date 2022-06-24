#pragma once


#include "../structures/table/unsorted_sequence_table.h"
#include "../kriterium/Kriterium.h"

/// <summary> Triedenie NonortedSequenceTable navrhnuté ako funkèný objekt. </summary>
/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
template <typename K, typename T, typename R>
class Sort
{
public:
	/// <summary> Destruktor. </summary>
	virtual ~Sort();

	/// <summary> Funkcny operator utriedi tabulku. </summary>
	/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
	/// <remarks> Využíva metódu sort. </remarks>
	void operator()(structures::UnsortedSequenceTable<K, T>& table);

	/// <summary> Utriedi utriedi tabulku. </summary>
	/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
	virtual void sort(structures::UnsortedSequenceTable<K, T>& table) = 0;
	virtual void utriedCezKriterium(structures::UnsortedSequenceTable<K, T>& table, Kriterium<R>& criterium, bool vzostupne) = 0;
};

template <typename K, typename T, typename R>
inline Sort<K, T,R>::~Sort()
{
}

template <typename K, typename T, typename R>
inline void Sort<K, T,R>::operator()(structures::UnsortedSequenceTable<K, T>& table)
{
	this->sort(table);
}
