#include "list_test.h"

namespace tests
{
// ListTestInterface:

	ListTestInterface::ListTestInterface(std::string name) :
		SimpleTest(std::move(name))
	{
	}

	void ListTestInterface::test()
	{
		int x = 0;
		structures::List<int>* list = this->makeList();
		list->add(x);
		list->assign(*list);
		list->clear();
		delete list->getBeginIterator();
		delete list->getEndIterator();
		list->getIndexOf(x);
		list->insert(x, x);
		list->isEmpty();
		list->operator[](0);
		list->removeAt(0);
		list->size();
		list->tryRemove(x);
		delete list;
		this->logPass("Compiled.");
	}

// ArrayListTestInterface:

	ArrayListTestInterface::ArrayListTestInterface() :
		ListTestInterface("Interface")
	{
	}

	structures::List<int>* ArrayListTestInterface::makeList() const
	{
		return new structures::ArrayList<int>();
	}

// LinkedListTestInterface:

	LinkedListTestInterface::LinkedListTestInterface() :
		ListTestInterface("Interface")
	{
	}

	structures::List<int>* LinkedListTestInterface::makeList() const
	{
		return new structures::LinkedList<int>();
	}

// DoubleLinkedListTestInterface:

	DoubleLinkedListTestInterface::DoubleLinkedListTestInterface() :
		ListTestInterface("Interface")
	{
	}

	structures::List<int>* DoubleLinkedListTestInterface::makeList() const
	{
		return new structures::DoubleLinkedList<int>();
	}


// ArrayListTestOverall:

	ArrayListTestOverall::ArrayListTestOverall() :
		ComplexTest("ArrayList")
	{
		addTest(new ArrayListTestInterface());
		addTest(new ArrayListTestInsert());
		addTest(new ArrayListTestRemove());
	}

// LinkedListTestOverall:

	LinkedListTestOverall::LinkedListTestOverall() :
		ComplexTest("LinkedList")
	{
		addTest(new LinkedListTestInterface());
		addTest(new LinkedListTestInsert());
		addTest(new LinkedListTestRemove());
	}

// DoubleLinkedListTestOverall:

	DoubleLinkedListTestOverall::DoubleLinkedListTestOverall() :
		ComplexTest("DoubleLinkedList")
	{
		addTest(new DoubleLinkedListTestInterface());
		
	}

// ListTestOverall:

	ListTestOverall::ListTestOverall() :
		ComplexTest("List")
	{
		addTest(new ArrayListTestOverall());
		addTest(new LinkedListTestOverall());
		addTest(new DoubleLinkedListTestOverall());

		addTest(new Zadanie2_TestMetod());
		addTest(new Zadanie2_Uloha2());
		addTest(new Zadanie2_Uloha3());
		
	}
//ArrayListTestInsert:

	ArrayListTestInsert::ArrayListTestInsert()
		:SimpleTest("Insert and Add") {

	}

