#include "stdvector_test.h"
#include "../../structures/_logger/logger.h"
#include <vector>

namespace tests
{
// StdVectorTestInsertion:

    StdVectorTestInsertion::StdVectorTestInsertion() :
        SimpleTest("insertion")
    {
    }

    void StdVectorTestInsertion::test()
    {
        std::vector<int>* vector = new std::vector<int>();

        this->logInfo("Creating an empty vector.");
        this->logInfo("Inserting 10 elements.");
        for (int i = 0; i < 10; ++i)
        {
            vector->push_back(i);
        }
        this->assertTrue(vector->size() == 10, "Vector size is 10.");

        //this->startStopwatch();

        for (int i = 0; i < 10; i++)
        {
            if (vector->at(i) != i)
            {
                this->fail("vector->at(i) != i for i = " + std::to_string(i));
                return;
            }
        }
        this->assertTrue(true, "vector->at(i) == i for i = 0 .. 9");

        //auto time = this->getElapsedTime();
        //structures::Logger::getInstance().logDuration(vector->size(), time, "add");

        //delete vector;
    }

// StdVectorTestSelectors:

    StdVectorTestSelectors::StdVectorTestSelectors() :
        SimpleTest("selection")
    {
    }

    void StdVectorTestSelectors::test()
    {
        std::vector<int>* vector = new std::vector<int>();

        this->logInfo("Creating an empty vector.");
        this->logInfo("Inserting 10 elements.");
        for (int i = 0; i < 10; ++i)
        {
            vector->push_back(i);
        }

        this->assertTrue(vector->front() == 0, "First element 0 using std::vector::front.");
        this->assertTrue(vector->back() == 9, "Last element 9 using std::vector::back.");

        for (int i = 0; i < 10; i++)
        {
            if (vector->at(i) != i)
            {
                this->fail("vector->at(i) != i for i = " + std::to_string(i));
                return;
            }

            if ((*vector)[i] != i)
            {
                this->fail("vector[i] != i for i = " + std::to_string(i));
                return;
            }
        }
        this->succeed("vector[i] == i for i = 0 .. 9");
        this->succeed("vector->at(i) == i for i = 0 .. 9");

        delete vector;
    }

// StdVectorTestErase:

    StdVectorTestErase::StdVectorTestErase() :
        SimpleTest("deletion")
    {
    }

    void StdVectorTestErase::test()
    {
        this->logInfo("Creating an empty vector.");
        std::vector<int>* vector = new std::vector<int>();
        this->logInfo("Inserting 10 elements.");
        for (int i = 0; i < 10; ++i)
        {
            vector->push_back(i);
        }

        this->logInfo("Deleting even elements.");
        for (int i = 0; i < 5; ++i)
        {
            vector->erase(vector->begin() + i);
        }
        this->assertTrue(vector->size() == 5, "Vector size is 5.");

        this->logInfo("Checking whether only odd elements are left.");
        for (int i = 0; i < 5; ++i)
        {
            if (vector->at(i) != 2 * i + 1)
            {
                this->fail("vector[i] = 2 * i + 1 for i = " + std::to_string(i));
                return;
            }
        }
        this->succeed("vector[i] = 2 * i + 1");

        delete vector;
    }

// StdVectorTestIterator:

    StdVectorTestIterator::StdVectorTestIterator() :
        SimpleTest("iterator")
    {
    }

    void StdVectorTestIterator::test()
    {
        structures::Logger::getInstance().logInfo("Starting to test std::vector iterator.");

        this->logInfo("Creating an empty vector.");
        std::vector<int>* vector = new std::vector<int>();
        this->logInfo("Inserting 10 elements.");
        for (int i = 0; i < 10; ++i)
        {
            vector->push_back(i);
        }

        std::vector<int>::iterator it = vector->begin();
        std::vector<int>::iterator lastIt = vector->end();

        for (int i = 0; i < 10; ++i)
        {
            if (*it != i)
            {
                this->fail("vector[i] != i for i = " + std::to_string(i));
                return;
            }
            ++it;
        }
        this->succeed("vector[i] == i for i = 0 .. 9");
        this->assertTrue(it == lastIt, "Begin iterator == end iterator after 10 increments.");

        delete vector;

        structures::Logger::getInstance().logInfo("End of test of std::vector iterator.");
    }

// StdVectorTestCopy:

    StdVectorTestCopy::StdVectorTestCopy() :
        SimpleTest("copy")
    {
    }

    void StdVectorTestCopy::test()
    {
        this->logInfo("Creating an empty vector.");
        std::vector<int>* vector = new std::vector<int>();
        this->logInfo("Inserting 10 elements.");
        for (int i = 0; i < 10; ++i)
        {
            vector->push_back(i);
        }

        this->logInfo("Creating copy of the vector.");
        std::vector<int>* vector2 = new std::vector<int>(*vector);
        this->assertTrue(vector->size() == vector2->size(), "Vector sizes are equal.");
        this->assertTrue(*vector == *vector2, "Vector is equal to its copy: vector == vector2.");

        this->logInfo("Erasing some elements from the first vector.");
        for (int i = 0; i < 5; ++i)
        {
            vector->erase(vector->begin() + i);
        }
        this->assertFalse(vector->size() == vector2->size(), "Vector sizes are different.");
        this->assertFalse(*vector == *vector2, "Vector differs from its copy after deletion: vector != vector2.");

        this->logInfo("Erasing some elements from the second vector.");
        for (int i = 0; i < 5; ++i)
        {
            vector2->erase(vector2->begin() + i);
        }
        this->assertTrue(vector->size() == vector2->size(), "Vector sizes are equal.");
        this->assertTrue(*vector == *vector2, "Now, vector is equal to its copy again.: vector == vector2.");

        delete vector;
        delete vector2;
    }

// StdVectorTestOverall:

    StdVectorTestOverall::StdVectorTestOverall() :
        ComplexTest("std::vector")
    {
        addTest(new StdVectorTestInsertion());
        addTest(new StdVectorTestSelectors());
        addTest(new StdVectorTestErase());
        addTest(new StdVectorTestIterator());
        addTest(new StdVectorTestCopy());
    }
}