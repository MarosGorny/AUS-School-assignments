#include "tree_test.h"
#include "../../structures/tree/binary_tree.h"
#include "../../structures/tree/k_way_tree.h"
#include "../../structures/tree/multi_way_tree.h"

namespace tests
{
	TreeTestInterface::TreeTestInterface() :
		SimpleTest("Interface")
	{
	}

	void TreeTestInterface::test()
	{
		structures::Tree<int>* tree = this->makeTree();
		tree->assign(*tree);
		tree->equals(*tree);
		tree->isEmpty();
		tree->size();
		tree->clear();
		tree->getRoot();
		tree->replaceRoot(tree->createTreeNodeInstance());
		delete tree->getBeginIterator();
		delete tree->getEndIterator();
		delete tree;
		this->logPass("Compiled.");
	}

	structures::Tree<int>* MultiWayTreeTestInterface::makeTree()
	{
		return new structures::MultiWayTree<int>();
	}

	structures::Tree<int>* KWayTreeTestInterface::makeTree()
	{
		return new structures::KWayTree<int, 3>();
	}

	structures::Tree<int>* BinaryTreeTestInterface::makeTree()
	{
		return new structures::BinaryTree<int>();
	}

	MultiWayTreeTestOverall::MultiWayTreeTestOverall() :
		ComplexTest("MultiWayTree")
	{
		addTest(new MultiWayTreeTestInterface());
	}

	KWayTreeTestOverall::KWayTreeTestOverall() :
		ComplexTest("KWayTree")
	{
		addTest(new KWayTreeTestInterface());
	}

	BinaryTreeTestOverall::BinaryTreeTestOverall() :
		ComplexTest("BinaryTree")
	{
		addTest(new BinaryTreeTestInterface());
	}

	TreeTestOverall::TreeTestOverall() :
		ComplexTest("Tree")
	{
		addTest(new MultiWayTreeTestOverall());
		addTest(new KWayTreeTestOverall());
		addTest(new BinaryTreeTestOverall());
	}


}