	void ArrayListTestInsert::test()
	{
		this->logInfo("Start of test ArrayListTestInsert");
		this->startStopwatch();
		//Vytvorte zoznam typu ArrayList<int>
		this->logInfo("Creating ArrayList<int>()");
		structures::ArrayList<int>* AL = new structures::ArrayList<int>();

		//Vložte pomocou metódy add na koniec zoznamu èísla 10, 20, 30, 40
		this->logInfo("Adding 10,20,30,40");
		for (int i{ 1 }; i < 5; i++) {
			AL->add(i*10);
		}
		
		// Overte pomocou metódy size, že má ve¾kos 4.
		this->assertTrue(AL->size() == 4,"size == 4");

		//Vložte pomocou metódy add na koniec zoznamu èísla 
			//100, 200, 300, 400 (dôjde k expanzii).
		this->logInfo("Adding 100,200,300,400 (expansion)");
		for (int i{ 1 }; i < 5; i++) {
			AL->add(i * 100);
		}

		//Overte pomocou metódy size, že má ve¾kos 8.
		this->assertTrue(AL->size() == 8, "size == 8");

		//Vložte na zaèiatok zoznamu pomocou metódy insert 9x èíslo 1.
		this->logInfo("Inserting on index 0: 9x number 1");
		for (size_t i{ 0 }; i < 9; i++) {
			AL->insert(1, 0);
		}

		// Overte pomocou metódy size, že má ve¾kos 17.
		this->assertTrue(AL->size() == 17, "size == 17");

		//Vložte pomocou metódy insert na index 0 
		//prvok 7, na index 4 prvok 77, na index 18 prvok 777 
		//a na index 20 prvok 7777
		this->logInfo("Insert on index 0: 7");
		AL->insert(7, 0);
		this->logInfo("Insert on index 4: 77");
		AL->insert(77, 4);
		this->logInfo("Insert on index 18: 777");
		AL->insert(777, 18);
		this->logInfo("Insert on index 20: 7777");
		AL->insert(7777, 20);

		//Overte pomocou metódy size, že má ve¾kos 21.
		this->assertTrue(AL->size() == 21, "size == 21");

		int expected[21]{7, 1, 1, 1, 77, 1, 1, 1, 1, 1, 1, 10, 20, 30, 40, 100, 200, 300, 777, 400, 7777};

		for (int i{ 0 }; i < AL->size(); i++) {
			this->assertTrue(AL->at(i) == expected[i], 
				"at("+std::to_string(i)+") == " + std::to_string(expected[i]));
		}

		delete AL;
		AL = nullptr;

		this->stopStopwatch();
		tests::DurationType duration = this->getElapsedTime();
		this->logInfo("Time of the test is " + std::to_string(duration.count()) + " ms");

		structures::Logger::getInstance().logDuration(100, duration, "ArrayListTestInsert TimeTest");


		this->logInfo("End of test ArrayListTestInsert");
	}

//ArrayListTestRemove
	ArrayListTestRemove::ArrayListTestRemove()
		:SimpleTest("Remove")
	{
	}

	void ArrayListTestRemove::test()
	{
		this->logInfo("Start of test ArrayListTestRemove");
		this->startStopwatch();
		//Vytvorte zoznam typu ArrayList<int>.
		this->logInfo("Creating ArrayList<int>()");
		structures::ArrayList<int>* AL = new structures::ArrayList<int>();

		// Vložte na koniec zoznamu postupne èísla od 0 do 99
		this->logInfo("Adding numbers from 0 to 99,included");
		for (int i = 0; i < 100; i++)
			AL->add(i);

		//Vymažte mocou metódy removeAt prvok na indexe 99.
		this->logInfo("removeAt(99)");
		AL->removeAt(99);

		//Overte pomocou metódy size, že má zoznam ve¾kos 99.
		this->assertTrue(AL->size() == 99, "size == 99");
		//Overte pomocou metódy getIndexOf, že sa v zozname nenachádza hodnota 99
		this->assertTrue(AL->getIndexOf(99) == -1,"AL->getIndexOf(99) == -1");

		//Vymažte mocou metódy removeAt prvok na indexe 50.
		this->logInfo("removeAt(50)");
		AL->removeAt(50);

		//Overte pomocou metódy size, že má zoznam ve¾kos 98.
		this->assertTrue(AL->size() == 98, "size == 98");
		//Overte pomocou metódy getIndexOf, že sa v zozname nenachádza hodnota 50.
		this->assertTrue(AL->getIndexOf(50) == -1, "AL->getIndexOf(50) == -1");

		//Vymažte mocou metódy removeAt prvok na indexe 0.
		this->logInfo("removeAt(0)");
		AL->removeAt(0);
		//Overte pomocou metódy size, že má zoznam ve¾kos 97.
		this->assertTrue(AL->size() == 97, "size == 97");
		//Overte pomocou metódy getIndexOf, že sa v zozname nenachádza hodnota 0.
		this->assertTrue(AL->getIndexOf(0) == -1, "AL->getIndexOf(0) == -1");

		//Vymažte pomocou metódy tryRemove všetky prvky delite¾né 5 (teda 5, 10, .. 95).
		this->logInfo("tryRemove all numbers that can be divided by 5");
		for (int i = 0; i < 100; i++)
		{
			if (i % 5 == 0)
				AL->tryRemove(i);
			//Overte v priebehu testu, že sa nepodarilo vymaza prvok 50.
			if (i == 50)
				this->assertFalse(AL->tryRemove(i),"tryRemove(50)");
		}

		//Overte pomocou metódy size, že má zoznam ve¾kos 79.
		this->assertTrue(AL->size() == 79, "size == 79");
		//Overte pomocou metódy getIndexOf, že sa v zozname nenachádzajú vymazané hodnoty.
		for (int i = 0; i < 100; i++)
		{
			if (i % 5 == 0)
				this->assertTrue(AL->getIndexOf(i) == -1,
					"getIndexOf(" + std::to_string(i) + ") == -1");
		}

		//Vymažte celý zoznam metódou clear.
		this->logInfo("clear()");
		AL->clear();
		//Overte pomocou metódy isEmpty, že je zoznam prázdny.
		this->assertTrue(AL->isEmpty(), "isEmpty()");

		delete AL;
		AL = nullptr;

		this->stopStopwatch();
		tests::DurationType duration = this->getElapsedTime();
		this->logInfo("Time of the test is " + std::to_string(duration.count()) + " ms");

		structures::Logger::getInstance().logDuration(100, duration, "ArrayListTestRemove TimeTest");


		this->logInfo("End of test ArrayListTestRemove");
	}

