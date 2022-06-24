#pragma once

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include <cmath>

namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists();

		PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other);
		~PriorityQueueTwoLists();

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T& peek() override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		int peekPriority() override;

	protected:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		LinkedList<PriorityQueueItem<T>*>* longList_;

	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>()
	{
		assign(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{

		this->clear();
		delete this->shortList_;
		delete this->longList_;

		this->longList_ = nullptr;
		this->shortList_ = nullptr;
	}

	template<typename T>
	Structure& PriorityQueueTwoLists<T>::assign(Structure& other)
	{
		if (this != &other) {
			PriorityQueueTwoLists<T>& otherPQTL = dynamic_cast<PriorityQueueTwoLists<T>&>(other);

			this->clear();
			this->shortList_->assign(*(otherPQTL.shortList_));

			//for each prepisany na while
			Iterator<PriorityQueueItem<T>*>* it = otherPQTL.longList_->getBeginIterator();
			Iterator<PriorityQueueItem<T>*>* end = otherPQTL.longList_->getEndIterator();

			//Objekt iterator porovnaj s endovym iteratorom
			while (*it != *end) {
				PriorityQueueItem<T>* item = *(*it); //spristupneny objekt iterator
				this->longList_->add(new PriorityQueueItem<T>(*item));
				++(*it);
			}

			delete it;
			delete end;
			

		}

		return *this;
	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size()
	{
		return this->longList_->size() + this->shortList_->size();

	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{

		this->shortList_->clear();
		this->shortList_->trySetCapacity(2);

		for (PriorityQueueItem<T>* item : *this->longList_) {
			delete item;
		}
		this->longList_->clear();

	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(int priority, const T& data)
	{
		if (this->shortList_->size() == 0 || this->shortList_->minPriority() > priority) {
			 PriorityQueueItem<T>* removedItem = this->shortList_->pushAndRemove(priority, data);

			 if (removedItem != nullptr) {
				 this->longList_->add(removedItem);
			 }
		}
		else {
			this->longList_->add(new PriorityQueueItem<T>(priority, data));
		}
	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{
		T data = this->shortList_->pop();

		if (this->shortList_->size() == 0 && this->longList_->size() != 0) {
			
			
			int sqrtOfLongList = static_cast<int>(std::sqrt(this->longList_->size()));

			if (sqrtOfLongList <= 4) {
				this->shortList_->trySetCapacity(4);
			}
			else {
				this->shortList_->trySetCapacity(sqrtOfLongList);
			}
			

			
			//new zoznam
			structures::LinkedList<PriorityQueueItem<T>*>* helpingLongList = new structures::LinkedList<PriorityQueueItem<T>*>();

			while (this->longList_->size() != 0) {
				PriorityQueueItem<T>* removedItem = this->longList_->removeAt(0);

				if (this->shortList_->size() != 0 && removedItem->getPriority() >= this->shortList_->minPriority()) {
					helpingLongList->add(removedItem);
				}
				else {
					PriorityQueueItem<T>* pushedItem = this->shortList_->pushAndRemove(removedItem->getPriority(), removedItem->accessData());

					delete removedItem;
					removedItem = nullptr;

					if (pushedItem != nullptr) {
						helpingLongList->add(pushedItem);
					}
				}
			}

			this->longList_->clear();
			delete this->longList_;
			this->longList_ = helpingLongList;
		}

		return data;

	}

	template<typename T>
	T& PriorityQueueTwoLists<T>::peek()
	{
		if (this->shortList_->size() == 0) {
			std::logic_error("PriorityQueueTwoLists<T>::peekPriority: List is empty!");
		}

		return this->shortList_->peek();

	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority()
	{
		if (this->shortList_->size() == 0) {
			std::logic_error("PriorityQueueTwoLists<T>::peekPriority: List is empty!");
		} 

		return this->shortList_->peekPriority();
	}
}