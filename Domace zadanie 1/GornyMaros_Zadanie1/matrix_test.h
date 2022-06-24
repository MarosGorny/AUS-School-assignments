#pragma once

#include "../test.h"
#include "../../structures/matrix/matrix.h"
#include "../../structures/_logger/logger.h"
#include "../../structures/_logger/file_log_consumer.h"
#include <functional>

namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania matice avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class MatrixTestInterface
		: public SimpleTest
	{
	public:
		MatrixTestInterface();
		void test() override;

	protected:
		virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;
	};

	/// <summary>
	/// Zavola vsetky metody koherentnej matice.
	/// </summary>
	class CoherentMatrixTestInterface
		: public MatrixTestInterface
	{
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	/// <summary>
	/// Zavola vsetky metody nekoherentnej matice.
	/// </summary>
	class IncoherentMatrixTestInterface
		: public MatrixTestInterface
	{
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju CoherentMatrix.
	/// </summary>
	class CoherentMatrixTestOverall
		: public ComplexTest
	{
	public:
		CoherentMatrixTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju IncoherentMatrix.
	/// </summary>
	class IncoherentMatrixTestOverall
		: public ComplexTest
	{
	public:
		IncoherentMatrixTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju CoherrentMatrix a IncoherrentMatrix.
	/// </summary>
	class MatrixTestOverall
		: public ComplexTest
	{
	public:
		MatrixTestOverall();
	};

	/// <summary>
	/// Zahrna testy fukncii CoherrentMatrix 
	/// </summary>
	class MatrixCohTestFunctions
		:public SimpleTest
	{
	public:
		MatrixCohTestFunctions();
		void test() override;
	};

	/// <summary>
	/// Zahrna testy fukncii IncoherrentMatrix 
	/// </summary>
	class MatrixIncohTestFunctions
		:public SimpleTest
	{
	public:
		MatrixIncohTestFunctions();
		void test() override;
	};

	/// <summary>
	/// Zahrna test scenarov A,B,C,D v ulohe2
	/// </summary>
	class MatrixScenar
		:public SimpleTest 
	{
	public:
		MatrixScenar();
		template<typename T>
		void getRowColummnTime(structures::FileLogConsumer* fileLogger,structures::Matrix<T>* matica, std::string method, int pocetRiadkov, int pocetStlpcov);
		template<typename T>
		void getAtCountTime(structures::FileLogConsumer* fileLogger,structures::Matrix<T>* matica,int pocetRiadkov, int pocetStlpcov);
		template<typename T>
		void uloha2(structures::Matrix<T>* matica,
			int ratioGetRow, int ratioGetColumn, int ratioAt,
			std::string nazov);
		void test() override;

	};

	/// <summary>
	/// Zahrna test scenarov metod at() a assign()
	/// </summary>
	class MatrixUloha3
		:public SimpleTest
	{
	public:
		
		MatrixUloha3();
		template <typename T>
		void otestujMetodu(structures::Matrix<T>& matica, std::string metoda, std::string typMatice);
		void test() override;
	};
	
}