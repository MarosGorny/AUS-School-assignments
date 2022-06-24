#include "table_test.h"
#include "../../structures/table/binary_search_tree.h"
#include "../../structures/table/hash_table.h"
#include "../../structures/table/linked_table.h"
#include "../../structures/table/sorted_sequence_table.h"
#include "../../structures/table/table.h"
#include "../../structures/table/treap.h"
#include "../../structures/table/unsorted_sequence_table.h"

namespace tests
{
	TableTestInterface::TableTestInterface() :
		SimpleTest("Interface")
	{
	}

	void TableTestInterface::test()
	{
		int x = 0;
		structures::Table<int, int>* table = this->makeTable();
		table->equals(*table);
		table->assign(*table);
		table->insert(0, 0);
		table->find(0);
		table->remove(0);
		table->tryFind(0, x);
		table->containsKey(0);
		delete table;
		this->logPass("Compiled.");
	}

	structures::Table<int, int>* BinarySearchTreeTestInterface::makeTable()
	{
		return new structures::BinarySearchTree<int, int>();
	}

	structures::Table<int, int>* HashTableTestInterface::makeTable()
	{
		return new structures::HashTable<int, int>();
	}

	structures::Table<int, int>* LinkedTableTestInterface::makeTable()
	{
		return new structures::LinkedTable<int, int>();
	}

	structures::Table<int, int>* SortedSequenceTableTestInterface::makeTable()
	{
		return new structures::SortedSequenceTable<int, int>();
	}

	structures::Table<int, int>* TreapTestInterface::makeTable()
	{
		return new structures::Treap<int, int>();
	}

	structures::Table<int, int>* UnsortedSequenceTableTestInterface::makeTable()
	{
		return new structures::UnsortedSequenceTable<int, int>();
	}

	BinarySearchTreeTestOverall::BinarySearchTreeTestOverall() :
		ComplexTest("BinarySearchTree")
	{
		addTest(new BinarySearchTreeTestInterface());
		addTest(new BinarySearchTreeFunctionsTest());
	}

	HashTableTestOverall::HashTableTestOverall() :
		ComplexTest("HashTable")
	{
		addTest(new HashTableTestInterface());
	}

	LinkedTableTestOverall::LinkedTableTestOverall() :
		ComplexTest("LinkedTable")
	{
		addTest(new LinkedTableTestInterface());
	}

	SortedSequenceTableTestOverall::SortedSequenceTableTestOverall() :
		ComplexTest("SortedSequenceTable")
	{
		addTest(new SortedSequenceTableTestInterface());
		addTest(new SortedSequenceTableFunctionsTest());
	}

	TreapTestOverall::TreapTestOverall() :
		ComplexTest("Treap")
	{
		addTest(new TreapTestInterface());
	}

	UnsortedSequenceTableTestOverall::UnsortedSequenceTableTestOverall() :
		ComplexTest("UnsortedSequenceTable")
	{
		addTest(new UnsortedSequenceTableTestInterface());
	}

	TableTestOverall::TableTestOverall() :
		ComplexTest("Table")
	{
		addTest(new BinarySearchTreeTestOverall());
		addTest(new HashTableTestOverall());
		addTest(new LinkedTableTestOverall());
		addTest(new SortedSequenceTableTestOverall());
		addTest(new TreapTestOverall());
		addTest(new UnsortedSequenceTableTestOverall());
		addTest(new Zadanie4_Uloha2());
		addTest(new Zadanie4_Uloha3());
	}
	BinarySearchTreeFunctionsTest::BinarySearchTreeFunctionsTest()
		:SimpleTest("UseCases")
	{
		
	}