	//LinkedListTestInsert:

	LinkedListTestInsert::LinkedListTestInsert()
		:SimpleTest("Insert and Add") {

	}

	void LinkedListTestInsert::test()
	{
		this->logInfo("Start of test LinkedListTestInsert");
		this->startStopwatch();
		//Vytvorte zoznam typu ArrayList<int>
		this->logInfo("Creating LinkedList<int>()");
		
		structures::LinkedList<int>* AL = new structures::LinkedList<int>();

		//Vložte pomocou metódy add na koniec zoznamu èísla 10, 20, 30, 40
		this->logInfo("Adding 10,20,30,40");
		for (int i{ 1 }; i < 5; i++) {
			AL->add(i * 10);
		}

		// Overte pomocou metódy size, že má ve¾kos 4.
		this->assertTrue(AL->size() == 4, "size == 4");

		//Vložte pomocou metódy add na koniec zoznamu èísla 
			//100, 200, 300, 400.
		this->logInfo("Adding 100,200,300,400 ");
		for (int i{ 1 }; i < 5; i++) {
			AL->add(i * 100);
		}

		//Overte pomocou metódy size, že má ve¾kos 8.
		this->assertTrue(AL->size() == 8, "size == 8");

		//Vložte na zaèiatok zoznamu pomocou metódy insert 9x èíslo 1.
		this->logInfo("Inserting on index 0: 9x number 1");
		for (size_t i{ 0 }; i < 9; i++) {
			AL->insert(1, 0);
		}

		// Overte pomocou metódy size, že má ve¾kos 17.
		this->assertTrue(AL->size() == 17, "size == 17");

		//Vložte pomocou metódy insert na index 0 
		//prvok 7, na index 4 prvok 77, na index 18 prvok 777 
		//a na index 20 prvok 7777
		this->logInfo("Insert on index 0: 7");
		AL->insert(7, 0);
		this->logInfo("Insert on index 4: 77");
		AL->insert(77, 4);
		this->logInfo("Insert on index 18: 777");
		AL->insert(777, 18);
		this->logInfo("Insert on index 20: 7777");
		AL->insert(7777, 20);

		//Overte pomocou metódy size, že má ve¾kos 21.
		this->assertTrue(AL->size() == 21, "size == 21");

		int expected[21]{ 7, 1, 1, 1, 77, 1, 1, 1, 1, 1, 1, 10, 20, 30, 40, 100, 200, 300, 777, 400, 7777 };

		for (int i{ 0 }; i < AL->size(); i++) {
			this->assertTrue(AL->at(i) == expected[i],
				"at(" + std::to_string(i) + ") == " + std::to_string(expected[i]));
		}

		delete AL;
		AL = nullptr;

		this->stopStopwatch();
		tests::DurationType duration = this->getElapsedTime();
		this->logInfo("Time of the test is " + std::to_string(duration.count()) + " ms");

		structures::Logger::getInstance().logDuration(100, duration, "LinkedListTestInsert TimeTest");

		this->logInfo("End of test LinkedListTestInsert");
	}

