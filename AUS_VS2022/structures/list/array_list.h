#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../array/array.h"

namespace structures
{
	/// <summary> Zoznam implementovany polom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class ArrayList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ArrayList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> ArrayList, z ktoreho sa prevezmu vlastnosti. </param>
		ArrayList(ArrayList<T>& other);

		/// <summary> Destruktor. </summary>
		~ArrayList();

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
		bool equals(Structure& other);

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

	private:
		/// <summary> Pole s datami. </summary>
		Array<T>* array_;
		/// <summary> Pocet prvkov v zozname. </summary>
		size_t size_;

	private:
		/// <summary> Rozsiri kapacitu zoznamu. </summary>
		void enlarge();

		/// <summary> Iterator pre ArrayList. </summary>
		class ArrayListIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "arrayList"> Zoznam, cez ktory iteruje. </param>
			/// <param name = "position"> Pozicia, na ktorej zacina. </param>
			ArrayListIterator(ArrayList<T>* arrayList, int position);

			/// <summary> Destruktor. </summary>
			~ArrayListIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator= (Iterator<T>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(Iterator<T>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			T operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<T>& operator++() override;

		private:
			/// <summary> Zoznam, cez ktory iteruje. </summary>
			ArrayList<T>* arrayList_;
			/// <summary> Aktualna pozicia v zozname. </summary>
			int position_;
		};
	};

	template<typename T>
	inline ArrayList<T>::ArrayList() :
		List<T>(),
		array_(new Array<T>(4)),
		size_(0)
	{
	}

	template<typename T>
	inline ArrayList<T>::ArrayList(ArrayList<T>& other) :
		List<T>(),
		array_(new Array<T>(*other.array_)),
		size_(other.size_)
	{
	}

	template<typename T>
	inline ArrayList<T>::~ArrayList()
	{
		this->clear();
		delete this->array_;
		this->array_ = nullptr;
	}

	template<typename T>
	inline size_t ArrayList<T>::size()
	{
		return this->size_;
	}

	template<typename T>
	inline Structure& ArrayList<T>::assign(Structure& other)
	{
		if (this != &other) {
			ArrayList<T>& otherAL = dynamic_cast<ArrayList<T>&>(other);
			if (this->array_->size() != otherAL.array_->size()) {
				//najskor musim vymazat, lebo by vznikol memory leak
				delete this->array_;
				//tu by sa mi stratil pointer
				this->array_ = new Array<T>(*otherAL.array_);
			}
			else {
				this->array_->assign(*otherAL.array_);
			}

			this->size_ = otherAL.size_;
		}

		return *this;
	}

	template<typename T>
	inline bool ArrayList<T>::equals(Structure& other)
	{
		//Nechcem aby vyhadzovalo vynimku, takze dyncast cey pointer
		ArrayList<T>* otherAL = dynamic_cast<ArrayList<T>*>(&other);
		if (otherAL == nullptr) {
			return false;
		}
		if (this->size_ != otherAL->size_) {
			return false;
		}

		for (int i = 0; i < this->size_; i++) {
			if (this->array_->at(i) != otherAL->array_->at(i)) {
				return false;
			}
		}
		return true;

	}

	template<typename T>
	inline T& ArrayList<T>::at(int index)
	{
		if (index < 0 || index >= this->size_) {
			throw std::out_of_range("ArrayList<T>::at: Invalid index.");
		}
		return this->array_->at(index);
	}

	template<typename T>
	inline void ArrayList<T>::add(const T& data)
	{
		enlarge();
		this->array_->at(static_cast<int>(this->size_)) = data;
		this->size_++;
	}

	template<typename T>
	inline void ArrayList<T>::insert(const T& data, int index)
	{
		if (index < 0 || index > this->size_) {
			throw std::out_of_range("ArrayList<T>::insert: Invalid index.");
		}
		enlarge();
		Array<T>::copy(*this->array_, index, *this->array_, index + 1, static_cast<int>(this->size_) - index);
		this->array_->at(index) = data;
		this->size_++;
	}

	template<typename T>
	inline bool ArrayList<T>::tryRemove(const T& data)
	{
		int index = this->getIndexOf(data);
		if (index < 0) {
			return false;
		}
		else {
			this->removeAt(index);
			return true;
		}

	}

	template<typename T>
	inline T ArrayList<T>::removeAt(int index)
	{
		if (index < 0 || index >= this->size_) {
			throw std::out_of_range("ArrayList<T>::removeAt: Invalid index.");
		}
		T data = this->array_->at(index);

		Array<T>::copy(*this->array_, index + 1, *this->array_, index, static_cast<int>(this->size_) - index - 1);
		this->size_--;
		return data;
	}

	template<typename T>
	inline int ArrayList<T>::getIndexOf(const T& data)
	{
		for (int i = 0; i < this->size_; i++) {
			if (this->array_->at(i) == data) {
				return i;
			}
		}
		//nic som nenasiel
		return -1;
	}

	template<typename T>
	inline void ArrayList<T>::clear()
	{
		this->size_ = 0;
	}

	template<typename T>
	inline Iterator<T>* ArrayList<T>::getBeginIterator()
	{
		return new ArrayListIterator(this, 0);
	}

	template<typename T>
	inline Iterator<T>* ArrayList<T>::getEndIterator()
	{
		return new ArrayListIterator(this, static_cast<int>(this->size_));
	}

	template<typename T>
	inline void ArrayList<T>::enlarge()
	{
		//
		if (this->size_ >= this->array_->size()) {
			//ternarny operator
			Array<T>* newArray = new Array<T>(this->size_ > 0 ? 2 * this->size_ : 4);
			//musim dereferencovat
			Array<T>::copy(*this->array_, 0, *newArray, 0, static_cast<int>(this->size_));
			delete this->array_;
			this->array_ = newArray;
		}
	}

	template<typename T>
	inline ArrayList<T>::ArrayListIterator::ArrayListIterator(ArrayList<T>* arrayList, int position) :
		arrayList_(arrayList),
		position_(position)
	{
	}

	template<typename T>
	inline ArrayList<T>::ArrayListIterator::~ArrayListIterator()
	{
		this->arrayList_ = nullptr;
		this->position_ = 0;
	}

	template<typename T>
	inline Iterator<T>& ArrayList<T>::ArrayListIterator::operator=(Iterator<T>& other)
	{
		if (this != &other) {
			ArrayListIterator& it = dynamic_cast<ArrayListIterator&>(other);
			this->arrayList_ = it.arrayList_;
			this->position_ = it.position_;
		}
		return *this;
	}

	template<typename T>
	inline bool ArrayList<T>::ArrayListIterator::operator!=(Iterator<T>& other)
	{
		ArrayListIterator& it = dynamic_cast<ArrayListIterator&>(other);
		return this->arrayList_ != it.arrayList_ || this->position_ != it.position_;
	}

	template<typename T>
	inline T ArrayList<T>::ArrayListIterator::operator*()
	{
		return this->arrayList_->at(this->position_);
	}

	template<typename T>
	inline Iterator<T>& ArrayList<T>::ArrayListIterator::operator++()
	{
		++this->position_;
		return *this;
	}

}