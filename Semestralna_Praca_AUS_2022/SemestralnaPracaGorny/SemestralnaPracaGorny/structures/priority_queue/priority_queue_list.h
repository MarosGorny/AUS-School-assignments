#pragma once

#include "priority_queue.h"
#include "../list/list.h"
#include <stdexcept>

namespace structures
{
    /// <summary> Spolocny predok pre vsetky prioritne fronty, ktorych implementujucim typom je zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
    template<typename T>
    class PriorityQueueList : public PriorityQueue<T>
    {
    public:
        /// <summary> Destruktor. </summary>
        ~PriorityQueueList();

        /// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom zoznamom. </summary>
        /// <returns> Pocet prvkov v prioritnom fronte implementovanom zoznamom. </returns>
        size_t size() override;

        /// <summary> Vymaze obsah prioritneho frontu implementovaneho zoznamom. </summary>
        void clear() override;

        /// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho zoznamom. </summary>
        /// <returns> Odstraneny prvok. </returns>
        /// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>
        T pop() override;

        /// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
        /// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
        /// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>
        T& peek() override;

        /// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
        /// <returns> Priorita prvku s najvacsou prioritou. </returns>
        /// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>
        int peekPriority() override;

    protected:
        /// <summary> Konstruktor. </summary>
        /// <param name = "list"> Zoznam, do ktoreho sa budu ukladat prvky prioritneho frontu. </param>
        /// <remarks>
        /// Potomkovia ako list vlozia instanciu implicitne alebo explicitne implementovaneho zoznamu.
        /// Prioritny front implementovany zoznamom dealokuje tento objekt.
        /// </remarks>
        PriorityQueueList(List<PriorityQueueItem<T>*>* list);
        //Abstraktna trieda

        /// <summary> Vrati index v zozname, na ktorom sa nachadza prvok s najvacsou prioritou. </summary>
        /// <returns> Index prvku s najvacsou prioritou. </returns>
        /// <exception cref="std::logic_error"> Vyhodena, ak je zoznam prazdny. </exception>
        virtual int indexOfPeek();

        /// <summary> Priradenie struktury. Pomocna metoda, ktora prebera referenciu, ktoru posle potomok. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        /// <summary>
        Structure& assignPrioQueueList(Structure& other);

    protected:
        /// <summary> Smernik na zoznam, do ktoreho sa ukladaju prvky prioritneho frontu. </summary>
        List<PriorityQueueItem<T>*>* list_;
    };

    template<typename T>
    inline PriorityQueueList<T>::PriorityQueueList(List<PriorityQueueItem<T>*>* list) :
        list_(list)
    {
    }

    template<typename T>
    inline PriorityQueueList<T>::~PriorityQueueList()
    {
        this->clear();
        delete this->list_;
        this->list_ = nullptr;
    }

    template<typename T>
    inline size_t PriorityQueueList<T>::size()
    {
        return this->list_->size();
    }

    template<typename T>
    inline void PriorityQueueList<T>::clear()
    {
        //nemozem zavolat clear hned na zaciatku, lebo v zozname boli pointre
        //takze stranim ukazovatela a mam leaky

        //V pripade for each, garantujeme, ze to prejdem N-kovou zlozitostou
        for (PriorityQueueItem<T>* item : *this->list_) {
            delete item;
        }

        this->list_->clear();
    }

    template<typename T>
    inline int PriorityQueueList<T>::indexOfPeek()
    {
        //protected, pristupne len v tejto triede a potomkoch, nie z vonka
        
        //V pripade for each, garantujeme, ze to prejdem N-kovou zlozitostou
        int min = this->list_->at(0)->getPriority();
        int index = 0;
        int minIndex = 0;
        for (PriorityQueueItem<T>* item : *this->list_) {
            if (item->getPriority() < min) {
                min = item->getPriority();
                minIndex = index;
            }
            index++;
        }
        return minIndex;
    }

    template<typename T>
    inline Structure& PriorityQueueList<T>::assignPrioQueueList(Structure& other)
    {
        if (this != &other) {
            PriorityQueueList<T>& otherPQ = dynamic_cast<PriorityQueueList<T>&>(other);
            //nemozem len list assignut lebo by vznikla plytka kopia 
            this->clear();

            //for each prepisany na while
            Iterator<PriorityQueueItem<T>*>* it  = otherPQ.list_->getBeginIterator();
            Iterator<PriorityQueueItem<T>*>* end = otherPQ.list_->getEndIterator();
            
            //Objekt iterator porovnaj s endovym iteratorom
            while (*it != *end) {
                PriorityQueueItem<T>* item = *(*it); //spristupneny objekt iterator
                this->list_->add(new PriorityQueueItem<T>(*item));
                ++(*it);
            }

            delete it;
            delete end;
        }

        return *this;
    }

    template<typename T>
    inline T PriorityQueueList<T>::pop()
    {
        if (this->list_->size() == 0) {
            throw std::logic_error("PriorityQueueList<T>::pop: List is empty!!");
        }

        //Najprv si ho musim zapamatat aby som ho mohol deletnut a vratit
        PriorityQueueItem<T>* item = this->list_->removeAt(this->indexOfPeek());
        T data = item->accessData();

        delete item;
        item = nullptr;

        return data;
    }

    template<typename T>
    inline T& PriorityQueueList<T>::peek()
    {
        return this->list_->at(this->indexOfPeek())->accessData();
    }

    template<typename T>
    inline int PriorityQueueList<T>::peekPriority()
    {
        return this->list_->at(this->indexOfPeek())->getPriority();
    }
}