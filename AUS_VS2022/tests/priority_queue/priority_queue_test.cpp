#include "priority_queue_test.h"
#include "../../structures/priority_queue/heap.h"
#include "../../structures/priority_queue/priority_queue_limited_sorted_array_list.h"
#include "../../structures/priority_queue/priority_queue_linked_list.h"
#include "../../structures/priority_queue/priority_queue_sorted_array_list.h"
#include "../../structures/priority_queue/priority_queue_two_lists.h"
#include "../../structures/priority_queue/priority_queue_unsorted_array_list.h"

namespace tests
{
    PriorityQueueTestInterface::PriorityQueueTestInterface() :
        SimpleTest("Interface")
    {
    }

    void PriorityQueueTestInterface::test()
    {
        int x = 0;
        structures::PriorityQueue<int>* queue = this->makePriorityQueue();
        queue->push(0, x);
        queue->peek();
        queue->peekPriority();
        queue->pop();
        queue->assign(*queue);
        delete queue;
        this->logPass("Compiled.");
    }

    structures::PriorityQueue<int>* PriorityQueueUnsortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueUnsortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueSortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueSortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueLimitedSortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueLimitedSortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueLinkedListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueLinkedList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueTwoListsTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueTwoLists<int>();
    }

    structures::PriorityQueue<int>* HeapTestInterface::makePriorityQueue()
    {
        return new structures::Heap<int>();
    }

    PriorityQueueUnsortedArrayListTestOverall::PriorityQueueUnsortedArrayListTestOverall() :
        ComplexTest("PriorityQueueUnsortedArray")
    {
        addTest(new PriorityQueueUnsortedArrayListTestInterface());
    }

    PriorityQueueSortedArrayListTestOverall::PriorityQueueSortedArrayListTestOverall() :
        ComplexTest("PriorityQueueSortedArrayList")
    {
        addTest(new PriorityQueueSortedArrayListTestInterface());
    }

    PriorityQueueLimitedSortedArrayListTestOverall::PriorityQueueLimitedSortedArrayListTestOverall() :
        ComplexTest("PriorityQueueLimitedSortedArrayList")
    {
        addTest(new PriorityQueueLimitedSortedArrayListTestInterface());
    }

    PriorityQueueLinkedListTestOverall::PriorityQueueLinkedListTestOverall() :
        ComplexTest("PriorityQueueLinkedList")
    {
        addTest(new PriorityQueueLinkedListTestInterface());
    }

    PriorityQueueTwoListsTestOverall::PriorityQueueTwoListsTestOverall() :
        ComplexTest("PriorityQueueTwoLists")
    {
        addTest(new PriorityQueueTwoListsTestInterface());
        addTest(new PriorityQueueTwoListFunctionsTest());
    }

    HeapTestOverall::HeapTestOverall() :
        ComplexTest("Heap")
    {
        addTest(new HeapTestInterface());
        addTest(new HeapFunctionsTest());
    }

    PriorityQueueTestOverall::PriorityQueueTestOverall() :
        ComplexTest("PriorityQueue")
    {
        addTest(new PriorityQueueUnsortedArrayListTestOverall());
        addTest(new PriorityQueueSortedArrayListTestOverall());
        addTest(new PriorityQueueLimitedSortedArrayListTestOverall());
        addTest(new PriorityQueueLinkedListTestOverall());
        addTest(new PriorityQueueTwoListsTestOverall());
        addTest(new HeapTestOverall());
        addTest(new Zadanie3_Uloha2());
        addTest(new Zadanie3_Uloha3());
    }
    PriorityQueueTwoListFunctionsTest::PriorityQueueTwoListFunctionsTest()
        :SimpleTest("UseCases")
    {
    }

    void PriorityQueueTwoListFunctionsTest::test()
    {
        this->logInfo("Start of test PriorityQueueTwoListFunctionsTest");

        this->logInfo("Creating pointer to a PriorityQueueTwoLists:pqt1");
        structures::PriorityQueueTwoLists<int>* pqt1 = new structures::PriorityQueueTwoLists<int>();

        this->logInfo("Size of pqt1 = " + std::to_string(pqt1->size()));

        this->logInfo("========================Fulling pqt1========================");
        for (int data = 1; data < 201; data++)
        {
            int priority = 201 - data;
            pqt1->push(priority, data);
            this->logInfo("pqt1:push Priority: " + std::to_string(priority) + " Data:" + std::to_string(data));
            this->assertTrue(pqt1->peekPriority() == priority, "pqt1->peekPriority() == " + std::to_string(priority));
            this->assertTrue(pqt1->peek() == data, "pqt1->peek() == " + std::to_string(data));
        }
        this->logInfo("======================End Fulling pqt1======================");

        this->logInfo("Size of pqt1 = " + std::to_string(pqt1->size()));

        this->logInfo("Creating pointer to a PriorityQueueTwoLists:pqt2");
        structures::PriorityQueueTwoLists<int>* pqt2 = new structures::PriorityQueueTwoLists<int>();

        this->logInfo("pqt2:assign pqt1");
        pqt2->assign(*pqt1);

        pqt1->push(0, 1337);
        this->logInfo("pqt1:push Priority:0 Data:1337");
        this->logInfo("Size of pqt1 = " + std::to_string(pqt1->size()));
        this->logInfo("Size of pqt2 = " + std::to_string(pqt2->size()));
        pqt2->push(0, 1111);
        this->logInfo("pqt2:push Priority:0 Data:1111");
        pqt2->push(1000, 1000);
        this->logInfo("pqt2:push Priority:1000 Data:1000");

        this->assertTrue(pqt1->peek() == 1337, "pqt1->peek() == 1337");
        this->assertTrue(pqt1->peekPriority() == 0, "pqt1->peekPriority() == 0");

        this->assertTrue(pqt2->peek() == 1111, "pqt2->peek() == 1111");
        this->assertTrue(pqt2->peekPriority() == 0, "pqt2->peekPriority() == 0");

        this->assertTrue(pqt1->pop() == 1337,"pqt1->pop() == 1337");
        this->assertTrue(pqt2->pop() == 1111,"pqt2->pop() == 1111");

        this->logInfo("Size of pqt1 = " + std::to_string(pqt1->size()));
        this->logInfo("Size of pqt2 = " + std::to_string(pqt2->size()));
        this->logInfo("pqt1:clear");
        pqt1->clear();
        this->logInfo("Size of pqt1 = " + std::to_string(pqt1->size()));

        this->logInfo("========================Fulling pqt1========================");
        for (int data = 1; data < 201; data++)
        {
            int priority = data;
            pqt1->push(priority, data);
            this->logInfo("pqt1:push Priority: " + std::to_string(priority) + " Data:" + std::to_string(data));
            this->assertTrue(pqt1->peekPriority() == 1, "pqt1->peekPriority() == 1");
            this->assertTrue(pqt1->peek() == 1, "pqt1->peek() == 1");
        }
        this->logInfo("======================End Fulling pqt1======================");




        this->logInfo("========================Popping pqt2========================");
        for (int data = 200; data > 0; data--)
        {
            int priority = 201 - data;
            this->assertTrue(pqt2->peekPriority() == priority, "pqt2->peekPriority() == " + std::to_string(priority));
            this->assertTrue(pqt2->pop() == data, "pqt2->pop() == " + std::to_string(data));
        }
        this->logInfo("====================== End Popping pqt2========================");

        this->assertTrue(pqt2->size() == 1, "pqt2->size() == 1");
        this->assertTrue(pqt2->peek() == 1000, "pqt2->peek() == 1000");
        this->assertTrue(pqt2->peekPriority() == 1000, "pqt2->peekPriority() == 1000");
        this->assertTrue(pqt2->pop() == 1000, "pqt2->pop() == 1000");
        this->assertTrue(pqt2->size() == 0, "pqt2->size() == 0");
    
        this->logInfo("End of test PriorityQueueTwoListFunctionsTest");
        delete pqt1;
        pqt1 = nullptr;

        delete pqt2;
        pqt2 = nullptr;

    }

    HeapFunctionsTest::HeapFunctionsTest()
        :SimpleTest("UseCases")
    {
    }

    void HeapFunctionsTest::test()
    {
        this->logInfo("Start of test HeapFunctionsTest");

        this->logInfo("Creating pointer to a Heap:heap1");
        structures::Heap<int>* heap1 = new structures::Heap<int>();


        this->logInfo("Size of heap1 = " + std::to_string(heap1->size()));

        this->logInfo("========================Fulling heap1========================");
        for (int data = 1; data < 11; data++)
        {
            int priority = 11 - data;
            heap1->push(priority, data);
            this->logInfo("heap1:push Priority: " + std::to_string(priority) + " Data:" + std::to_string(data));
            this->assertTrue(heap1->peekPriority() == priority, "heap1->peekPriority() == " + std::to_string(priority));
            this->assertTrue(heap1->peek() == data, "heap1->peek() == " + std::to_string(data));
        }
        this->logInfo("======================End Fulling heap1======================");

        this->logInfo("Size of heap1 = " + std::to_string(heap1->size()));

        this->logInfo("Creating pointer to a Heap:heap2");
        structures::Heap<int>* heap2 = new structures::Heap<int>();

        this->logInfo("heap2:assign heap1");
        heap2->assign(*heap1);

        heap1->push(0, 1337);
        this->logInfo("heap1:push Priority:0 Data:1337");
        this->logInfo("Size of heap1 = " + std::to_string(heap1->size()));
        this->logInfo("Size of heap2 = " + std::to_string(heap2->size()));
        heap2->push(0, 1111);
        this->logInfo("heap2:push Priority:0 Data:1111");
        heap2->push(1000, 1000);
        this->logInfo("heap2:push Priority:1000 Data:1000");

        this->assertTrue(heap1->peek() == 1337, "heap1->peek() == 1337");
        this->assertTrue(heap1->peekPriority() == 0, "heap1->peekPriority() == 0");

        this->assertTrue(heap2->peek() == 1111, "heap2heap2peek() == 1111");
        this->assertTrue(heap2->peekPriority() == 0, "pqt2->peekPriority() == 0");

        this->assertTrue(heap1->pop() == 1337, "heap1->pop() == 1337");
        this->assertTrue(heap2->pop() == 1111, "heap2->pop() == 1111");

        this->logInfo("Size of heap1 = " + std::to_string(heap1->size()));
        this->logInfo("Size of heap1 = " + std::to_string(heap2->size()));
        this->logInfo("heap1:clear");
        heap1->clear();
        this->logInfo("Size of heap1 = " + std::to_string(heap1->size()));

        this->logInfo("========================Fulling heap1========================");
        for (int data = 1; data < 11; data++)
        {
            int priority = data;
            heap1->push(priority, data);
            this->logInfo("heap1:push Priority: " + std::to_string(priority) + " Data:" + std::to_string(data));
            this->assertTrue(heap1->peekPriority() == 1, "heap1->peekPriority() == 1");
            this->assertTrue(heap1->peek() == 1, "heap1->peek() == 1");
        }
        this->logInfo("======================End Fulling heap1======================");




        this->logInfo("========================Popping heap2========================");
        for (int data = 10; data > 0; data--)
        {
            int priority = 11 - data;
            this->assertTrue(heap2->peekPriority() == priority, "heap2->peekPriority() == " + std::to_string(priority));
            this->assertTrue(heap2->pop() == data, "heap2->pop() == " + std::to_string(data));
        }
        this->logInfo("====================== End Popping heap2========================");

        this->assertTrue(heap2->size() == 1, "heap2->size() == 1");
        this->assertTrue(heap2->peek() == 1000, "heap2->peek() == 1000");
        this->assertTrue(heap2->peekPriority() == 1000, "heap2->peekPriority() == 1000");
        this->assertTrue(heap2->pop() == 1000, "heap2->pop() == 1000");
        this->assertTrue(heap2->size() == 0, "heap2->size() == 0");

        this->logInfo("End of test HeapFunctionsTest");
        delete heap1;
        heap1 = nullptr;

        delete heap2;
        heap2 = nullptr;
    }


    Zadanie3_Uloha2::Zadanie3_Uloha2()
        :SimpleTest("Uloha2[A,B,C]")
    {
    }

    template<typename T>
    void Zadanie3_Uloha2::getMethodTime(structures::FileLogConsumer* fileLogger, structures::PriorityQueue<T>* priorityQueue, std::string methodName) {
        int randomData = rand();
        //priority interval <0,100 000>
        int randomPriority = rand() % 100001;

        if (methodName == "push") {
            this->startStopwatch();
            priorityQueue->push(randomPriority,randomData);
            this->stopStopwatch();
        }
        else if (methodName == "pop") {
            this->startStopwatch();
            priorityQueue->pop();
            this->stopStopwatch();
        }
        else if (methodName == "peek") {
            this->startStopwatch();
            priorityQueue->peek();
            this->stopStopwatch();
        }
        else {
            this->fail("TEST: Zadanie3_Uloha2::getMethodTime: Invalid method!!!");
        }


        tests::DurationType duration = this->getElapsedTime();
        fileLogger->logDuration(priorityQueue->size(), duration, methodName);
    }


    template<typename T>
    void Zadanie3_Uloha2::uloha2(structures::PriorityQueue<T>* priorityQueue, int ratioPush, int ratioPop, int ratioPeek, std::string nazov) {
        std::string nazovCSV = nazov + ".csv";

        structures::FileLogConsumer* fileLogConsumer = new structures::FileLogConsumer(nazovCSV);

        fileLogConsumer->SizeTimeNsMethodTitle();
        srand(static_cast<unsigned int>(time(NULL)));

        const int REPEATS = 100000;


        const int pushRatioPercent = (REPEATS / 100) * ratioPush;
        const int popRatioPercent = (REPEATS / 100) * ratioPop;
        const int peekRatioPercent = (REPEATS / 100) * ratioPeek;


        const int level1 = ratioPush;
        const int level2 = level1 + ratioPop;

        int counterPush = 0;
        int counterPop = 0;
        int counterPeek = 0;


        for (int j = 0; j < REPEATS; j++)
        {
            int randomRatio = rand() % 100;


            if (randomRatio < level1 && counterPush < pushRatioPercent) {
                //push
                getMethodTime(fileLogConsumer, priorityQueue, "push");
                counterPush++;
            }
            else if (randomRatio < level2 && counterPop < popRatioPercent && priorityQueue->size() != 0) {
                //pop
                getMethodTime(fileLogConsumer, priorityQueue, "pop");
                counterPop++;
            }
            else if (randomRatio < 100 && counterPeek < peekRatioPercent && priorityQueue->size() != 0) {
                //at
                getMethodTime(fileLogConsumer, priorityQueue, "peek");
                counterPeek++;
            }
            else if (counterPush < pushRatioPercent) {
                //push
                getMethodTime(fileLogConsumer, priorityQueue, "push");
                counterPush++;
            }
            else if (counterPeek < peekRatioPercent && priorityQueue->size() != 0) {
                //peek
                getMethodTime(fileLogConsumer, priorityQueue, "peek");
                counterPeek++;
            }
            else if (counterPop < popRatioPercent && priorityQueue->size() != 0) {
                //pop
                getMethodTime(fileLogConsumer, priorityQueue, "pop");
                counterPop++;
            }
            else if (counterPop < popRatioPercent) {
                //je jedno co tam dam, aj tak to bude prazdne
                priorityQueue->push(0, 0);
                getMethodTime(fileLogConsumer, priorityQueue, "pop");
                counterPop++;
            } else {
                priorityQueue->push(0, 0);
                getMethodTime(fileLogConsumer, priorityQueue, "peek");
                counterPeek++;
                priorityQueue->pop();
            }

        }

        delete fileLogConsumer;
        fileLogConsumer = nullptr;
    }

    void Zadanie3_Uloha2::test() {
        //A===================
        structures::PriorityQueue<int>* HeapA = new structures::Heap<int>();
        uloha2(HeapA, 35, 35, 30,"Heap_A");
        delete HeapA;
        HeapA = nullptr;

        structures::PriorityQueue<int>* TwoListsA = new structures::PriorityQueueTwoLists<int>();
        uloha2(TwoListsA, 35, 35, 30, "PriorityQueueTwoLists_A");
        delete TwoListsA;
        TwoListsA = nullptr;

        //B=======================
        structures::PriorityQueue<int>* HeapB = new structures::Heap<int>();
        uloha2(HeapB, 50, 30, 20, "Heap_B");
        delete HeapB;
        HeapB = nullptr;

        structures::PriorityQueue<int>* TwoListsB = new structures::PriorityQueueTwoLists<int>();
        uloha2(TwoListsB, 50, 30, 20, "PriorityQueueTwoLists_B");
        delete TwoListsB;
        TwoListsB = nullptr;

        //C=======================
        structures::PriorityQueue<int>* HeapC = new structures::Heap<int>();
        uloha2(HeapC, 70, 25, 5, "Heap_C");
        delete HeapC;
        HeapC = nullptr;

        structures::PriorityQueue<int>* TwoListsC = new structures::PriorityQueueTwoLists<int>();
        uloha2(TwoListsC, 70, 25, 5, "PriorityQueueTwoLists_C");
        delete TwoListsC;
        TwoListsC = nullptr;
    }


    Zadanie3_Uloha3::Zadanie3_Uloha3()
        :SimpleTest("Uloha3 - pop,push,peek")
    {
    }

    template<typename T>
    void Zadanie3_Uloha3::uloha3(structures::PriorityQueue<T>* priorityQueue, std::string methodName, std::string nazov) {

        std::string nazovCSV = nazov + ".csv";

        structures::FileLogConsumer* fileLogConsumer = new structures::FileLogConsumer(nazovCSV);
        tests::Zadanie3_Uloha2* cas = new tests::Zadanie3_Uloha2();


        fileLogConsumer->SizeTimeNsMethodTitle();
        srand(static_cast<unsigned int>(time(NULL)));

        const int REPEATS = 100000;
        if (methodName == "push") {
            for (int i = 0; i < REPEATS; i++)
            {    
                cas->getMethodTime(fileLogConsumer, priorityQueue, methodName);
            }
        }
        else if (methodName == "peek") {
            for (int i = 0; i < REPEATS; i++)
            {
                int randomData = rand();
                int randomPriority = rand();
                priorityQueue->push(randomPriority,randomData);

                cas->getMethodTime(fileLogConsumer, priorityQueue, methodName);
            }
        }
        else if (methodName == "pop") {
            for (int i = 0; i < REPEATS; i++)
            {
                int randomData = rand();
                int randomPriority = rand() % 100001;
                priorityQueue->push(randomPriority, randomData);
            }

            for (int i = 0; i < REPEATS; i++)
            {
                cas->getMethodTime(fileLogConsumer, priorityQueue, methodName);
            }
        }
        else {
            this->fail("Zadanie2_Uloha3::uloha3: Invalid method!!!");
        }

        delete cas;
        cas = nullptr;

        delete fileLogConsumer;
        fileLogConsumer = nullptr;
    }
    void Zadanie3_Uloha3::test() {
        
        //push
        structures::PriorityQueue<int>* HeapPush = new structures::Heap<int>();
        uloha3(HeapPush, "push", "Heap_Push");
        delete HeapPush;
        HeapPush = nullptr;
        
        structures::PriorityQueue<int>* twoListsPush = new structures::PriorityQueueTwoLists<int>();
        uloha3(twoListsPush, "push", "TwoLists_Push");
        delete twoListsPush;
        twoListsPush = nullptr;
        
        
        //pop
        structures::PriorityQueue<int>* HeapPop = new structures::Heap<int>();
        uloha3(HeapPop, "pop", "Heap_Pop");
        delete HeapPop;
        HeapPop = nullptr;
       
        
        structures::PriorityQueue<int>* twoListsPop = new structures::PriorityQueueTwoLists<int>();
        uloha3(twoListsPop, "pop", "TwoLists_Pop");
        delete twoListsPop;
        twoListsPop = nullptr;

        //peek
        structures::PriorityQueue<int>* HeapPeek = new structures::Heap<int>();
        uloha3(HeapPeek, "peek", "Heap_Peek");
        delete HeapPeek;
        HeapPeek = nullptr;

        structures::PriorityQueue<int>* twoListsPeek = new structures::PriorityQueueTwoLists<int>();
        uloha3(twoListsPeek, "peek", "TwoLists_Peek");
        delete twoListsPeek;
        twoListsPeek = nullptr;
        
    }


}