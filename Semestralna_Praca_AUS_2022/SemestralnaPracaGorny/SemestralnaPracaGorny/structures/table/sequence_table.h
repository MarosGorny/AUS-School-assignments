#pragma once

#include "table.h"
#include "../list/list.h"
#include <stdexcept>

namespace structures
{

	/// <summary> Sekvencna tabulka. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class SequenceTable : public Table<K, T>
	{
	public:
		/// <summary> Destruktor. </sumary>
		~SequenceTable();

		/// <summary> Vrati pocet prvkov v tabulke. </summary>
		/// <returns> Pocet prvkov v tabulke. </returns>
		size_t size() override;

		/// <summary> Vrati adresou data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Adresa dat s danym klucom. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak kluc nepatri do tabulky. </exception>
		T& find(const K& key) override;

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>
		void insert(const K& key, const T& data) override;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>
		T remove(const K& key) override;

		/// <summary> Bezpecne ziska data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <param name = "data"> Najdene data (vystupny parameter). </param>
		/// <returns> true, ak sa podarilo najst a naplnit data s danym klucom, false inak. </returns>
		bool tryFind(const K& key, T& data) override;

		/// <summary> Zisti, ci tabulka obsahuje data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> true, tabulka obsahuje dany kluc, false inak. </returns>
		bool containsKey(const K& key) override;

		/// <summary> Vymaze tabulku. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getBeginIterator() override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getEndIterator() override;

	protected:
		/// <summary> Konstruktor. </summary>
		/// <param name = "list"> Zoznam, do ktoreho sa budu ukladat prvky tabulky. </param>
		/// <remarks>
		/// Potomkovia ako list vlozia instanciu implicitne alebo explicitne implementovaneho zoznamu.
		/// List dealokuje tento objekt.
		/// </remarks>
		SequenceTable(List<TableItem<K, T>*>* list);

		/// <summary> Najde prvok tabulky s danym klucom. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <returns> Prvok tabulky s danym klucom, ak neexistuje, vrati nullptr. </returns>
		virtual TableItem<K, T>* findTableItem(const K& key);

		/// <summary> Priradenie struktury. Pomocna metoda, ktora prebera referenciu, ktoru posle potomok. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		/// <summary>
		SequenceTable<K, T>& assignSequenceTable(SequenceTable<K, T>& other);

	protected:
		List<TableItem<K, T>*>* list_;
	};

	template<typename K, typename T>
	inline SequenceTable<K, T>::~SequenceTable()
	{
		this->clear();
		delete list_;
		this->list_ = nullptr;
	}

	template<typename K, typename T>
	inline size_t SequenceTable<K, T>::size()
	{
		return this->list_->size();
	}

	template<typename K, typename T>
	inline T& SequenceTable<K, T>::find(const K& key)
	{

		TableItem<K, T>* item = this->findTableItem(key);
		if (item == nullptr) {
			throw std::out_of_range("SequenceTable<K, T>::find: Unkown key!");
		}
		return item->accessData();
		
		
	}

	template<typename K, typename T>
	inline void SequenceTable<K, T>::insert(const K& key, const T& data)
	{
		if (!this->containsKey(key)) {
			this->list_->add(new TableItem<K, T>(key, data));
		}
		else {
			throw std::logic_error("SequenceTable<K, T>::insert: Duplicate key!");
		}

	}

	template<typename K, typename T>
	inline T SequenceTable<K, T>::remove(const K& key)
	{
		TableItem<K, T>* item = this->findTableItem(key);
		if (item != nullptr) {

			T data = item->accessData();
			list_->tryRemove(item);
			delete item;
			return data;
		}
		else {
			throw std::logic_error("SequenceTable<K, T>::remove: No such key!");
		}


	}

	template<typename K, typename T>
	inline bool SequenceTable<K, T>::tryFind(const K& key, T& data)
	{

		TableItem<K, T>* item = this->findTableItem(key);
		if (item != nullptr) {
			data = item->accessData();
			return true;
		}
		else {
			return false;
		}

	}

	template<typename K, typename T>
	inline bool SequenceTable<K, T>::containsKey(const K& key)
	{
		return !(this->findTableItem(key) == nullptr);
	}

	template<typename K, typename T>
	inline void SequenceTable<K, T>::clear()
	{
		for (TableItem<K, T>* item : *list_) {
			delete item;
		}
		//aby sa nastavili nullptr pre kazdy item.
		list_->clear();

	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* SequenceTable<K, T>::getBeginIterator()
	{
		return list_->getBeginIterator();
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* SequenceTable<K, T>::getEndIterator()
	{
		return list_->getEndIterator();
	}

	template<typename K, typename T>
	inline SequenceTable<K, T>::SequenceTable(List<TableItem<K, T>*>* list) :
		Table<K, T>(),
		list_(list)
	{
	}

	template<typename K, typename T>
	inline TableItem<K, T>* SequenceTable<K, T>::findTableItem(const K& key)
	{
		for (TableItem<K, T>* item : *list_)
		{
			if (item->getKey() == key)
				return item;
		}

		return nullptr;
	}
	
	template<typename K, typename T>
	inline SequenceTable<K, T>& SequenceTable<K, T>::assignSequenceTable(SequenceTable<K, T>& other)
	{
		//deep copy
		//test identity, dolezity kvoli clearu. (tu je to nutne)
		if (this != &other) {
			this->clear();
			for (TableItem<K, T>* otherItem : other) 
			{
				this->list_->add(new TableItem<K, T>(otherItem->getKey(), otherItem->accessData()));
			}
		}

		return *this;
	}
}