	void BinarySearchTreeFunctionsTest::test()
	{
		this->logInfo("Start of test BinarySearchTreeFunctionsTest");

		this->logInfo("Creating pointer to a BST:BST1");
		structures::BinarySearchTree<int, int>* BST1 = new structures::BinarySearchTree<int, int>();



		this->assertTrue(BST1->size() == 0, "BST1->size() == 0");

		this->logInfo("========================Fulling BST1========================");
		this->logInfo("Testing find() and containts key");
		for (int data = 1; data < 11; data++)
		{
			int key = data;
			BST1->insert(key, data);
			this->logInfo("BST1:Insert: key- " + std::to_string(key) + " data-:" + std::to_string(data));
			this->assertTrue(BST1->find(key) == key, "BST1->find(" + std::to_string(key) + " == " + std::to_string(data));
			this->assertTrue(BST1->containsKey(key) == true, "BST1->containsKey(key) == true");
		}
		this->logInfo("======================End Fulling BST1======================");

		this->assertTrue(BST1->size() == 10, "BST1->size() == 10");

		this->logInfo("Creating pointer to a BST:BST2");
		structures::BinarySearchTree<int, int>* BST2 = new structures::BinarySearchTree<int, int>();

		this->logInfo("BST2:assign BST1");
		BST2->assign(*BST1);

		BST1->insert(0, 1000);
		this->logInfo("BST1 Insert:Key-0 Data-1000");
		this->assertTrue(BST1->size() == 11, "BST1->size() == 11");
		this->assertTrue(BST2->size() == 10, "BST2->size() == 10");
		BST2->insert(1000, 0);
		this->logInfo("BST1 Insert:Key-1000 Data-0");
		this->assertTrue(BST2->size() == 11, "BST2->size() == 11");

		this->assertTrue(BST1->remove(0) == 1000, "BST1->remove(0) == 1000");
		this->assertTrue(BST2->remove(1000) == 0, "BST1->remove(1000) == 0");

		this->assertTrue(BST1->size() == 10, "BST1->size() == 10");
		this->assertTrue(BST2->size() == 10, "BST2->size() == 10");

		int data;
		this->assertFalse(BST1->tryFind(0, data), "BST1->tryFind(0,data)");
		this->assertFalse(BST2->tryFind(1000, data), "BST2->tryFind(0,data)");
		this->assertTrue(BST1->tryFind(1, data), "BST1->tryFind(1,data)");
		this->assertTrue(data == 1, "data == 1");

		this->logInfo("BST1:clear");
		BST1->clear();
		this->assertTrue(BST1->size() == 0, "BST1->size() == 0");
		this->assertTrue(BST2->size() == 10, "BST2->size() == 10");


		for (int i = 1; i < 11; i++)
		{
			this->assertTrue(BST2->containsKey(i));
		}


		this->logInfo("========================Removing BST2========================");
		for (int key = 1; key < 11; key++)
		{

			BST2->remove(key);
			this->logInfo("BST2->remove(" + std::to_string(key) + ")");

			int dataLoop;
			this->assertFalse(BST2->tryFind(key, dataLoop), "BST2->tryFind(" + std::to_string(key) + ",data)");
			//this->assertFalse(dataLoop == key, "data = " + std::to_string(key));
		}
		this->logInfo("====================== End of removing on BST2========================");


		this->logInfo("clearing BST2");
		BST2->clear();
		this->logInfo("Creating tree BST2");
		BST2->insert(128, 1);
		BST2->insert(125, 1);
		BST2->insert(122, 1);
		BST2->insert(213, 1);
		BST2->insert(178, 1);
		BST2->insert(143, 1);
		BST2->insert(241, 1);
		BST2->insert(222, 1);
		BST2->insert(237, 1);
		BST2->insert(259, 1);

		this->logInfo("Removing leaf");
		BST2->remove(122);
		this->logInfo("Removing node with one son");
		BST2->remove(222);
		this->logInfo("Removing node with two sons");
		BST2->remove(241);
		this->logInfo("Removing root");
		BST2->remove(128);

		this->assertTrue(BST2->size() == 6, "BST2->size() == 6");
		this->logInfo("clearing BST2");
		BST2->clear();



		this->logInfo("End of test BinarySearchTreeFunctionsTest");
		delete BST1;
		BST1 = nullptr;

		delete BST2;
		BST2 = nullptr;
	}

	SortedSequenceTableFunctionsTest::SortedSequenceTableFunctionsTest()
		:SimpleTest("UseCases")
	{

	}

