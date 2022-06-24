#pragma once

#include "../structure.h"
#include "../structure_iterator.h"
#include "../data_item.h"
//#include <queue>
#include "../queue/explicit_queue.h"


namespace structures
{
	/// <summary> Vrchol stromu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo vrchole stromu. </typepram>
	template <typename T>
	class TreeNode : public DataItem<T>
	{
	public:
		/// <summary> Vytvori plytku kopiu vrchola (teda skopiruje iba data a smerniky na synov). </summary>
		/// <returns> Vystvorena plytka kopia vrcholu. </returns>
		virtual TreeNode<T>* shallowCopy() = 0;

		/// <summary> Vytvori a vrati hlboku kopiu vrchola (teda skopiruje data a skopiruje celu stromovu strukturu). </summary>
		/// <returns> Hlboka kopia vrchola. </returns>
		virtual TreeNode<T>* deepCopy();

		/// <summary> Test, ci je koren. </summary>
		/// <returns> true, ak je koren, false inak. </returns>
		bool isRoot();

		/// <summary> Test, ci je list. </summary>
		/// <returns> true, ak je list, false inak. </returns>
		virtual bool isLeaf() = 0;

		/// <summary> Spristupni rodica vrcholu. </summary>
		/// <returns> Rodic vrcholu. </returns>
		TreeNode<T>* getParent();

		/// <summary> Nastavi rodica na nullptr. </summary>
		void resetParent();

		/// <summary> Zmeni rodica vrcholu. </summary>
		/// <param name = "parent"> Novy rodic vrcholu. </param>
		void setParent(TreeNode<T>* parent);

		/// <summary> Spristupni brata vrcholu podla jeho pozicie u spolocneho rodica. </summary>
		/// <param name = "brothersOrder"> Poradie brata u rodica. </param>
		/// <exception cref=""> Vyhodena, ak je korenom. </exception>
		/// <returns> Brat vrcholu. </returns>
		virtual TreeNode<T>* getBrother(int brothersOrder);

		/// <summary> Spristupni syna vrcholu podla jeho pozicie v tomto vrchole. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <returns> Syn vrcholu. </returns>
		virtual TreeNode<T>* getSon(int order) = 0;

		/// <summary> Vlozi noveho syna vrcholu na dane miesto. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <remarks>
		/// Spravanie sa lisi podla toho, ci sa jedna o vrchol s pevnym alebo variabilnym poctom synov.
		/// Vsetky smerniky zucastnenych vrcholov budu spravne nastavene.
		/// </remarks>
		virtual void insertSon(TreeNode<T>* son, int order) = 0;

		/// <summary> Nahradi syna vrcholu na danom mieste. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je poradie neplatne. </exception>
		/// <returns> Nahradeny syn vrcholu. </returns>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		virtual TreeNode<T>* replaceSon(TreeNode<T>* son, int order) = 0;

		/// <summary> Odstrani syna na danom mieste. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <returns> Odstraneny syn vrcholu. </returns>
		/// <remarks>
		/// Spravanie sa lisi podla toho, ci sa jedna o vrchol s pevnym alebo variabilnym poctom synov.
		/// Vsetky smerniky zucastnenych vrcholov budu spravne nastavene.
		/// </remarks>
		virtual TreeNode<T>* removeSon(int order) = 0;

		/// <summary> Vrati stupen vrcholu. </summary>
		/// <returns> Stupen vrcholu. </returns>
		virtual int degree() = 0;

		/// <summary> Vrati pocet vrcholov v podstrome. </summary>
		/// <returns> Pocet vrcholov v podstrome. </returns>
		virtual size_t sizeOfSubtree();

	protected:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		TreeNode(const T& data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Vrchol stromu, z ktoreho sa prevezmu vlastnosti. </param>
		TreeNode(TreeNode<T>& other);

		/// <summary> Odkaz na rodica. </summary>
		TreeNode<T>* parent_;
	};

	/// <summary> Strom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v strome. </typepram>
	template <typename T>
	class Tree : public Structure, public Iterable<T>
	{
	public:
		/// <summary> Konstruktor, inicializuje prazdny strom. </summary>
		Tree();

