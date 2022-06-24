#pragma once

#include "priority_queue_list.h"
#include "../list/linked_list.h"

namespace structures
{
	/// <summary> Prioritny front implementovany neutriednym LinkedList-om. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class PriorityQueueLinkedList : public PriorityQueueList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueLinkedList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prioritny front implementovany neutriednym LinkedList-om, z ktoreho sa prevezmu vlastnosti. </param>
		PriorityQueueLinkedList(PriorityQueueLinkedList<T>& other);

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho neutriednym LinkedList-om. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;
	};

	template<typename T>
	PriorityQueueLinkedList<T>::PriorityQueueLinkedList() :
		PriorityQueueList<T>(new LinkedList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueLinkedList<T>::PriorityQueueLinkedList(PriorityQueueLinkedList<T>& other) :
		PriorityQueueList<T>()
	{
		//Vymayat hore a pridat len konstruktor, je to vsade takto zle
		this->assign(other);
	}

	template<typename T>
	inline Structure& PriorityQueueLinkedList<T>::assign(Structure& other)
	{
		//pretypovanie na strukturu ktoru robim
		//Ak sa nepodari, tak to zhavaruje a nic sa neudeje
		return PriorityQueueList<T>::assignPrioQueueList(dynamic_cast<PriorityQueueLinkedList<T>&>(other));
	}

	template<typename T>
	inline void PriorityQueueLinkedList<T>::push(int priority, const T& data)
	{
		//zabalit data
		PriorityQueueItem<T>* item = new PriorityQueueItem<T>(priority, data);
		//vyvolanie atributu predka to iste ako this->list_
		PriorityQueueList<T>::list_->add(item);
	}
}