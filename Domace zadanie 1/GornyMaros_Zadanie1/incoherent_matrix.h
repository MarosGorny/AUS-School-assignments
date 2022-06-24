#pragma once

#include "matrix.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Implementacia matice v nesuvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class IncoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		IncoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		IncoherentMatrix(IncoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~IncoherentMatrix();

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;

		/// <summary>
		/// Ak je to mozne (parametrom je matica, ktora ma rovnake rozmery ako ako aktualna matica),
		/// tak skopiruje vlastnosti z matice odovzdanej ako parameter.
		/// Ak to nie je mozne, vyhodi sa vynimka.
		/// </summary>
		/// <param name = "other"> Odkaz na strukturu, z ktorej maju prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		/// <exception cref="std::length_error"> Vyhodena, ak sa velkost riadku alebo stlpca nezhoduje s maticou. </exception>
		Structure& assign(Structure& other) override;

		/// <summary>
		/// Ak je parametrom matica a obsah porovnavanych matic je rovnaky,
		/// tak vrati hodnotu true. V opacnom pripade vrati hodnotu false.
		/// </summary>
		/// <param name="other"> Odkaz na strukturu, s ktorou sa ma tato matica porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Pocet vsetkych prvkov v matici. </summary>
		/// <returns> Pocet prvkov v matici. </returns>
		size_t size() override;

		/// <summary> Vrati pocet riadkov v matici. </summary>
		/// <returns> Pocet riadkov matice. </returns>
		size_t getRowCount() override;

		/// <summary> Vrati pocet stlpcov matice. </summary>
		/// <returns> Pocet stlpcov matice. </returns>
		size_t getColumnCount() override;

		/// <summary> Vrati odkaz na prvok v danom riadku a stlpci. </summary>
		/// <param name="rowIndex"> Index riadku. </param>
		/// <param name="columnIndex"> Index stlpca. </param>
		/// <returns> Odkaz na prvok na danych indexoch. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		T& at(int rowIndex, int columnIndex) override;

	private:
		/// <summary> Pole Poli s datami. </summary>
		Array<Array<T>*>* arrays_;

		/// <summary> Pocet riadkov v zozname. </summary>
		size_t rows_;

		/// <summary> Pocet stlpcov v zozname. </summary>
		size_t columns_;
	};

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(size_t rowCount, size_t columnCount)
		:rows_(rowCount),
		columns_(columnCount)
	{
		this->arrays_ = new Array<Array<T>*>(rowCount);

		for (int i = 0; i < rowCount; i++) {
			this->arrays_->at(i) = new Array<T>(columnCount);
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(IncoherentMatrix& other)
		:IncoherentMatrix<T>(other.rows_,other.columns_)
	{
		this->assign(other);
	}

	template<typename T>
	inline IncoherentMatrix<T>::~IncoherentMatrix()
	{
		this->clear();
	}

	template<typename T>
	inline void IncoherentMatrix<T>::clear() {
		for (int i = 0; i < rows_; i++) {
			delete this->arrays_->at(i);
			this->arrays_->at(i) = nullptr;
		}

		delete this->arrays_;
		this->arrays_ = nullptr;
	}

	template<typename T>
	inline Structure& IncoherentMatrix<T>::assign(Structure& other)
	{
		if (this != &other) {
			IncoherentMatrix<T>& otherIM = dynamic_cast<IncoherentMatrix<T>&>(other);
			if (this->columns_ != otherIM.columns_ || this->rows_ != otherIM.rows_) {
				throw std::length_error("IncoherentMatrix<T>::assign: Invalid size.");
			}

			else {
				this->clear();

				this->arrays_ = new Array<Array<T>*>(otherIM.rows_);

				for (int i = 0; i < otherIM.rows_; i++) {
					this->arrays_->at(i) = new Array<T>(*otherIM.arrays_->at(i));
				}

			}
		}

		return *this;
	}

	template<typename T>
	inline bool IncoherentMatrix<T>::equals(Structure& other)
	{
		IncoherentMatrix<T>* otherIM = dynamic_cast<IncoherentMatrix<T>*>(&other);
		if (otherIM == nullptr) {
			//Nepodaril sa dynamic_cast
			return false;
		}

		if (this->columns_ != otherIM->columns_ || this->rows_ != otherIM->rows_) {
			return false;
		}

		for (int i = 0; i < this->rows_; i++)
		{
			for (int j = 0; j < this->columns_; j++)
				if (this->at(i,j) != otherIM->at(i,j)) {
					return false;
				}
		}

		return true;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::size()
	{
		return this->rows_ * this->columns_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getRowCount()
	{
		return this->rows_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getColumnCount()
	{
		return this->columns_;
	}

	template<typename T>
	inline T& IncoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		if ((rowIndex < 0 || rowIndex >= this->rows_) ||
			(columnIndex < 0 || columnIndex >= this->columns_)) {
			throw std::out_of_range("IncoherentMatrix<T>::at: Invalid index.");
		}

		return this->arrays_->at(rowIndex)->at(columnIndex);
	}
}