#pragma once

#include "../test.h"
#include "../../structures/stack/stack.h"

namespace tests
{
    /// <summary>
    /// Zavola vsetky metody z rozhrania zasobnika avsak nekontroluje ich spravnost.
    /// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
    /// </summary>
    class StackTestInterface
        : public SimpleTest
    {
    public:
        StackTestInterface(std::string name);
        void test() override;

    protected:
        virtual structures::Stack<int>* makeStack() = 0;
    };

    /// <summary>
    /// Zavola vsetky metody implicitneho zasobika.
    /// </summary>
    class ImplicitStackTestInterface
        : public StackTestInterface
    {
    public:
        ImplicitStackTestInterface();

    protected:
        structures::Stack<int>* makeStack() override;
    };

    /// <summary>
    /// Zavola vsetky metody explicitneho zasobika.
    /// </summary>
    class ExplicitStackTestInterface
        : public StackTestInterface
    {
    public:
        ExplicitStackTestInterface();

    protected:
        structures::Stack<int>* makeStack() override;
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju implicitny zasobnik.
    /// </summary>
    class ImplicitStackTestOverall
        : public ComplexTest
    {
    public:
        ImplicitStackTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju explicitny zasobnik.
    /// </summary>
    class ExplicitStackTestOverall
        : public ComplexTest
    {
    public:
        ExplicitStackTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju implicitny a explicitny zasobnik.
    /// </summary>
    class StackTestOverall
        : public ComplexTest
    {
    public:
        StackTestOverall();
    };
}