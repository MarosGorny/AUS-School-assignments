#pragma once

#include "../test.h"
#include "../../structures/table/table.h"
#include "../../structures/array/array.h"
#include "../../structures/list/array_list.h"
#include "../../structures/_logger/file_log_consumer.h"


namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania tabulky avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class TableTestInterface
		: public SimpleTest
	{
	public:
		TableTestInterface();
		void test() override;

	protected:
		virtual structures::Table<int, int>* makeTable() = 0;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class BinarySearchTreeTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class HashTableTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class LinkedTableTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class SortedSequenceTableTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class TreapTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class UnsortedSequenceTableTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class BinarySearchTreeTestOverall
		: public ComplexTest
	{
	public:
		BinarySearchTreeTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class HashTableTestOverall
		: public ComplexTest
	{
	public:
		HashTableTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class LinkedTableTestOverall
		: public ComplexTest
	{
	public:
		LinkedTableTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class SortedSequenceTableTestOverall
		: public ComplexTest
	{
	public:
		SortedSequenceTableTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class TreapTestOverall
		: public ComplexTest
	{
	public:
		TreapTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class UnsortedSequenceTableTestOverall
		: public ComplexTest
	{
	public:
		UnsortedSequenceTableTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju tabulku.
	/// </summary>
	class TableTestOverall
		: public ComplexTest
	{
	public:
		TableTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe testy fuknci(UseCases), ktore testuju binary search tree.
	/// </summary>
	class BinarySearchTreeFunctionsTest
		: public SimpleTest
	{
	public:
		BinarySearchTreeFunctionsTest();
		void test() override;
	};

	/// <summary>
	/// Zahrna v sebe testy fuknci(UseCases), ktore testuju binary search tree.
	/// </summary>
	class SortedSequenceTableFunctionsTest
		: public SimpleTest
	{
	public:
		SortedSequenceTableFunctionsTest();
		void test() override;
	};

	/// <summary>
	/// Zahrna test scenarov A,B,C v ulohe2, domace zadanie 3
	/// <summary>
	class Zadanie4_Uloha2
		: public SimpleTest {
	public:
		Zadanie4_Uloha2();

		~Zadanie4_Uloha2();

		/// <summary> Do loggeru zapise cas metody ktora sa vybrala. </summary>
		/// <param name = "fileLogger"> Pointer na File Logger do ktoreho sa cas bude zapisovat. </param>
		/// <param name = "priorityQueue"> Pointer na Table v ktorom sa budu vykonavat akcie. </param>
		/// <param name = "methodName"> Nazov metody ktora sa ma vykonat. </param>
		template<typename K, typename T>
		void getMethodTime(structures::FileLogConsumer* fileLogger, structures::Table<K, T>* table, std::string methodName);

		/// <summary> Rozdelenie volania metod podla pomeru funkcii, vykonanie urcity pocet volani a nasledne zapisanie dat do CSV suboru. </summary>
		/// <param name = "priorityQueue"> Pointer na Prioritny front v ktorom sa budu vykonavat akcie. </param>
		/// <param name = "ratioInsert"> Perecentualny pomer volania metody Insert() z celkovu 100 percentneho pomeru. </param>
		/// <param name = "ratioRemove"> Perecentualny pomer volania metody Remove() z celkovu 100 percentneho pomeru. </param>
		/// <param name = "ratioPeek"> Perecentualny pomer volania metody ratioTryFind() z celkovu 100 percentneho pomeru. </param>
		/// <param name = "nazov"> Nazov CSV suboru ktory sa zapise. (bez .CSV pripony) </param>
		template<typename K, typename T>
		void uloha2(structures::Table<K, T>* table, int ratioInsert, int ratioRemove, int ratioTryFind, std::string nazov);

		template<typename K, typename T>
		void insertRepeat(structures::FileLogConsumer* fileLogger, structures::Table<K, T>* table, int numberOfItems,int keyMaxIndex,bool time);

		template<typename K, typename T>
		void insertThenRemove(structures::FileLogConsumer* fileLogger, structures::Table<K, T>* table, int numberOfItems);

		template<typename K, typename T>
		void RemoveThenTryFind(structures::FileLogConsumer* fileLogger, structures::Table<K, T>* table, int numberOfItems);


		/// <summary>
		/// Vytvorenie table a nasledne vykonanie akcii pre ulohu 2, zadanie 4.
		/// <summary>
		void test() override;
	protected:
		structures::ArrayList<int>* keyArray_;
		structures::Array<bool>* isInside_;
	};

	/// <summary>
	/// Zahrna test rychlosti metod insert remove tryFind v ulohe3, domace zadanie 4
	/// <summary>
	class Zadanie4_Uloha3
		:public SimpleTest {
	public:
		Zadanie4_Uloha3();

		template<typename K,typename T>
		void uloha3(structures::Table<K,T>* table, std::string methodName, std::string nazov);


		void test() override;
	private:
		structures::ArrayList<int>* keyArray_;
		structures::Array<bool>* isInside_;
	};
}