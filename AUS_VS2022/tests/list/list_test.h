#pragma once

#include "../test.h"
#include "../../structures/list/array_list.h"
#include "../../structures/list/linked_list.h"
#include "../../structures/list/double_linked_list.h"
#include "../../structures/_logger/logger.h"
#include "../../structures/_logger/file_log_consumer.h"
#include <functional>

namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania listu avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class ListTestInterface
		: public SimpleTest
	{
	public:
		ListTestInterface(std::string name);
		void test() override;

	protected:
		virtual structures::List<int>* makeList() const = 0;
	};

	/// <summary>
	/// Zavola vsetky metody ArrayListu.
	/// </summary>
	class ArrayListTestInterface
		: public ListTestInterface
	{
	public:
		ArrayListTestInterface();

	protected:
		structures::List<int>* makeList() const override;
	};

	/// <summary>
	/// Zavola vsetky metody LinkedListu.
	/// </summary>
	class LinkedListTestInterface
		: public ListTestInterface
	{
	public:
		LinkedListTestInterface();

	protected:
		structures::List<int>* makeList() const override;
	};

	/// <summary>
	/// Zavola vsetky metody DoubleLinkedListu.
	/// </summary>
	class DoubleLinkedListTestInterface
		: public ListTestInterface
	{
	public:
		DoubleLinkedListTestInterface();

	protected:
		structures::List<int>* makeList() const override;
	};


	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju ArrayList.
	/// </summary>
	class ArrayListTestOverall
		: public ComplexTest
	{
	public:
		ArrayListTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju LinkedList.
	/// </summary>
	class LinkedListTestOverall
		: public ComplexTest
	{
	public:
		LinkedListTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju DoubleLinkedList.
	/// </summary>
	class DoubleLinkedListTestOverall
		: public ComplexTest
	{
	public:
		DoubleLinkedListTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju ArrayList a LinkedList.
	/// </summary>
	class ListTestOverall :
		public ComplexTest
	{
	public:
		ListTestOverall();
	};

	//Homework 
	/// <summary>
	/// Zahrna v sebe testy na overenie metody insert() a add()
	/// <summary>

	class ArrayListTestInsert
		: public SimpleTest
	{
	public:
		ArrayListTestInsert();
		void test() override;
	};

	//HomeWork
	/// <summary>
	/// Zahrna v sebe testy na overenie metody removeAt(),tryRemove()
	/// getIndexOf(), clear() a isEmpty()
	/// <summary>

	class ArrayListTestRemove
		: public SimpleTest {
	public:
		ArrayListTestRemove();
		void test() override;
	};

	//Homework 
	/// <summary>
	/// Zahrna v sebe testy na overenie metody insert() a add()
	/// <summary>

	class LinkedListTestInsert
		: public SimpleTest
	{
	public:
		LinkedListTestInsert();
		void test() override;
	};

	//HomeWork
	/// <summary>
	/// Zahrna v sebe testy na overenie metody removeAt(),tryRemove()
	/// getIndexOf(), clear() a isEmpty()
	/// <summary>

	class LinkedListTestRemove
		: public SimpleTest {
	public:
		LinkedListTestRemove();
		void test() override;
	};

	/// <summary>
	/// Zahrna v sebe testy na overenie metody isert,removeAt,At,getIndexOf
	/// <summary>
	class Zadanie2_TestMetod
		: public SimpleTest {
	public:
		Zadanie2_TestMetod();
		void test() override;
	};

	/// <summary>
	/// Zahrna test scenarov A,B,C v ulohe2, domace zadanie 2
	/// <summary>
	class Zadanie2_Uloha2
		: public SimpleTest {
	public:
		Zadanie2_Uloha2();
		template<typename T>
		void getMethodTime(structures::FileLogConsumer* fileLogger, structures::List<T>* list, std::string methodName);
		

		template<typename T>
		void uloha2(structures::List<T>* list,
			int ratioInsert, int ratioRemoveAt, int ratioAt, int ratioGetIndexOf,
			std::string nazov);
		void test() override;
	};

	class Zadanie2_Uloha3
		:public SimpleTest {
	public:
		Zadanie2_Uloha3();
		template<typename T>
		void uloha3(structures::List<T>* list, std::string methodName, std::string nazov);
		void test() override;
	};




}