	//ArrayListTestRemove
	LinkedListTestRemove::LinkedListTestRemove()
		:SimpleTest("Remove")
	{
	}

	void LinkedListTestRemove::test()
	{
		this->logInfo("Start of test LinkedListTestRemove");
		this->startStopwatch();
		//Vytvorte zoznam typu ArrayList<int>.
		this->logInfo("Creating LinkedList<int>()");
		structures::LinkedList<int>* AL = new structures::LinkedList<int>();
	

		// Vložte na koniec zoznamu postupne èísla od 0 do 99
		this->logInfo("Adding numbers from 0 to 99,included");
		for (int i = 0; i < 100; i++)
			AL->add(i);
	
		//Vymažte mocou metódy removeAt prvok na indexe 99.
		this->logInfo("removeAt(99)");
		AL->removeAt(99);
	
		//Overte pomocou metódy size, že má zoznam ve¾kos 99.
		this->assertTrue(AL->size() == 99, "size == 99");
		//Overte pomocou metódy getIndexOf, že sa v zozname nenachádza hodnota 99
		this->assertTrue(AL->getIndexOf(99) == -1, "AL->getIndexOf(99) == -1");

		//Vymažte mocou metódy removeAt prvok na indexe 50.
		this->logInfo("removeAt(50)");
		AL->removeAt(50);

		//Overte pomocou metódy size, že má zoznam ve¾kos 98.
		this->assertTrue(AL->size() == 98, "size == 98");
		//Overte pomocou metódy getIndexOf, že sa v zozname nenachádza hodnota 50.
		this->assertTrue(AL->getIndexOf(50) == -1, "AL->getIndexOf(50) == -1");

		//Vymažte mocou metódy removeAt prvok na indexe 0.
		this->logInfo("removeAt(0)");
		AL->removeAt(0);
		//Overte pomocou metódy size, že má zoznam ve¾kos 97.
		this->assertTrue(AL->size() == 97, "size == 97");
		//Overte pomocou metódy getIndexOf, že sa v zozname nenachádza hodnota 0.
		this->assertTrue(AL->getIndexOf(0) == -1, "AL->getIndexOf(0) == -1");

		//Vymažte pomocou metódy tryRemove všetky prvky delite¾né 5 (teda 5, 10, .. 95).
		this->logInfo("tryRemove all numbers that can be divided by 5");
		for (int i = 0; i < 100; i++)
		{
			if (i % 5 == 0)
				AL->tryRemove(i);
			//Overte v priebehu testu, že sa nepodarilo vymaza prvok 50.
			if (i == 50)
				this->assertFalse(AL->tryRemove(i), "tryRemove(50)");
		}

		//Overte pomocou metódy size, že má zoznam ve¾kos 79.
		this->assertTrue(AL->size() == 79, "size == 79");
		//Overte pomocou metódy getIndexOf, že sa v zozname nenachádzajú vymazané hodnoty.
		for (int i = 0; i < 100; i++)
		{
			if (i % 5 == 0)
				this->assertTrue(AL->getIndexOf(i) == -1,
					"getIndexOf(" + std::to_string(i) + ") == -1");
		}

		//Vymažte celý zoznam metódou clear.
		this->logInfo("clear()");
		AL->clear();
		//Overte pomocou metódy isEmpty, že je zoznam prázdny.
		this->assertTrue(AL->isEmpty(), "isEmpty()");

		delete AL;
		AL = nullptr;
		this->stopStopwatch();
		tests::DurationType duration = this->getElapsedTime();
		this->logInfo("End of test LinkedListTestRemove");
		
		this->logInfo("Time of the LinkedListTestRemove test is " + std::to_string(duration.count()) + " ms");
		structures::Logger::getInstance().logDuration(100, duration, "LinkedList Remove TimeTest");
	
	}

	
	Zadanie2_TestMetod::Zadanie2_TestMetod()
		:SimpleTest("Uloha1")
	{
	}

