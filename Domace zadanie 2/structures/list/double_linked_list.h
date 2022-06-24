#pragma once

#include "list.h"

namespace structures
{
	// implementacne tipy: 
	//  - namiesto triedy List<T> mozete v triede DoubleLinkedList<T> 
	//    zdedit jednostranne zretazeny zoznam (LinkedList<T>).
	//    ak tak urobite, mozete mnoho metod odstranit a prekryt iba tie, 
	//    ktore maju z pohladu obojsmerne zretazeneho zoznamu vyznam a
	//    zvysok nechat na predka.
	//  - nezabudnite si vytvorit triedu pre prvok obojstranne zretazeneho zoznamu.
	//    opat tento prvok mozete zdedit z prvku jednostranne zretazeneho zoznamu.
	//  - ak vyuzijete dedicnost, budete moct vyuzit predkove iteratory, 
	//    takze ich nebudete musiet implementovat.
	
    /// <summary> Obojstranne zretazeny zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class DoubleLinkedList : public List<T> 
	{
    public:
        /// <summary> Konstruktor. </summary>
        DoubleLinkedList();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> DoubleLinkedList, z ktoreho sa prevezmu vlastnosti. </param>
        DoubleLinkedList(DoubleLinkedList<T>& other);

        /// <summary> Destruktor. </summary>
        ~DoubleLinkedList();

        /// <summary> Vrati pocet prvkov v zozname. </summary>
        /// <returns> Pocet prvkov v zozname. </returns>
        size_t size() override;

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        Structure& assign(Structure& other) override;

        /// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
        bool equals(Structure& other) override;

        /// <summary> Vrati adresou prvok na indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Adresa prvku na danom indexe. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T& at(int index) override;

        /// <summary> Prida prvok do zoznamu. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        void add(const T& data) override;

        /// <summary> Vlozi prvok do zoznamu na dany index. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        /// <param name = "index"> Index prvku. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        /// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
        void insert(const T& data, int index) override;

        /// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
        /// <param name = "data"> Odstranovany prvok. </param>
        /// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
        bool tryRemove(const T& data) override;

        /// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Odstraneny prvok. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T removeAt(int index) override;

        /// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
        /// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
        /// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
        int getIndexOf(const T& data) override;

        /// <summary> Vymaze zoznam. </summary>
        void clear() override;

        /// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
        /// <returns> Iterator na zaciatok struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getBeginIterator() override;

        /// <summary> Vrati skutocny iterator na koniec struktury </summary>
        /// <returns> Iterator na koniec struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getEndIterator() override;
	};

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList()
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::DoubleLinkedList: Not implemented yet.");
    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T>& other)
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::DoubleLinkedList: Not implemented yet.");
    }

    template<typename T>
    inline DoubleLinkedList<T>::~DoubleLinkedList()
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::~DoubleLinkedList: Not implemented yet.");
    }

    template<typename T>
    inline size_t DoubleLinkedList<T>::size()
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::size: Not implemented yet.");
    }

    template<typename T>
    inline Structure& DoubleLinkedList<T>::assign(Structure& other)
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::assign: Not implemented yet.");
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::equals(Structure& other)
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::equals: Not implemented yet.");
    }

    template<typename T>
    inline T& DoubleLinkedList<T>::at(int index)
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::at: Not implemented yet.");
    }

    template<typename T>
    inline void DoubleLinkedList<T>::add(const T& data)
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::add: Not implemented yet.");
    }

    template<typename T>
    inline void DoubleLinkedList<T>::insert(const T& data, int index)
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::insert: Not implemented yet.");
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::tryRemove(const T& data)
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::tryRemove: Not implemented yet.");
    }

    template<typename T>
    inline T DoubleLinkedList<T>::removeAt(int index)
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::removeAt: Not implemented yet.");
    }

    template<typename T>
    inline int DoubleLinkedList<T>::getIndexOf(const T& data)
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::getIndexOf: Not implemented yet.");
    }

    template<typename T>
    inline void DoubleLinkedList<T>::clear()
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::clear: Not implemented yet.");
    }

    template<typename T>
    inline Iterator<T>* DoubleLinkedList<T>::getBeginIterator()
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::getBeginIterator: Not implemented yet.");
    }

    template<typename T>
    inline Iterator<T>* DoubleLinkedList<T>::getEndIterator()
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::getEndIterator: Not implemented yet.");
    }
}