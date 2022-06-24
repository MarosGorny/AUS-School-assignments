#pragma once

#include "../test.h"

namespace tests
{
    /// <summary>
    /// Testuje vkladanie do vektora.
    /// </summary>
    class StdVectorTestInsertion
        : public SimpleTest
    {
    public:
        StdVectorTestInsertion();
        void test() override;
    };

    /// <summary>
    /// Testuje spristupnovanie prvkov vektora.
    /// </summary>
    class StdVectorTestSelectors
        : public SimpleTest
    {
    public:
        StdVectorTestSelectors();
        void test() override;
    };

    /// <summary>
    /// Testuje mazanie prvkov z vektora.
    /// </summary>
    class StdVectorTestErase
        : public SimpleTest
    {
    public:
        StdVectorTestErase();
        void test() override;
    };

    /// <summary>
    /// Testuje iterator vektora.
    /// </summary>
    class StdVectorTestIterator
        : public SimpleTest
    {
    public:
        StdVectorTestIterator();
        void test() override;
    };

    /// <summary>
    /// Testuje kopirovaci konstruktor vektora.
    /// </summary>
    class StdVectorTestCopy
        : public SimpleTest
    {
    public:
        StdVectorTestCopy();
        void test() override;
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy vektora.
    /// </summary>
    class StdVectorTestOverall
        : public ComplexTest
    {
    public:
        StdVectorTestOverall();
    };
}