	void SortedSequenceTableFunctionsTest::test()
	{
		this->logInfo("Start of test SortedSequenceTableFunctionsTest");

		this->logInfo("Creating pointer to a SST:SST1");
		structures::SortedSequenceTable<int, int>* SST1 = new structures::SortedSequenceTable<int, int>();



		this->assertTrue(SST1->size() == 0, "SST1->size() == 0");

		this->logInfo("========================Fulling SST1!========================");
		this->logInfo("Testing find() and containts key");
		for (int data = 1; data < 11; data++)
		{
			int key = data;
			SST1->insert(key, data);
			this->logInfo("SST1:Insert: key- " + std::to_string(key) + " data-:" + std::to_string(data));
			this->assertTrue(SST1->find(key) == key, "SST1->find(" + std::to_string(key) + " == " + std::to_string(data));
			this->assertTrue(SST1->containsKey(key) == true, "SST1->containsKey(key) == true");
		}
		this->logInfo("======================End Fulling SST1======================");

		this->assertTrue(SST1->size() == 10, "SST1->size() == 10");

		this->logInfo("Creating pointer to a SST:SST2");
		structures::SortedSequenceTable<int, int>* SST2 = new structures::SortedSequenceTable<int, int>();

		this->logInfo("SST2:assign SST1");
		SST2->assign(*SST1);

		SST1->insert(0, 1000);
		this->logInfo("SST1 Insert:Key-0 Data-1000");
		this->assertTrue(SST1->size() == 11, "SST1->size() == 11");
		this->assertTrue(SST2->size() == 10, "SST2->size() == 10");
		SST2->insert(1000, 0);
		this->logInfo("SST1 Insert:Key-1000 Data-0");
		this->assertTrue(SST2->size() == 11, "SST2->size() == 11");

		this->assertTrue(SST1->remove(0) == 1000, "SST1->remove(0) == 1000");
		this->assertTrue(SST2->remove(1000) == 0, "SST1->remove(1000) == 0");

		this->assertTrue(SST1->size() == 10, "SST1->size() == 10");
		this->assertTrue(SST2->size() == 10, "SST2->size() == 10");

		int data;
		this->assertFalse(SST1->tryFind(0, data), "SST1->tryFind(0,data)");
		this->assertFalse(SST2->tryFind(1000, data), "SST2->tryFind(0,data)");
		this->assertTrue(SST1->tryFind(1, data), "SST1->tryFind(1,data)");
		this->assertTrue(data == 1, "data == 1");

		this->logInfo("SST1:clear");
		SST1->clear();
		this->assertTrue(SST1->size() == 0, "SST1->size() == 0");
		this->assertTrue(SST2->size() == 10, "SST2->size() == 10");


		for (int i = 1; i < 11; i++)
		{
			this->assertTrue(SST2->containsKey(i));
		}


		this->logInfo("========================Removing SST2========================");
		for (int key = 1; key < 11; key++)
		{

			SST2->remove(key);
			this->logInfo("SST2->remove(" + std::to_string(key) + ")");

			int dataLoop;
			this->assertFalse(SST2->tryFind(key, dataLoop), "SST2->tryFind(" + std::to_string(key) + ",data)");
			//this->assertFalse(dataLoop == key, "data = " + std::to_string(key));
		}
		this->logInfo("====================== End of removing on SST2========================");


		this->logInfo("clearing SST2");
		SST2->clear();
		this->logInfo("Creating tree SST2");
		SST2->insert(128, 1);
		SST2->insert(125, 1);
		SST2->insert(122, 1);
		SST2->insert(213, 1);
		SST2->insert(178, 1);
		SST2->insert(143, 1);
		SST2->insert(241, 1);
		SST2->insert(222, 1);
		SST2->insert(237, 1);
		SST2->insert(259, 1);

		this->logInfo("Removing leaf");
		SST2->remove(122);
		this->logInfo("Removing node with one son");
		SST2->remove(222);
		this->logInfo("Removing node with two sons");
		SST2->remove(241);
		this->logInfo("Removing root");
		SST2->remove(128);

		this->assertTrue(SST2->size() == 6, "SST2->size() == 6");
		this->logInfo("clearing SST2");
		SST2->clear();



		this->logInfo("End of test SortedSequenceTableFunctionsTest");
		delete SST1;
		SST1 = nullptr;

		delete SST2;
		SST2 = nullptr;
	}
	