	void Zadanie2_TestMetod::test()
	{
		this->logInfo("Start of test DoubleLinkedListTest - Uloha1");

		//Vytvorte zoznam typu ArrayList<int>.
		this->logInfo("Creating DoubleLinkedList<int>()");
		structures::DoubleLinkedList<int>* DLL = new structures::DoubleLinkedList<int>();


		// Vložte na koniec zoznamu postupne èísla od 0 do 9
		this->logInfo("Adding numbers from 0 to 9,included");
		for (int i = 0; i < 10; i++) {
			DLL->add(i);
			this->assertTrue(DLL->at(i) == i, "DLL->at(" + std::to_string(i) + ") == " + std::to_string(i));
		}

		this->logInfo("Insert 10 at 10");
		DLL->insert(10, 10);
		this->assertTrue(DLL->at(10) == 10, "DLL->at(10) == 10");

		this->logInfo("Insert -1 at 0");
		DLL->insert(-1, 0);
		this->assertTrue(DLL->at(0) == -1, "DLL->at(0) == -1");

		this->logInfo("Insert 1 at 1");
		DLL->insert(1, 1);
		this->assertTrue(DLL->at(1) == 1, "DLL->at(1) == 1");
			
		this->logInfo("removeAt(12)");
		this->logInfo("removed: " + std::to_string(DLL->removeAt(12)));

		this->logInfo("removeAt(1)");
		this->logInfo("removed: " + std::to_string(DLL->removeAt(1)));

		this->logInfo("removeAt(0)");
		this->logInfo("removed: " + std::to_string(DLL->removeAt(0)));


		this->logInfo("Checking numbers from 0 to 9,included");
		for (int i = 0; i < 10; i++)
			this->assertTrue(DLL->at(i) == i, "DLL->at("+ std::to_string(i) +") == " + std::to_string(i));

		this->assertFalse(DLL->tryRemove(10), "DLL->tryRemove(10)");
		this->assertTrue(DLL->tryRemove(9), "DLL->tryRemove(9)");
		this->assertTrue(DLL->tryRemove(0), "DLL->tryRemove(0)");
		this->assertTrue(DLL->tryRemove(5), "DLL->tryRemove(5)");


		delete DLL;
		DLL = nullptr;

		this->logInfo("End of test DoubleLinkedListTest - Uloha1");
	}



	Zadanie2_Uloha2::Zadanie2_Uloha2()
		:SimpleTest("Uloha2[A,B,C]")
	{
	}

	void Zadanie2_Uloha2::test()
	{
		//A===================
		structures::ArrayList<int>* arrayListA = new structures::ArrayList<int>();
		uloha2(arrayListA, 20, 20, 50, 10, "ArrayList_A");
		delete arrayListA;
		arrayListA = nullptr;

		structures::DoubleLinkedList<int>* doubleLinkedListA = new structures::DoubleLinkedList<int>();
		uloha2(doubleLinkedListA, 20, 20, 50, 10, "doubleLinkedList_A");
		delete doubleLinkedListA;
		doubleLinkedListA = nullptr;

		//B===================
		structures::ArrayList<int>* arrayListB = new structures::ArrayList<int>();
		uloha2(arrayListB, 35, 35, 20, 10, "ArrayList_B");
		delete arrayListB;
		arrayListB = nullptr;

		structures::DoubleLinkedList<int>* doubleLinkedListB = new structures::DoubleLinkedList<int>();
		uloha2(doubleLinkedListB, 35, 35, 20, 10, "doubleLinkedList_B");
		delete doubleLinkedListB;
		doubleLinkedListB = nullptr;

		//C===================
		structures::ArrayList<int>* arrayListC = new structures::ArrayList<int>();
		uloha2(arrayListC, 45, 45, 5, 5, "ArrayList_C");
		delete arrayListC;
		arrayListC = nullptr;

		structures::DoubleLinkedList<int>* doubleLinkedListC = new structures::DoubleLinkedList<int>();
		uloha2(doubleLinkedListC, 45, 45, 5, 5, "doubleLinkedList_C");
		delete doubleLinkedListC;
		doubleLinkedListC = nullptr;

	}
	
