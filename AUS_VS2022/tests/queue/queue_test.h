#pragma once

#include "../test.h"
#include "../../structures/queue/queue.h"

namespace tests
{
    /// <summary>
    /// Zavola vsetky metody z rozhrania frontu avsak nekontroluje ich spravnost.
    /// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
    /// </summary>
    class QueueTestInterface
        : public SimpleTest
    {
    public:
        QueueTestInterface(std::string name);
        void test() override;

    protected:
        virtual structures::Queue<int>* makeQueue() = 0;
    };

    /// <summary>
    /// Zavola vsetky metody implicitneho frontu.
    /// </summary>
    class ImplicitQueueTestInterface
        : public QueueTestInterface
    {
    public:
        ImplicitQueueTestInterface();

    protected:
        structures::Queue<int>* makeQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody explicitneho frontu.
    /// </summary>
    class ExplicitQueueTestInterface
        : public QueueTestInterface
    {
    public:
        ExplicitQueueTestInterface();

    protected:
        structures::Queue<int>* makeQueue() override;
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju implicitny front.
    /// </summary>
    class ImplicitQueueTestOverall
        : public ComplexTest
    {
    public:
        ImplicitQueueTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju explicitny front.
    /// </summary>
    class ExplicitQueueTestOverall
        : public ComplexTest
    {
    public:
        ExplicitQueueTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju implicitny a explicitny front.
    /// </summary>
    class QueueTestOverall
        : public ComplexTest
    {
    public:
        QueueTestOverall();
    };
}