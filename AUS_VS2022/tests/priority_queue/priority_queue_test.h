#pragma once

#include "../test.h"
#include "../../structures/priority_queue/priority_queue.h"
#include "../../structures/priority_queue/priority_queue_list.h"
#include "../../structures/_logger/file_log_consumer.h"

namespace tests
{
    /// <summary>
    /// Zavola vsetky metody z rozhrania prioritneho frontu avsak nekontroluje ich spravnost.
    /// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
    /// </summary>
    class PriorityQueueTestInterface
        : public SimpleTest
    {
    public:
        PriorityQueueTestInterface();
        void test() override;

    protected:
        virtual structures::PriorityQueue<int>* makePriorityQueue() = 0;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueUnsortedArrayListTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueSortedArrayListTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueLimitedSortedArrayListTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueLinkedListTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueTwoListsTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class HeapTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueUnsortedArrayListTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueUnsortedArrayListTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueSortedArrayListTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueSortedArrayListTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueLimitedSortedArrayListTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueLimitedSortedArrayListTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueLinkedListTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueLinkedListTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueTwoListsTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueTwoListsTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class HeapTestOverall
        : public ComplexTest
    {
    public:
        HeapTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju prioritny front.
    /// </summary>
    class PriorityQueueTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueTestOverall();
    };


    /// <summary>
    /// Zahrna v sebe testy fuknci(UseCases), ktore testuju prioritny front - dvoj list.
    /// </summary>
    class PriorityQueueTwoListFunctionsTest
        : public SimpleTest
    {
    public:
        PriorityQueueTwoListFunctionsTest();
        void test() override;
    };

    /// <summary>
    /// Zahrna v sebe testy fuknci(UseCases), ktore testuju heap.
    /// </summary>
    class HeapFunctionsTest
        : public SimpleTest
    {
    public:
        HeapFunctionsTest();
        void test() override;
    };

    /// <summary>
    /// Zahrna test scenarov A,B,C v ulohe2, domace zadanie 3
    /// <summary>
    class Zadanie3_Uloha2
        : public SimpleTest {
    public:
        Zadanie3_Uloha2();

        /// <summary> Do loggeru zapise cas metody ktora sa vybrala. </summary>
        /// <param name = "fileLogger"> Pointer na File Logger do ktoreho sa cas bude zapisovat. </param>
        /// <param name = "priorityQueue"> Pointer na Prioritny front v ktorom sa budu vykonavat akcie. </param>
        /// <param name = "methodName"> Nazov metody ktora sa ma vykonat. </param>
        template<typename T>
        void getMethodTime(structures::FileLogConsumer* fileLogger, structures::PriorityQueue<T>* priorityQueue, std::string methodName);

        /// <summary> Rozdelenie volania metod podla pomeru funkcii, vykonanie urcity pocet volani a nasledne zapisanie dat do CSV suboru. </summary>
        /// <param name = "priorityQueue"> Pointer na Prioritny front v ktorom sa budu vykonavat akcie. </param>
        /// <param name = "ratioPush"> Perecentualny pomer volania metody Push() z celkovu 100 percentneho pomeru. </param>
        /// <param name = "ratioPop"> Perecentualny pomer volania metody Pop() z celkovu 100 percentneho pomeru. </param>
        /// <param name = "ratioPeek"> Perecentualny pomer volania metody Peek() z celkovu 100 percentneho pomeru. </param>
        /// <param name = "nazov"> Nazov CSV suboru ktory sa zapise. (bez .CSV pripony) </param>
        template<typename T>
        void uloha2(structures::PriorityQueue<T>* priorityQueue,int ratioPush, int ratioPop, int ratioPeek, std::string nazov);
        
        /// <summary>
        /// Vytvorenie prioritnych frontov a nasledne vykonanie akcii pre ulohu 2, zadanie 3.
        /// <summary>
        void test() override;
    };

    /// <summary>
    /// Zahrna test rychlosti metod push,pop,peek v ulohe3, domace zadanie 3
    /// <summary>
    class Zadanie3_Uloha3
        :public SimpleTest {
    public:
        Zadanie3_Uloha3();

        template<typename T>
        void uloha3(structures::PriorityQueue<T>* priorityQueue, std::string methodName, std::string nazov);
        void test() override;
    };

}