	Zadanie4_Uloha2::Zadanie4_Uloha2()
		:SimpleTest("Uloha2[A,B]"),
		isInside_(new structures::Array<bool>(100001)),
		keyArray_(new structures::ArrayList<int>())
	{
		for (int i = 0; i < keyArray_->size(); i++)
		{
			isInside_->at(i) = false;
		}
	}

	Zadanie4_Uloha2::~Zadanie4_Uloha2() {
		this->keyArray_->clear();
		delete keyArray_;
		keyArray_ = nullptr;

		delete isInside_;
		isInside_ = nullptr;
	}

	template<typename K, typename T>
	void Zadanie4_Uloha2::getMethodTime(structures::FileLogConsumer* fileLogger, structures::Table<K, T>* table, std::string methodName) {
		int randomData = rand();

		//key interval <0,100 000>
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> distribution(0, 100000);
		int randomKey = static_cast<int>(distribution(gen));


		if (methodName == "insert") {
			bool keyIsInside = this->isInside_->at(randomKey);

			while (keyIsInside)
			{
				randomKey = static_cast<int>(distribution(gen)) % 100001;
				keyIsInside = this->isInside_->at(randomKey);
			}

			this->startStopwatch();
			table->insert(randomKey, randomData);
			this->stopStopwatch();

			//add the key to the array
			this->keyArray_->add(randomKey);
			this->isInside_->at(randomKey) = true;
		}
		else if (methodName == "remove") {
			//gemerate random index of keyArray
			int randomKeyIndex = (static_cast<int>(distribution(gen))) % this->keyArray_->size();
			//get key to remove
			int key = this->keyArray_->at(randomKeyIndex);

			this->startStopwatch();
			table->remove(key);
			this->stopStopwatch();

			//remove the key from arrayList
			this->keyArray_->removeAt(randomKeyIndex);
			this->isInside_->at(key) = false;
		}
		else if (methodName == "tryFind") {
			int data;
			this->startStopwatch();
			table->tryFind(randomKey,data);
			this->stopStopwatch();
		}
		else {
			this->fail("TEST: Zadanie4_Uloha2::getMethodTime: Invalid method!!!");
		}


		tests::DurationType duration = this->getElapsedTime();
		fileLogger->logDuration(table->size(), duration, methodName);
	}


	template<typename K, typename T>
	void Zadanie4_Uloha2::uloha2(structures::Table<K, T>* table, int ratioInsert, int ratioRemove, int ratioTryFind, std::string nazov) {
		std::string nazovCSV = nazov + ".csv";

		structures::FileLogConsumer* fileLogConsumer = new structures::FileLogConsumer(nazovCSV);

		fileLogConsumer->SizeTimeNsMethodTitle();
		srand(static_cast<unsigned int>(time(NULL)));

		const int REPEATS = 100000;


		const int insertRatioPercent = (REPEATS / 100) * ratioInsert;
		const int removeRatioPercent = (REPEATS / 100) * ratioRemove;
		const int tryFindRatioPercent = (REPEATS / 100) * ratioTryFind;


		const int level1 = ratioInsert;
		const int level2 = level1 + ratioRemove;

		int counterInsert = 0;
		int counterRemove = 0;
		int counterTryFind = 0;


		for (int j = 0; j < REPEATS; j++)
		{
			int randomRatio = rand() % 100;


			if (randomRatio < level1 && counterInsert < insertRatioPercent) {
				//insert
				getMethodTime(fileLogConsumer, table, "insert");
				counterInsert++;
			}
			else if (randomRatio < level2 && counterRemove < removeRatioPercent && table->size() != 0) {
				//remove
				getMethodTime(fileLogConsumer, table, "remove");
				counterRemove++;
			}
			else if (randomRatio < 100 && counterTryFind < tryFindRatioPercent) {
				//tryFind
				getMethodTime(fileLogConsumer, table, "tryFind");
				counterTryFind++;
			}
			else if (counterInsert < insertRatioPercent) {
				//insert
				getMethodTime(fileLogConsumer, table, "insert");
				counterInsert++;
			}
			else if (counterTryFind < tryFindRatioPercent ) {
				//tryFind
				getMethodTime(fileLogConsumer, table, "tryFind");
				counterTryFind++;
			}
			else if (counterRemove < removeRatioPercent && table->size() != 0) {
				//remove
				getMethodTime(fileLogConsumer, table, "remove");
				counterRemove++;
			}
			else {
				//je jedno co tam dam, aj tak to bude prazdne
				table->insert(0, 0);
				this->keyArray_->add(0);
				this->isInside_->at(0) = true;
				getMethodTime(fileLogConsumer, table, "remove");
				counterRemove++;
			}

		}

		delete fileLogConsumer;
		fileLogConsumer = nullptr;
	}

