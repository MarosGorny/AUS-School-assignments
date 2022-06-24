#pragma once

#include "../test.h"
#include "../../structures/tree/tree.h"

namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania stromu avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class TreeTestInterface :
		public SimpleTest
	{
	public:
		TreeTestInterface();
		void test() override;

	protected:
		virtual structures::Tree<int>* makeTree() = 0;
	};

	/// <summary>
	/// Zavola vsetky metody daneho stromu.
	/// </summary>
	class MultiWayTreeTestInterface
		: public TreeTestInterface
	{
	protected:
		structures::Tree<int>* makeTree() override;
	};

	/// <summary>
	/// Zavola vsetky metody daneho stromu.
	/// </summary>
	class KWayTreeTestInterface
		: public TreeTestInterface
	{
	protected:
		structures::Tree<int>* makeTree() override;
	};

	/// <summary>
	/// Zavola vsetky metody daneho stromu.
	/// </summary>
	class BinaryTreeTestInterface
		: public TreeTestInterface
	{
	protected:
		structures::Tree<int>* makeTree() override;
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju dany strom.
	/// </summary>
	class MultiWayTreeTestOverall
		: public ComplexTest
	{
	public:
		MultiWayTreeTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju dany strom.
	/// </summary>
	class KWayTreeTestOverall
		: public ComplexTest
	{
	public:
		KWayTreeTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju dany strom.
	/// </summary>
	class BinaryTreeTestOverall
		: public ComplexTest
	{
	public:
		BinaryTreeTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju strom.
	/// </summary>
	class TreeTestOverall :
		public ComplexTest
	{
	public:
		TreeTestOverall();
	};
}