	template <typename T>
	void Zadanie2_Uloha2::getMethodTime(structures::FileLogConsumer* fileLogger, structures::List<T>* list, std::string methodName) {
		size_t listSize = list->size();
		int index{};
		int randomData = rand();

		if (listSize == 0)
			index = 0;
		else
			index = rand() % listSize;

		if (methodName == "insert") {
			index = rand() % (listSize + 1);
			this->startStopwatch();
			list->insert(randomData, index);
			this->stopStopwatch();
		}
		else if (methodName == "getIndexOf") {
			this->startStopwatch();
			list->getIndexOf(randomData);
			this->stopStopwatch();
		}
		//Pri volani osetrim, aby som tu nemohol mat neplatny index
		else if (methodName == "at") {
			this->startStopwatch();
			list->at(index);
			this->stopStopwatch();
		}
		//Pri volani osetrim, aby som tu nemohol mat neplatny index
		else if (methodName == "removeAt") {
			this->startStopwatch();
			list->removeAt(index);
			this->stopStopwatch();
		}
		else {
			this->fail("TEST: DoubleLinkedListUloha2::getMethodTime: Invalid method!!!");
		}


		tests::DurationType duration = this->getElapsedTime();
		fileLogger->logDuration(listSize,duration, methodName);
	}

	template<typename T>
	void Zadanie2_Uloha2::uloha2(structures::List<T>* list, 
		int ratioInsert, int ratioRemoveAt, int ratioAt, int ratioGetIndexOf, std::string nazov)
	{
		std::string nazovCSV = nazov + ".csv";

		structures::FileLogConsumer* fileLogConsumer = new structures::FileLogConsumer(nazovCSV);
		//structures::Logger::getInstance().registerConsumer(fileLogConsumer);
		fileLogConsumer->DoubleLinkedListTitle();
		srand(static_cast<unsigned int>(time(NULL)));

		const int REPEATS = 100000;


		const int insertRatioPercent = (REPEATS / 100) * ratioInsert;
		const int removeAtRatioPercent = (REPEATS / 100) * ratioRemoveAt;
		const int atRatioPercent = (REPEATS / 100) * ratioAt;
		const int getIndexOfRatioPercent = (REPEATS / 100) * ratioGetIndexOf;

		const int level1 = ratioInsert;
		const int level2 = level1 + ratioRemoveAt;
		const int level3 = level2 + ratioAt;


		int counterInsert = 0;
		int counterRemoveAt = 0;
		int counterAt = 0;
		int counterGetIndexOf = 0;



		for (int j = 0; j < REPEATS; j++)
		{
			int randomRatio = rand() % 100;


			if (randomRatio < level1 && counterInsert < insertRatioPercent) {
				//insert
				getMethodTime(fileLogConsumer, list, "insert");
				counterInsert++;
			}
			else if (randomRatio < level2 && counterRemoveAt < removeAtRatioPercent && list->size() != 0) {
				//removeAt
				getMethodTime(fileLogConsumer, list, "removeAt");
				counterRemoveAt++;
			}
			else if (randomRatio < level3 && counterAt < atRatioPercent && list->size() != 0) {
				//at
				getMethodTime(fileLogConsumer, list, "at");
				counterAt++;
			}
			else if (randomRatio < 100 && counterGetIndexOf < getIndexOfRatioPercent) {
				//getIndexOf
				getMethodTime(fileLogConsumer, list, "getIndexOf");
				counterGetIndexOf++;
			}
			else if (counterInsert < insertRatioPercent) {
				//insert
				getMethodTime(fileLogConsumer, list, "insert");
				counterInsert++;
			}
			else if (counterAt < atRatioPercent && list->size() != 0) {
				//at
				getMethodTime(fileLogConsumer, list, "at");
				counterAt++;
			}
			else if (counterRemoveAt < removeAtRatioPercent && list->size() != 0) {
				//removeAt
				getMethodTime(fileLogConsumer, list, "removeAt");
				counterRemoveAt++;
			}

			else if (counterGetIndexOf < getIndexOfRatioPercent) {
				//getIndexOf
				getMethodTime(fileLogConsumer, list, "getIndexOf");
				counterGetIndexOf++;

			}
			else {
				if (counterGetIndexOf != getIndexOfRatioPercent && counterInsert != insertRatioPercent)
				{
					if (counterAt != atRatioPercent && counterRemoveAt != removeAtRatioPercent) {
						int randomNumber = rand() % 2;
						if (randomNumber == 1)
						{
							list->add(1);
							getMethodTime(fileLogConsumer, list, "removeAt");
							counterRemoveAt++;
						}
						else {
							list->add(1);
							getMethodTime(fileLogConsumer, list, "at");
							list->removeAt(0);
							counterAt++;
						}

					}
				}
				else if (counterAt == atRatioPercent) {
					list->add(1);
					getMethodTime(fileLogConsumer, list, "removeAt");
					counterRemoveAt++;
				}
				else {
					list->add(1);
					getMethodTime(fileLogConsumer, list, "at");
					list->removeAt(0);
					counterAt++;
				}
			}
		}

		delete fileLogConsumer;
		fileLogConsumer = nullptr;

	}


