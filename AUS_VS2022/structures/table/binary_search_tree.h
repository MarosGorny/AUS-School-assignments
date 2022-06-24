#pragma once

#include "table.h"
#include "../list/list.h"
#include "../tree/binary_tree.h"
#include <stdexcept>

namespace structures
{

	/// <summary> Binarny vyhladavaci strom. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class BinarySearchTree : public Table<K, T>
	{
	public:
		typedef typename BinaryTreeNode<TableItem<K, T>*> BSTTreeNode;
	public:
		/// <summary> Konstruktor. </summary>
		BinarySearchTree();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> BinarySearchTree, z ktoreho sa prevezmu vlastnosti. </param>
		BinarySearchTree(BinarySearchTree<K, T>& other);

		/// <summary> Destruktor. </summary>
		~BinarySearchTree();

		/// <summary> Vrati pocet prvkov v tabulke. </summary>
		/// <returns> Pocet prvkov v tabulke. </returns>
		size_t size() override;

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vrati adresou data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Adresa dat s danym klucom. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak kluc nepatri do tabulky. </exception>
		T& find(const K& key) override;

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>
		void insert(const K& key, const T& data) override;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>
		T remove(const K& key) override;

		/// <summary> Bezpecne ziska data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <param name = "data"> Najdene data (vystupny parameter). </param>
		/// <returns> true, ak sa podarilo najst a naplnit data s danym klucom, false inak. </returns>
		bool tryFind(const K& key, T& data) override;

		/// <summary> Zisti, ci tabulka obsahuje data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> true, tabulka obsahuje dany kluc, false inak. </returns>
		bool containsKey(const K& key) override;

		/// <summary> Vymaze tabulku. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getBeginIterator() override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getEndIterator() override;

	protected:
		/// <summary> Najde vrchol binarneho vyhladavacieho stromu s danym klucom. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <param name = "found"> Vystupny parameter, ktory indikuje, ci sa kluc nasiel. </param>
		/// <returns> Vrchol binarneho vyhladavacieho stromu s danym klucom. Ak sa kluc v tabulke nenachadza, vrati otca, ktoreho by mal mat vrchol s takym klucom. </returns>
		typename BSTTreeNode* findBSTNode(K key, bool& found);

	protected:
		/// <summary> Binarny strom s datami. </summary>
		BinaryTree<TableItem<K, T>*>* binaryTree_;
		//kompozicia

		/// <summary> Pocet prvkov v binarnom vyhladavacom strome. </summary>
		size_t size_;

		/// <summary> Vlozi vrchol do stromu tak, aby nedoslo k naruseniu usporiadania BST. </summary>
		/// <param name = "node"> Vrchol stromu, ktory ma byt vlozeny. </param>
		/// <returns> true, ak sa podarilo vrchol vlozit (teda v strome nie je vrchol s rovnakym klucom), false inak. </returns>
		bool tryToInsertNode(BSTTreeNode* node);

		/// <summary> Bezpecne vyjme zo stromu vrchol stromu tak, aby nedoslo k naruseniu usporiadania BST. </summary>
		/// <param name = "node"> Vrchol stromu, ktory ma byt vyjmuty. </param>
		/// <remarks> Vrchol nebude zruseny, iba odstraneny zo stromu a ziadne vrcholy nebudu ukazovat na neho a ani on nebude ukazovat na ziadne ine vrcholy. </remarks>
		void extractNode(BSTTreeNode* node);
	};

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::BinarySearchTree() :
		Table<K, T>(),
		binaryTree_(new BinaryTree<TableItem<K, T>*>()),
		size_(0)
	{
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::BinarySearchTree(BinarySearchTree<K, T>& other) :
		BinarySearchTree()
	{
		assign(other);
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::~BinarySearchTree()
	{
		this->clear();

		delete this->binaryTree_;
		this->binaryTree_ = nullptr;
	}

	template<typename K, typename T>
	inline size_t BinarySearchTree<K, T>::size()
	{
		return this->size_;
	}

	template<typename K, typename T>
	inline Structure& BinarySearchTree<K, T>::assign(Structure& other)
	{
		if (this != &other) {
			BinarySearchTree<K, T>& otherBST = dynamic_cast<BinarySearchTree<K, T>&>(other);

			//najskor sa vycistit
			this->clear();

			Tree<TableItem<K, T>*>::PreOrderTreeIterator* curIt =
				new Tree<TableItem<K, T>*>::PreOrderTreeIterator(otherBST.binaryTree_->getRoot());

			Tree<TableItem<K, T>*>::PreOrderTreeIterator* endIt =
				new Tree<TableItem<K, T>*>::PreOrderTreeIterator(nullptr);

			while (*curIt != *endIt) {
				TableItem<K, T>* otherItem = *(*curIt);

				this->insert(otherItem->getKey(), otherItem->accessData());

				++(*curIt);
			}

			delete curIt;
			delete endIt;

		}
		return *this;
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::equals(Structure& other)
	{
		return Table<K, T>::equalsTable(dynamic_cast<BinarySearchTree<K, T>*>(&other));
	}

	template<typename K, typename T>
	inline T& BinarySearchTree<K, T>::find(const K& key)
	{
		bool found;
		BSTTreeNode* node = this->findBSTNode(key, found);

		if (!found) {
			throw std::out_of_range("BinarySearchTree<K, T>::find: Key is not present in BST!");
		}
		else {
			return node->accessData()->accessData();	//najprv table item a potom data
		}
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::insert(const K& key, const T& data)
	{
		TableItem<K, T>* tableItem = new TableItem<K, T>(key, data);
		BSTTreeNode* newNode = new BSTTreeNode(tableItem);

		if (!this->tryToInsertNode(newNode)) {
			delete tableItem;
			delete newNode;
			throw std::logic_error("BinarySearchTree<K, T>::insert: Key is already present in BST!");
		}

	}

	template<typename K, typename T>
	inline T BinarySearchTree<K, T>::remove(const K& key)
	{
		bool found;
		BSTTreeNode* node = this->findBSTNode(key, found);

		if (!found) {
			throw std::logic_error("BinarySearchTree<K, T>::remove: Key is not present!");
		}
		else {
			this->extractNode(node);
			T data = node->accessData()->accessData();

			delete node->accessData(); //zmazanie tableItemu
			delete node;

			this->size_--;

			return data;
		}

	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::tryFind(const K& key, T& data)
	{
		bool found;
		BSTTreeNode* node = this->findBSTNode(key, found);

		if (found) {
			data = node->accessData()->accessData();
		}

		return found;
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::containsKey(const K& key)
	{
		bool found;
		this->findBSTNode(key, found);
		return found;

	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::clear()
	{
		for (TableItem<K, T>* item : *this->binaryTree_) { //ale moze byt aj iba this, bez ->binaryTree, alebo *this->binaryTree_
			delete item;
		}
		this->binaryTree_->clear();
		
		this->size_ = 0;
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* BinarySearchTree<K, T>::getBeginIterator()
	{
		return this->binaryTree_->getBeginIterator();
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* BinarySearchTree<K, T>::getEndIterator()
	{
		return this->binaryTree_->getEndIterator();
	}

	template<typename K, typename T>
	inline typename BinarySearchTree<K, T>::BSTTreeNode* BinarySearchTree<K, T>::findBSTNode(K key, bool& found)
	{
		if (this->size_ == 0) {
			found = false;
			return nullptr;
		}

		BSTTreeNode* node = dynamic_cast<BSTTreeNode*>(this->binaryTree_->getRoot());
		BSTTreeNode* parent = nullptr;
		while (node != nullptr) {

			K nodeKey = node->accessData()->getKey(); //najprv table item
			if (key == nodeKey) {
				found = true;
				return node;
			}
			else if (key < nodeKey) {
				parent = node;
				node = node->getLeftSon();
				
			}
			else {
				parent = node;
				node = node->getRightSon();
			}
		} 

		found = false;
		return parent;

	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::tryToInsertNode(BSTTreeNode* node)
	{
		bool found;
		BSTTreeNode* parent = this->findBSTNode(node->accessData()->getKey(), found);

		if (found) {
			return false;
		}
		else {
			if (parent == nullptr) {
				this->binaryTree_->replaceRoot(node);
			}
			else if (node->accessData()->getKey() < parent->accessData()->getKey()) {
				parent->setLeftSon(node);
			}
			else {
				parent->setRightSon(node);
			}
			this->size_++;
			return true;
		}
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::extractNode(BSTTreeNode* node)
	{

		BSTTreeNode* parent = node->getParent();
		BSTTreeNode* inOrderNode = nullptr;

		if (node->degree() == 1) {
			//ak ma laveho syna
			if (node->hasLeftSon()) {
				inOrderNode = node->changeLeftSon(nullptr);
			}
			else {
				inOrderNode = node->changeRightSon(nullptr);
			}
			
		}
		else if (node->degree() == 2) {
			//ist do praveho podstromu
			inOrderNode = node->getRightSon();
			//az pokial nepridem na najviac lavy uzol,list
			while (inOrderNode->hasLeftSon()) {
				inOrderNode = inOrderNode->getLeftSon();
			}

			//extraktni list
			this->extractNode(inOrderNode);

			inOrderNode->setLeftSon(node->changeLeftSon(nullptr));
			inOrderNode->setRightSon(node->changeRightSon(nullptr));
		}

		if (node->isRoot()) {
			this->binaryTree_->replaceRoot(inOrderNode);
		}
		else {
			//nahrad po vetve
			if (node->isLeftSon()) {
				parent->setLeftSon(inOrderNode);
			}
			else {
				parent->setRightSon(inOrderNode);
			}
		}
		//ak to nie je list
		if (inOrderNode != nullptr) {
			inOrderNode->setParent(parent);
		}

	}

}