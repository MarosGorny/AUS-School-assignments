#include "array_test.h"
#include "../../structures/array/array.h"

namespace tests
{
// ArrayTestInterface:

	ArrayTestInterface::ArrayTestInterface() :
		SimpleTest("Interface")
	{
	}

	void ArrayTestInterface::test()
	{
		structures::Array<int>* testArray = new structures::Array<int>(10);
		testArray->copy(*testArray, 0, *testArray, 0, 1);
		testArray->isEmpty();
		testArray->assign(*testArray);
		testArray->equals(*testArray);
		testArray->at(0);
		testArray->size();
		delete testArray;
		SimpleTest::logPass("Compiled.");
	}

// ArrayTestOverall:

	ArrayTestOverall::ArrayTestOverall() :
		ComplexTest("Array")
	{
		//doplnit vsetky simple testy
		addTest(new ArrayTestInterface());
	}



}



