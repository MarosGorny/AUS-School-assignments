#pragma once

#include "sort.h"
#include "../uzemnaJednotka/UzemnaJednotka.h"


/*
objekt ktory vrati hodnotu kriteria
T je objekt nad ktorym to budem spustat (obec napr)
O aky typ ma dana informacia (napr string...nazov)
*/



/// <summary> Triedenie Select sort. </summary>
/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
/// <typeparam name = "O"> Typ parametra na zaklade ktoreho sa triedi </typepram>
template <typename K, typename T, typename R>
class SelectSort : public Sort<K, T,R>
{		//O je typ parametra na zaklade ktoreho sa bude triedit
public:
	/// <summary> Utriedi tabulku triedenim Select sort. </summary>
	/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
	void sort(structures::UnsortedSequenceTable<K, T>& table) override;
	//tu je ale treti parameter O, ktory predstavuje navratovu hodnotu
	void utriedCezKriterium(structures::UnsortedSequenceTable<K, T>& table, Kriterium<R>& criterium, bool vzostupne = true) override;
};

template<typename K, typename T,typename R>
inline void SelectSort<K, T,R>::sort(structures::UnsortedSequenceTable<K, T>& table)
{
	for (int i = 0; i < table.size(); i++) {
		K min = table.getItemAtIndex(i).getKey();
		int minIndex = i;
		for (int j = i + 1; j < table.size(); j++) {
			if (table.getItemAtIndex(j).getKey() < min) {
				min = table.getItemAtIndex(j).getKey();
				minIndex = j;
			}
		}
		table.swap(i, minIndex);
	}
}

//triedenie podla objektu
//tu uz budem volat len ine kriterium podla ktoreho chcem triedit
// napriklad ak budem chciet robit podla kriterium obce, alebo podla veku.
template<typename K, typename T, typename R>
inline void SelectSort<K, T,R>::utriedCezKriterium(structures::UnsortedSequenceTable<K, T>& table, Kriterium<R>& criterium, bool vzostupne)
{
	for (int i = 0; i < table.size(); i++) {
		//poslem kriteriu moju obec a ten vrati vystup "O"
		R min = criterium.urobKriterium(table.getItemAtIndex(i).accessData());
		int minIndex = i;
		for (int j = i + 1; j < table.size(); j++) {
			if (criterium.urobKriterium(table.getItemAtIndex(j).accessData()) < min) {
				min = criterium.urobKriterium(table.getItemAtIndex(j).accessData());
				minIndex = j;
			}
		}
		table.swap(i, minIndex);
	}
}

