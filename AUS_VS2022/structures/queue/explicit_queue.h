#pragma once

#include "queue.h"
#include "../list/linked_list.h"

namespace structures
{
	/// <summary> Explicitny front. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo fronte. </typepram>
	template<typename T>
	class ExplicitQueue : public Queue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ExplicitQueue();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Explicitny front, z ktoreho sa prevezmu vlastnosti. </param>
		ExplicitQueue(ExplicitQueue<T>& other);

		/// <summary> Destruktor. </summary>
		~ExplicitQueue();

		/// <summary> Vrati pocet prvkov vo fronte. </summary>
		/// <returns> Pocet prvkov vo fronte. </returns>
		size_t size() override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento front nachadza po priradeni. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vymaze front. </summary>
		void clear() override;

		/// <summary> Prida prvok do frontu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void push(const T& data) override;

		/// <summary> Odstrani prvok z frontu. </summary>
		/// <returns> Prvok na zaciatku frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>
		T pop() override;

		/// <summary> Vrati prvok na zaciatku frontu. </summary>
		/// <returns> Prvok na zaciatku frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>
		T& peek() override;

	protected:
		/// <summary> Zoznam, pomocou ktoreho je implementovany front. </summary>
		LinkedList<T>* list_;
	};

	template<typename T>
	ExplicitQueue<T>::ExplicitQueue() :
		Queue<T>(),
		list_(new LinkedList<T>())
	{
	}

	template<typename T>
	ExplicitQueue<T>::ExplicitQueue(ExplicitQueue<T>& other) :
		ExplicitQueue()
	{
		assign(other);
	}

	template<typename T>
	ExplicitQueue<T>::~ExplicitQueue()
	{
		delete this->list_;
		this->list_ = nullptr;
	}

	template<typename T>
	inline Structure& ExplicitQueue<T>::assign(Structure& other)
	{
		if (this != &other) {
			//porovnat ci je spravna struktura
			//Ak by to nebol zasobnik tak mi to spadne pocas pretypovania
			ExplicitQueue<T>& otherQueue = dynamic_cast<ExplicitQueue<T>&>(other);
			//Nie je jedno, co tam pridam, lebo cez other sa nedostanem na list
			this->list_->assign(*otherQueue.list_);
		}


		return *this;
	}

	template<typename T>
	inline bool ExplicitQueue<T>::equals(Structure& other)
	{
		if (this == &other) {
			return true;
		}

		//Cez pointer aby som nedostal vynimku
		ExplicitQueue<T>* otherQueue = dynamic_cast<ExplicitQueue<T>*>(&other);
		//keby zavolam this->equals, isiel by som rekurzivne (tato metoda)
		//Keby to neplati, tak mi hodi nullptr
		return otherQueue != nullptr && this->list_->equals(*otherQueue->list_);
	}

	template<typename T>
	size_t ExplicitQueue<T>::size()
	{
		return this->list_->size();
	}

	template<typename T>
	inline void ExplicitQueue<T>::clear()
	{
		this->list_->clear();
	}

	template<typename T>
	inline void ExplicitQueue<T>::push(const T& data)
	{
		this->list_->add(data);
	}

	template<typename T>
	inline T ExplicitQueue<T>::pop()
	{
		return this->list_->removeAt(0);
	}

	template<typename T>
	inline T& ExplicitQueue<T>::peek()
	{
		return this->list_->at(0);
	}
}