	void Zadanie4_Uloha2::test()
	{
		//A===================
		structures::Table<int,int>* BSTA= new structures::BinarySearchTree<int,int>();
		Zadanie4_Uloha2::uloha2(BSTA, 20, 20, 60, "BST_A");
		delete BSTA;
		BSTA = nullptr;

		structures::Table<int,int>* SSTA = new structures::SortedSequenceTable<int,int>();
		Zadanie4_Uloha2::uloha2(SSTA, 20, 20, 60, "SST_A");
		delete SSTA;
		SSTA = nullptr;

		//B=======================
		structures::Table<int, int>* BSTB = new structures::BinarySearchTree<int, int>();
		Zadanie4_Uloha2::uloha2(BSTB, 40, 40, 20, "BST_B");
		delete BSTB;
		BSTB = nullptr;

		structures::Table<int, int>* SSTB = new structures::SortedSequenceTable<int, int>();
		Zadanie4_Uloha2::uloha2(SSTB, 40, 40, 20, "SST_B");
		delete SSTB;
		SSTB = nullptr;
	}

	template<typename K, typename T>
	void Zadanie4_Uloha2::insertRepeat(structures::FileLogConsumer* fileLogger,structures::Table<K, T>* table, int numberOfItems,int keyMaxIndex, bool time)
	{
		for (int i = 0; i < numberOfItems; i++)
		{
			//random data
			int randomData = rand();

			//random key
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> distribution(0, keyMaxIndex);
			int randomKey = static_cast<int>(distribution(gen));

			while (table->containsKey(randomKey))
			{
				randomKey = static_cast<int>(distribution(gen));
			}
			if (time) {
				this->startStopwatch();
				table->insert(randomKey, randomData);
				this->stopStopwatch();

				tests::DurationType duration = this->getElapsedTime();
				fileLogger->logDuration(table->size(), duration, "insert");
			}
			else {
				table->insert(randomKey, randomData);
			}				

		}
	}

