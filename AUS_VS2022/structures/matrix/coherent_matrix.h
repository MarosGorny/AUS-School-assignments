#pragma once

#include "matrix.h"
#include "../array/array.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Implementacia matice v suvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class CoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		CoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		CoherentMatrix(CoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~CoherentMatrix();


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
		/// <summary> Pole s datami. </summary>
		Array<T>* array_;

		/// <summary> Pocet riadkov v zozname. </summary>
		size_t rows_;

		/// <summary> Pocet stlpcov v zozname. </summary>
		size_t columns_;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;
	};

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(size_t rowCount, size_t columnCount)
		:array_(new Array<T>(rowCount * columnCount)),
		rows_(rowCount),
		columns_(columnCount)
	{
	}

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(CoherentMatrix& other)
		:Matrix<T>(other),
		array_(new Array<T>(*other.array_)),
		rows_(other.rows_),
		columns_(other.columns_)
	{
	}

	template<typename T>
	inline CoherentMatrix<T>::~CoherentMatrix()
	{
		this->clear();
	}

	template<typename T>
	inline void CoherentMatrix<T>::clear()
	{
		this->rows_ = 0;
		this->columns_ = 0;
		delete this->array_;
		this->array_ = nullptr;
	}

	template<typename T>
	inline Structure& CoherentMatrix<T>::assign(Structure& other)
	{

		if (this != &other) {
			CoherentMatrix<T>& otherCohMatrix = dynamic_cast<CoherentMatrix<T>&>(other);
			if (this->columns_ != otherCohMatrix.columns_ || this->rows_ != otherCohMatrix.rows_) {
				throw std::length_error("CoherentMatrix<T>::assign: Invalid size.");
			}

			else {
				this->array_->assign(*otherCohMatrix.array_);
			}
		}

		return *this;

	}

	template<typename T>
	inline bool CoherentMatrix<T>::equals(Structure& other)
	{
		CoherentMatrix<T>* otherCohMatrix = dynamic_cast<CoherentMatrix<T>*>(&other);
		if (otherCohMatrix == nullptr) {
			//Nepodaril sa dynamic_cast
			return false;
		}

		if (this->columns_ != otherCohMatrix->columns_ || this->rows_ != otherCohMatrix->rows_) {
			return false;
		}

		for (int i = 0; i < this->size(); i++)
		{
			if (this->array_->at(i) != otherCohMatrix->array_->at(i)) {
				return false;
			}
		}

		return true;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::size()
	{
		return this->rows_ * this->columns_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getRowCount()
	{
		return this->rows_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getColumnCount()
	{
		return this->columns_;
	}

	template<typename T>
	inline T& CoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		
		if ((rowIndex < 0 || rowIndex >= this->rows_) || 
			(columnIndex < 0 || columnIndex >= this->columns_)) {
			throw std::out_of_range("CoherentMatrix<T>::at: Invalid index.");
		}
		

		return this->array_->at(static_cast<int>((rowIndex * columns_) + columnIndex));
	}
}