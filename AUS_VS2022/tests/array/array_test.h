#pragma once

#include "../test.h"

namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania pola avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class ArrayTestInterface
		: public SimpleTest
	{
	public:
		ArrayTestInterface();
		void test() override;
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju pole.
	/// </summary>
	class ArrayTestOverall
		: public ComplexTest
	{
	public:
		ArrayTestOverall();
	};



}