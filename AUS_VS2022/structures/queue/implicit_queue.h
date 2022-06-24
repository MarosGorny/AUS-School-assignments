#pragma once

#include "queue.h"
#include "../array/array.h"

#include <stdexcept>

namespace structures
{
	/// <summary> Implicitny front. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo fronte. </typepram>
	template<typename T>
	class ImplicitQueue : public Queue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ImplicitQueue();

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "capacity"> Maximalna velkost frontu. </param>
		ImplicitQueue(size_t capacity);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Implicitny front, z ktoreho sa prevezmu vlastnosti. </param>
		ImplicitQueue(ImplicitQueue<T>& other);

		/// <summary> Destruktor. </summary>
		~ImplicitQueue();

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
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front plny. </exception>
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
		/// <summary> Pole, pomocou ktoreho je implementovany front. </summary>
		Array<T>* array_;

		/// <summary> Index prveho prvku vo fronte. </summary>
		int startIndex_;

		/// <summary> Pocet prvkov vo fronte. </summary>
		size_t size_;
	};

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue() :
		ImplicitQueue(10)
	{
	}

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue(size_t capacity) :
		Queue<T>(),
		array_(new Array<T>(capacity)),
		startIndex_(0),
		size_(0)
	{
	}

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue(ImplicitQueue<T>& other) :
		Queue<T>(other),
		array_(new Array<T>(*other.array_)),
		startIndex_(other.startIndex_),
		size_(other.size_)
	{
	}

	template<typename T>
	ImplicitQueue<T>::~ImplicitQueue()
	{
		delete this->array_;
		this->array_ = nullptr;
		this->size_ = 0;
		this->startIndex_ = 0;
	}

	template<typename T>
	inline Structure& ImplicitQueue<T>::assign(Structure& other)
	{
		if (this != &other) {
			//porovnat ci je spravna struktura
			//Ak by to nebol zasobnik tak mi to spadne pocas pretypovania
			ImplicitQueue<T>& otherQueue = dynamic_cast<ImplicitQueue<T>&>(other);

			if (this->array_->size() == otherQueue.array_->size()) {
				this->array_->assign(*otherQueue.array_);
			}
			else {
				delete this->array_;
				this->array_ = new Array<T>(*otherQueue.array_);
			}
			this->startIndex_ = otherQueue.startIndex_;
			this->size_ = otherQueue.size();
		}

		return *this;
	}

	template<typename T>
	size_t ImplicitQueue<T>::size()
	{
		return this->size_;
	}

	template<typename T>
	inline bool ImplicitQueue<T>::equals(Structure& other)
	{
		if (this == &other) {
			return true;
		}

		//Cez pointer aby som nedostal vynimku
		ImplicitQueue<T>* otherQueue = dynamic_cast<ImplicitQueue<T>*>(&other);
		//Keby to neplati, tak mi hodi nullptr
		if (otherQueue == nullptr) {
			return false;
		}

		if (this->size_ != otherQueue->size()) {
			return false;
		}
		int thisIndex = this->startIndex_;
		int otherIndex = otherQueue->startIndex_;
		for (int i = 0; i < this->size_; i++) {
			if (this->array_->at(thisIndex) != otherQueue->array_->at(otherIndex)) {
				return false;
			}
			thisIndex = (thisIndex + 1) % this->array_->size();
			otherIndex = (otherIndex + 1) % otherQueue->array_->size();
		}

		return true;


	}

	template<typename T>
	inline void ImplicitQueue<T>::clear()
	{
		this->startIndex_ = 0;
		this->size_ = 0;
	}

	template<typename T>
	inline void ImplicitQueue<T>::push(const T& data)
	{
		if (this->size_ >= this->array_->size()) {
			throw std::out_of_range("ImplicitQueue<T>::push: Implicit queue is full.");
		}
		this->array_->at(static_cast<int>((this->startIndex_ + this->size_) % this->array_->size())) = data;
		this->size_++;
	}

	template<typename T>
	inline T ImplicitQueue<T>::pop()
	{
		if (this->size_ == 0) {
			throw std::out_of_range("ImplicitQueue<T>::pop: Implicit queue is full.");
		}

		T data = this->array_->at(this->startIndex_);
		this->startIndex_ = ((this->startIndex_ + 1) % this->array_->size());
		this->size_--;
		return data;
	}

	template<typename T>
	inline T& ImplicitQueue<T>::peek()
	{
		if (this->size_ == 0) {
			throw std::out_of_range("ImplicitQueue<T>::peek: Implicit queue is full.");
		}

		return this->array_->at(this->startIndex_);
	}
}