		/// <summary> Kopirovaci konstruktor. </summary>
		Tree(Tree<T>& other);

		/// <summary> Destruktor. </summary>
		~Tree();

		/// <summary> Zisti, ci je struktura prazdna. </summary>
		/// <returns> true, ak je struktura prazdna, false inak. </returns>
		bool isEmpty() override;

		/// <summary> Vrati pocet vrcholov v strome. </summary>
		/// <returns> Pocet vrcholov v strome. </returns>
		size_t size() override;

		/// <summary> Vymaze strom. </summary>
		virtual void clear();

		/// <summary> Spristupni koren stromu. </summary>
		/// <returns> Koren stromu. </returns>
		TreeNode<T>* getRoot();

		/// <summary> Nahradi koren stromu. </summary>
		/// <param name = "newRoot">  Novy koren stromu. </param>
		/// <returns> Povodny koren stromu. </returns>
		virtual TreeNode<T>* replaceRoot(TreeNode<T>* newRoot);

		/// <summary> Vytvori a vrati instanciu vrcholu stromu. </summary>
		/// <returns> Vytvorena instancia vrcholu stromu. </returns>
		/// <remarks>
		/// Kazdy strom spravuje vrcholy ineho typu, mali by vsak byt jednotne v celom strome.
		/// Tato tovarenska metoda by mala byt pretazena v kazdom potomkovi stromu tak, aby vracala vrcholy, ktore ten strom ocakava.
		/// Instance vrcholov by mali byt vytvarane vyhradne pomocou tejto metody.
		/// </remarks>
		virtual TreeNode<T>* createTreeNodeInstance() = 0;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() override;

	protected:
		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assignTree(Tree<T>& other);

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equalsTree(Tree<T>* other);

	private:
		/// <summary> Koren stromu. </summary>
		TreeNode<T>* root_;

	protected:
		/// <summary> Iterator pre Tree. </summary>
		class TreeIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			TreeIterator();

			/// <summary> Destruktor. </summary>
			~TreeIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator=(Iterator<T>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(Iterator<T>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			T operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<T>& operator++() override;

		protected:
			/// <summary> Prehliadka stromu. </summary>
			Queue<TreeNode<T>*>* path_;
		};

	public:
		class PreOrderTreeIterator : public TreeIterator
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "startNode"> Vrchol podstromu, cez ktory ma iterovat. </param>
			PreOrderTreeIterator(TreeNode<T>* startNode);
		private:
			/// <summary> Zostavi do path_ prehliadku stromu v poradi preorder. </summary>
			/// <param name = "current"> Aktualny spracovavany vrchol stromu. </param>
			void populatePath(TreeNode<T>* current);
		};

		class PostOrderTreeIterator: public TreeIterator
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "startNode"> Vrchol podstromu, cez ktory ma iterovat. </param>
			PostOrderTreeIterator(TreeNode<T>* startNode);
		private:
			/// <summary> Zostavi do path_ prehliadku stromu v poradi postorder. </summary>
			/// <param name = "path"> Cesta stromom, ktoru zostavuje. </param>
			/// <param name = "current"> Aktualny spracovavany vrchol stromu. </param>
			void populatePath(TreeNode<T>* current);
		};