	template<typename K, typename T>
	void Zadanie4_Uloha2::insertThenRemove(structures::FileLogConsumer* fileLogger, structures::Table<K, T>* table, int numberOfItems) {
		for (int i = 0; i < numberOfItems; i++)
		{
			//random data
			int randomData = rand();

			//random key
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> distribution(0, 1000000);
			int randomKey = static_cast<int>(distribution(gen));

			while (table->containsKey(randomKey))
			{
				randomKey = static_cast<int>(distribution(gen));
			}

			table->insert(randomKey, randomData);
			this->keyArray_->add(randomKey);
		}

		for (int i = 0; i < numberOfItems; i++)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> distribution(0, 1000000);
			int randomKey = static_cast<int>(distribution(gen)) % this->keyArray_->size();

			this->startStopwatch();
			table->remove(this->keyArray_->removeAt(randomKey));
			this->stopStopwatch();

			tests::DurationType duration = this->getElapsedTime();
			fileLogger->logDuration(table->size(), duration, "remove");
		}
	}

	template<typename K, typename T>
	void Zadanie4_Uloha2::RemoveThenTryFind(structures::FileLogConsumer* fileLogger, structures::Table<K, T>* table, int numberOfItems) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> distribution(0, 100000);
		
		for (int i = 0; i < numberOfItems; i++)
		{
			//random data
			int randomData = rand();

			//random key
			int randomKey = static_cast<int>(distribution(gen));

			while (table->containsKey(randomKey))
			{
				randomKey = static_cast<int>(distribution(gen));
			}

			table->insert(randomKey, randomData);
			this->keyArray_->add(randomKey);
		}

		for (int i = 0; i < numberOfItems; i++)
		{
			int randomKey = static_cast<int>(distribution(gen));
			int value;

			this->startStopwatch();
			table->tryFind(randomKey, value);
			this->stopStopwatch();

			randomKey = static_cast<int>(distribution(gen)) % this->keyArray_->size();

			table->remove(this->keyArray_->removeAt(randomKey));


			tests::DurationType duration = this->getElapsedTime();
			fileLogger->logDuration(table->size(), duration, "tryFind");
		}


	}



	Zadanie4_Uloha3::Zadanie4_Uloha3()
		:SimpleTest ("Uloha3 - insert,remove,tryFind")
	{
	}


	template<typename K, typename T>
	void Zadanie4_Uloha3::uloha3(structures::Table<K, T>* table, std::string methodName, std::string nazov) {
		std::string nazovCSV = nazov + ".csv";

		structures::FileLogConsumer* fileLogConsumer = new structures::FileLogConsumer(nazovCSV);
		tests::Zadanie4_Uloha2* cas = new tests::Zadanie4_Uloha2();

		fileLogConsumer->SizeTimeNsMethodTitle();
		srand(static_cast<unsigned int>(time(NULL)));

		const int REPEATS = 100000;
		if (methodName == "insert") {
			cas->insertRepeat(fileLogConsumer, table, REPEATS,1000000,true);
		}
		else if (methodName == "remove") {

			cas->insertThenRemove(fileLogConsumer, table, REPEATS);

		}
		else if (methodName == "tryFind") {
			cas->RemoveThenTryFind(fileLogConsumer, table, REPEATS);
		}
		else {
			this->fail("Zadanie4_Uloha3::uloha3: Invalid method!!!");
		}

		delete fileLogConsumer;
		fileLogConsumer = nullptr;

		delete cas;
		cas = nullptr;
	}


	void Zadanie4_Uloha3::test() {
		//insert
		structures::Table<int, int>* BST_Insert = new structures::BinarySearchTree<int, int>();
		Zadanie4_Uloha3::uloha3(BST_Insert,"insert", "BST_Insert");
		delete BST_Insert;
		BST_Insert = nullptr;

		structures::Table<int, int>* SST_Insert = new structures::SortedSequenceTable<int, int>();
		Zadanie4_Uloha3::uloha3(SST_Insert, "insert", "SST_Insert");
		delete SST_Insert;
		SST_Insert = nullptr;

		//remove
		structures::Table<int, int>* BST_Remove = new structures::BinarySearchTree<int, int>();
		Zadanie4_Uloha3::uloha3(BST_Remove, "remove", "BST_Remove");
		delete BST_Remove;
		BST_Remove = nullptr;

		structures::Table<int, int>* SST_Remove = new structures::SortedSequenceTable<int, int>();
		Zadanie4_Uloha3::uloha3(SST_Remove, "remove", "SST_Remove");
		delete SST_Remove;
		SST_Remove = nullptr;

		//tryFind
		structures::Table<int, int>* BST_TryFind = new structures::BinarySearchTree<int, int>();
		Zadanie4_Uloha3::uloha3(BST_TryFind, "tryFind", "BST_TryFind");
		delete BST_TryFind;
		BST_TryFind = nullptr;

		structures::Table<int, int>* SST_TryFind = new structures::SortedSequenceTable<int, int>();
		Zadanie4_Uloha3::uloha3(SST_TryFind, "tryFind", "SST_TryFind");
		delete SST_TryFind;
		SST_TryFind = nullptr;
	}


}