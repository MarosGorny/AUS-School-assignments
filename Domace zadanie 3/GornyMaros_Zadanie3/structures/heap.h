#pragma once

#include "priority_queue_list.h"
#include "../list/array_list.h"
#include "../utils.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Prioritny front implementovany haldou. Implementujucim typom haldy je struktura ArrayList. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class Heap : public PriorityQueueList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		Heap();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Halda, z ktorej sa prevezmu vlastnosti. </param>
		Heap(Heap<T>& other);

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vlozi prvok s danou prioritou do haldy. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z haldy. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je halda prazdna. </exception>
		T pop() override;

	protected:
		/// <summary> Vrati index v ArrayList-e, na ktorom sa nachadza prvok s najvacsou prioritou. </summary>
		/// <returns> Index prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je ArrayList prazdny. </exception>
		int indexOfPeek() override;

	private:
		/// <summary> Vrati index v ArrayList-e, na ktorom by sa mal nachadzat otec daneho prvku. </summary>
		/// <param name = "index"> Index prvku, ktoreho otca chceme vratit. </param>
		/// <returns> Index, na ktorom by sa mal nachadzat otec prvku. </returns>
		int getParentIndex(int index);

		/// <summary> Vrati index v ArrayList-e, na ktorom by mal mat dany prvok syna s najvacsou prioritou. </summary>
		/// <param name = "index"> Index prvku, ktoreho syna chceme vratit. </param>
		/// <returns> Index, na ktorom by sa mal nachadzat syn prvku. </returns>
		int getGreaterSonIndex(int index);

	};

	template<typename T>
	Heap<T>::Heap() :
		PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	Heap<T>::Heap(Heap<T>& other) :
		Heap<T>()
	{
		assign(other)
	}

	template<typename T>
	inline Structure& Heap<T>::assign(Structure& other)
	{
		if (this != &other) {
			Heap<T>& otherHeap = dynamic_cast<Heap<T>&>(other);
			return PriorityQueueList<T>::assignPrioQueueList(otherHeap);
		}

		return *this;

		
	}

	template<typename T>
	void Heap<T>::push(int priority, const T& data)
	{
		//pridany item
		PriorityQueueItem<T>* item = new PriorityQueueItem<T>(priority, data);
		//pridam na prvu volnu poziciu
		this->list_->add(item);

		//ak nemam otca
		if (this->list_->size() == 1)
			return;

		//index pridaneho prvku
		int index = static_cast<int>(this->list_->size()) - 1;

		
		//prebublanie smerom hore na spravne miesto
		while (this->list_->at(getParentIndex(index))->getPriority() > this->list_->at(index)->getPriority()) {
			

			//vymena prvkov
			Utils::swap(this->list_->at(getParentIndex(index)), this->list_->at(index));
			//swap(getParentIndex(index), index);
			if (index == 0)
				return;
			//aktualizacia indexu
			index = getParentIndex(index);
		}


	}

	template<typename T>
	T Heap<T>::pop()
	{
		//ak je halda prazdna
		if (this->list_->size() == 0)
			std::logic_error("Heap<T>::pop(): Heap is empty!");



		//ulozeny prvok s najvacsou prioritou
		PriorityQueueItem<T>* item = this->list_->at(indexOfPeek());
		//ulozene data z PriorityQueueItem<T>*
		T data = item->accessData();
		
		if (this->list_->size() == 1) {
			this->list_->removeAt(0);
			delete item;
			return data;
		}


		//vymazanie posledneho prvku a presunutie ho na nultu poziciu
		this->list_->at(0) = this->list_->removeAt(static_cast<int>(this->list_->size()) - 1);
		
		//prebublanie smerom dole na spravne miesto
		//index korena
		int index = 0;
		int greaterSonIndex = getGreaterSonIndex(0);
		if (greaterSonIndex < this->list_->size()) {
			while (this->list_->at(greaterSonIndex)->getPriority() < this->list_->at(index)->getPriority()) {

				//inak swapujem so synom ktory mal lepsiu prioritu
				Utils::swap(this->list_->at(greaterSonIndex), this->list_->at(index));

				//aktualizujem indexes
				index = greaterSonIndex;
				greaterSonIndex = getGreaterSonIndex(index);

				if (greaterSonIndex >= this->list_->size())
					break;
			}
		}
		


		delete item;
		return data;
	}

	template<typename T>
	inline int Heap<T>::getParentIndex(int index)
	{
		//ak je otec
		if (index == 0)
			return 0;

		if (index % 2 != 0) {
			return index / 2;
		}
		else {
			return (index / 2) - 1;
		}
	}

	template<typename T>
	inline int Heap<T>::getGreaterSonIndex(int index)
	{

		int leftSon = (index * 2) + 1;
		int rightSon = (index * 2) + 2;


		//ak nema synov
		if (leftSon >= this->list_->size()) {
			return leftSon;
		}

		//ak ma len laveho syna
		if (rightSon >= this->list_->size()) {
			return leftSon;
		}

		//ak ma obidvoch synov, porovnavam priority
		if (this->list_->at(leftSon)->getPriority() <= this->list_->at(rightSon)->getPriority())
			return leftSon;
		return rightSon;

	}


	template<typename T>
	inline int Heap<T>::indexOfPeek()
	{
		if (this->list_->size() == 0)
			throw std::logic_error("Heap<T>::indexOfPeek(): Heap is empty!");

		return 0;
	}
}