		class LevelOrderTreeIterator : public TreeIterator
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "startNode"> Vrchol podstromu, cez ktory ma iterovat. </param>
			LevelOrderTreeIterator(TreeNode<T>* startNode);
		private:
			/// <summary> Zostavi do path_ prehliadku stromu v poradi levelorder. </summary>
			/// <param name = "current"> Aktualny spracovavany vrchol stromu. </param>
			void populatePath(TreeNode<T>* current);
		};
	};

	template<typename T>
	inline TreeNode<T>* TreeNode<T>::deepCopy()
	{
	    TreeNode<T>* thisCopy = this->shallowCopy();
		int processedSons = 0;
		for (int i = 0; processedSons < this->degree(); i++) {
			TreeNode<T>* son = this->getSon(i);
			if (son != nullptr) {
				TreeNode<T>* sonCopy = son->deepCopy();
				thisCopy->replaceSon(sonCopy, i);
				processedSons++;
			}
		}
		return thisCopy;
	}

	template<typename T>
	inline bool TreeNode<T>::isRoot()
	{
		return this->parent_ == nullptr;
	}

	template<typename T>
	inline TreeNode<T>* TreeNode<T>::getParent()
	{
		return this->parent_;
	}

	template<typename T>
	inline void TreeNode<T>::resetParent()
	{
		this->parent_ = nullptr;
	}

	template<typename T>
	inline void TreeNode<T>::setParent(TreeNode<T>* parent)
	{
		parent_ = parent;
	}

	template<typename T>
	inline TreeNode<T>* TreeNode<T>::getBrother(int brothersOrder)
	{
		//if(this->parent_ == nullptr)
		if (this->isRoot()) {
			throw std::logic_error("TreeNode<T>::getBrother: Node is root and has no brothers.");
		}
		return this->parent_->getSon(brothersOrder);
	}

	template<typename T>
	inline size_t TreeNode<T>::sizeOfSubtree()
	{
		size_t count = 1;	//zaratam automaticky seba
		int processedSons = 0;
		for (int i = 0; processedSons < this->degree(); i++) {
			TreeNode<T>* son = this->getSon(i);
			if (son != nullptr) {
				count += son->sizeOfSubtree();
				processedSons++;
			}
		}
		return count;
	}

	template<typename T>
	inline TreeNode<T>::TreeNode(const T& data):
		DataItem<T>(data),
		parent_(nullptr)
	{
	}

	template<typename T>
	inline TreeNode<T>::TreeNode(TreeNode<T>& other):
		DataItem<T>(other),
		parent_(other.parent_)
	{
	}

	template<typename T>
	inline Tree<T>::~Tree()
	{
		this->clear();
	}

	template<typename T>
	inline bool Tree<T>::isEmpty()
	{
		return this->root_ == nullptr;
	}

	template<typename T>
	inline size_t Tree<T>::size()
	{
		return this->root_ == nullptr ? 0 : this->root_->sizeOfSubtree();
	}

	template<typename T>
	inline Iterator<T>* Tree<T>::getBeginIterator()
	{
		return new PreOrderTreeIterator(root_);
	}

	template<typename T>
	inline Iterator<T>* Tree<T>::getEndIterator()
	{
		return new PreOrderTreeIterator(nullptr);
	}

	template<typename T>
	inline Structure& Tree<T>::assignTree(Tree<T>& other)
	{
		if (this != &other) {
		//	Toto je zbytocne, lebo beriem strom
			Tree<T>& otherTree = dynamic_cast<Tree<T>&>(other);
			this->clear();
		//Tu uz mozem pracovat s other
			this->root_ = otherTree.root_ == nullptr ? nullptr : otherTree.root_->deepCopy();
		}
		return *this;
	}

	template<typename T>
	inline bool Tree<T>::equalsTree(Tree<T>* other)
	{
		if (other == nullptr) {
			return false;
		}

		Iterator<T>* curThis = this->getBeginIterator();
		Iterator<T>* endThis = this->getEndIterator();

		Iterator<T>* curOther = other->getBeginIterator();
		Iterator<T>* endOther = other->getEndIterator();

		//to su pointre ale ja chcem objekty
		while (*curThis != *endThis && *curOther != *endOther) {
			T itemThis = *(*curThis);	//operator hviezdicka od iteratora ale najprv chcem objekt
			T itemOther = *(*curOther);

			if (itemThis != itemOther) {
				return false;
			}

			++(*curThis);
			++(*curOther);
		}

		delete curThis;		//getBeginIterator vytvara novy objekt
		delete endThis;

		delete curOther;
		delete endOther;

		return true;

	/*  EKVIVALENT horneho while
		//spravim pre order a zistim ci su v rovnakom poradi
		//implementacia je spravena tak ze vracia T a nie TreeNode
		for (T item : *this) {
			if (item != otherItem) {
				return false;
			}
		}

		return true;
		*/
	}

	template<typename T>
	inline Tree<T>::Tree():
		Structure(),
		Iterable<T>(),
		root_(nullptr)
	{
	}

	template<typename T>
	inline Tree<T>::Tree(Tree<T>& other):
		Tree<T>()
	{
		assignTree(other);
	}

	template<typename T>
	inline void Tree<T>::clear()
	{
		//stavame na predpoklade, ze destruktor automaticky zavola delete potomkov
		delete this->root_;
		this->root_ = nullptr;
	}

	template<typename T>
	inline TreeNode<T>* Tree<T>::getRoot()
	{
		return root_;
	}

	template<typename T>
	inline TreeNode<T>* Tree<T>::replaceRoot(TreeNode<T>* newRoot)
	{
		TreeNode<T>* oldRoot = this->root_;
		this->root_ = newRoot;
		return oldRoot;
 	}

	template<typename T>
	inline Tree<T>::TreeIterator::TreeIterator():
		Iterator<T>(),
		path_(new ExplicitQueue<TreeNode<T>*>())
	{
	}

	template<typename T>
	inline Tree<T>::TreeIterator::~TreeIterator()
	{
		delete this->path_;
		this->path_ = nullptr;
	}

	template<typename T>
	inline Iterator<T>& Tree<T>::TreeIterator::operator=(Iterator<T>& other)
	{
		if (this != &other) {
			TreeIterator& otherIt = dynamic_cast<TreeIterator&>(other);
			this->path_->assign(*otherIt.path_);
		}

		return *this;
	}

	template<typename T>
	inline bool Tree<T>::TreeIterator::operator!=(Iterator<T>& other)
	{
		if (this == &other) {
			return false;
		}
		//skontrolovat atributy, ale musim pretypovat,
		//tu sa oplati cez hviezdicku, lebo nullptr
		TreeIterator* otherIt = dynamic_cast<TreeIterator*>(&other);
		if (otherIt == nullptr) {
			return true;
		}

		return !this->path_->equals(*otherIt->path_);
	}

	template<typename T>
	inline T Tree<T>::TreeIterator::operator*()
	{
		return this->path_->peek()->accessData();
	}

	template<typename T>
	inline Iterator<T>& Tree<T>::TreeIterator::operator++()
	{
		this->path_->pop();
		return *this;
	}

	template<typename T>
	inline Tree<T>::PreOrderTreeIterator::PreOrderTreeIterator(TreeNode<T>* startNode):
		TreeIterator()
	{
		populatePath(startNode);
	}

	template<typename T>
	inline void Tree<T>::PreOrderTreeIterator::populatePath(TreeNode<T>* current)
	{
		if (current == nullptr) {
			return;
		}
		this->path_->push(current);

		for (int i = 0, processedSons = 0; processedSons < current->degree(); i++) {
			TreeNode<T>* son = current->getSon(i);
			if (son != nullptr) {
				this->populatePath(son);
				processedSons++;
			}
		}
	}

	template<typename T>
	inline Tree<T>::PostOrderTreeIterator::PostOrderTreeIterator(TreeNode<T>* startNode) :
		TreeIterator()
	{
		populatePath(startNode);
	}

	template<typename T>
	inline void Tree<T>::PostOrderTreeIterator::populatePath(TreeNode<T>* current)
	{
		if (current == nullptr) {
			return;
		}

		for (int i = 0, processedSons = 0; processedSons < current->degree(); i++) {
			TreeNode<T>* son = current->getSon(i);
			if (son != nullptr) {
				this->populatePath(son);
				processedSons++;
			}
		}
		this->path_->push(current);
	}

	template<typename T>
	inline Tree<T>::LevelOrderTreeIterator::LevelOrderTreeIterator(TreeNode<T>* startNode) :
		TreeIterator()
	{
		populatePath(startNode);
	}

	template<typename T>
	inline void Tree<T>::LevelOrderTreeIterator::populatePath(TreeNode<T>* current)
	{
		if (current == nullptr) {
			return;
		}

		Queue<TreeNode<T>*>* processQueue = new ExplicitQueue<TreeNode<T>*>();
		processQueue->push(current);
		while (processQueue->isEmpty()) {
			TreeNode<T>* node = processQueue->pop();
			this->path_->push(node);

			for (int i = 0, processedSons = 0; processedSons < node->degree(); i++) {
				TreeNode<T>* son = node->getSon(i);
				if (son != nullptr) {
					processQueue->push(son);
					processedSons++;
				}
			}
		}
	}

}

