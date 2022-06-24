#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"

namespace structures
{
	/*
	objekt ktory vrati hodnotu kriteria
	T je objekt nad ktorym to budem spustat (obec napr)
	O aky typ ma dana informacia (napr string...nazov)
	*/
	template <typename T, typename O>
	class Criterium
	{
	public:
		virtual O getValue(T& data) = 0;
	};

	class Obec
	{
	public:
		std::string nazov() { return this->nazov_; }
	private:
		std::string nazov_;
	};

	class CriteriumTitle : Criterium<Obec,std::string>
	{
	public:
		std::string getValue(Obec& data) {
			return data.nazov();
		}
	};

	/// <summary> Triedenie Select sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T, typename O>
	class SelectSort : public Sort<K, T>
	{		//O je typ parametra na zaklade ktoreho sa bude triedit
	public:
		/// <summary> Utriedi tabulku triedenim Select sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
		//tu je ale treti parameter O, ktory predstavuje navratovu hodnotu
		void sort2(UnsortedSequenceTable<K, T>& table, Criterium<T,O>& criterium);
	};

	template<typename K, typename T,typename O>
	inline void SelectSort<K, T,O>::sort(UnsortedSequenceTable<K, T>& table)
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
	template<typename K, typename T, typename O>
	inline void SelectSort<K, T,O>::sort2(UnsortedSequenceTable<K, T>& table, Criterium<T, O>& criterium)
	{
		for (int i = 0; i < table.size(); i++) {
			//poslem kriteriu moju obec a ten vrati vystup "O"
			O min = criterium.getValue(table.getItemAtIndex(i).accessData());
			int minIndex = i;
			for (int j = i + 1; j < table.size(); j++) {
				if (criterium.getValue(table.getItemAtIndex(j).accessData()) < min) {
					min = criterium.getValue(table.getItemAtIndex(j).accessData());
					minIndex = j;
				}
			}
			table.swap(i, minIndex);
		}
	}

}