	Zadanie2_Uloha3::Zadanie2_Uloha3()
		:SimpleTest("Uloha3 - insert,at,removeAt")
	{
	}

	void Zadanie2_Uloha3::test()
	{
		//Insert
		structures::ArrayList<int>* arrayListInsert = new structures::ArrayList<int>();
		uloha3(arrayListInsert, "insert", "ArrayList_Insert");
		delete arrayListInsert;
		arrayListInsert = nullptr;

		structures::DoubleLinkedList<int>* doubleLinkedListInsert = new structures::DoubleLinkedList<int>();
		uloha3(doubleLinkedListInsert, "insert", "DoubleLinkedList_Insert");
		delete doubleLinkedListInsert;
		doubleLinkedListInsert = nullptr;

		//at
		structures::ArrayList<int>* arrayListAt = new structures::ArrayList<int>();
		uloha3(arrayListAt, "at", "ArrayList_At");
		delete arrayListAt;
		arrayListAt = nullptr;

		structures::DoubleLinkedList<int>* doubleLinkedListAt = new structures::DoubleLinkedList<int>();
		uloha3(doubleLinkedListAt, "at", "DoubleLinkedList_At");
		delete doubleLinkedListAt;
		doubleLinkedListAt = nullptr;

		//removeAt
		structures::ArrayList<int>* arrayListRemoveAt = new structures::ArrayList<int>();
		uloha3(arrayListRemoveAt, "removeAt", "ArrayList_RemoveAt");
		delete arrayListRemoveAt;
		arrayListRemoveAt = nullptr;

		structures::DoubleLinkedList<int>* doubleLinkedListRemoveAt = new structures::DoubleLinkedList<int>();
		uloha3(doubleLinkedListRemoveAt, "removeAt", "DoubleLinkedList_RemoveAt");
		delete doubleLinkedListRemoveAt;
		doubleLinkedListRemoveAt = nullptr;
	}

	template<typename T>
	void Zadanie2_Uloha3::uloha3(structures::List<T>* list,std::string methodName, std::string nazov)
	{

		std::string nazovCSV = nazov + ".csv";

		structures::FileLogConsumer* fileLogConsumer = new structures::FileLogConsumer(nazovCSV);
		tests::Zadanie2_Uloha2* cas = new tests::Zadanie2_Uloha2();


		fileLogConsumer->DoubleLinkedListTitle();
		srand(static_cast<unsigned int>(time(NULL)));

		const int REPEATS = 100000;
		if (methodName == "insert") {
			for (int i = 0; i < REPEATS; i++)
			{
				cas->getMethodTime(fileLogConsumer, list, methodName);
			}
		} else if(methodName == "at") {
			for (int i = 0; i < REPEATS; i++)
			{
				int randomData = rand();
				list->add(randomData);
				cas->getMethodTime(fileLogConsumer, list, methodName);
			}
		} else if (methodName == "removeAt") {
			for (int i = 0; i < REPEATS; i++)
			{
				int randomData = rand();
				list->add(randomData);
			}

			for (int i = 0; i < REPEATS; i++)
			{
				cas->getMethodTime(fileLogConsumer, list, methodName);
			}
		} else {
			this->fail("Zadanie2_Uloha3::uloha3: Invalid method!!!");
		}

		delete cas;
		cas = nullptr;

		delete fileLogConsumer;
		fileLogConsumer = nullptr;
	}



}