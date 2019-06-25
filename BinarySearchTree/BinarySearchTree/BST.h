#pragma once
#include <iostream>
using namespace std;

// Assumed that a node with the same key value is not inserted

template <class T>
class Node {
private:
	T data;
	Node<T>* leftChild;
	Node<T>* rightChild;

public:
	Node(T data) {
		this->data = data;
		leftChild = rightChild = NULL;
	}
	T			getData() { return data; }
	void		setData(T data) { this->data = data; }
	Node<T>*	getLeftChild() { return leftChild; }
	void		setLeftChild(Node<T>* child) { leftChild = child; }
	Node<T>*	getRightChild() { return rightChild; }
	void		setRightChild(Node<T>* child) { rightChild = child; }
};

template <class T>
class BST {
private:
	Node<T>* root;

public:
	BST() { root = NULL; }
	~BST();

	Node<T>*	GetRoot() { return root; }
	bool		IsEmpty() { return root == NULL; }
	Node<T>*	Search(Node<T>* p, T target);
	void		Insert(const T& data);
	void		Delete(T data);
	Node<T>*	SearchMinNode(Node<T>* subroot);	// search min node starts from subroot

	void		ThreeWayJoin(BST<T>& small, T mid, BST<T>& big);
	void		TwoWayJoin(BST<T>& small, BST<T>& big);	// join small & big tree and make new tree
	void		Split(T key, BST<T>& small, Node<T>* mid, BST<T>& big);

	void		PreorderTraversal(Node<T>* root);
	void		InorderTraversal(Node<T>* root);
	void		PostorderTraversal(Node<T>* root);
};

template<class T>
inline BST<T>::~BST()
{
}

template<class T>
inline Node<T>* BST<T>::Search(Node<T>* p, T target)
{
	if (p == NULL)
		return NULL;

	if (target < p->getData())
		return Search(p->getLeftChild(), target);
	else if (target > p->getData())
		return Search(p->getRightChild(), target);
	else
		return p;
}

template<class T>
inline void BST<T>::Insert(const T& data)
{
	Node<T>* pCur = root;
	Node<T>* ppCur = NULL;

	// find the position to insert
	while (pCur) {
		ppCur = pCur;
		if (data < pCur->getData())
			pCur = pCur->getLeftChild();
		else
			pCur = pCur->getRightChild();
	}

	// insert at that position
	pCur = new Node<T>(data);
	if (root) {
		if (data < ppCur->getData())
			ppCur->setLeftChild(pCur);
		else
			ppCur->setRightChild(pCur);
	}
	else
		root = pCur;
}

template<class T>
inline void BST<T>::Delete(T data)
{
	if (IsEmpty()) {
		cout << "[DELETE ERROR] Tree is empty" << endl;
		return;
	}

	// find pp and p
	Node<T>* pCur = root;
	Node<T>* ppCur = NULL;
	while (pCur) {
		if (data < pCur->getData()) {
			ppCur = pCur;
			pCur = pCur->getLeftChild();	// move to left child
		}
		else if (data > pCur->getData()) {
			ppCur = pCur;
			pCur = pCur->getRightChild();	// move to right child
		}
		else
			break;	// find target
	}

	// if target wasn't root
	if (ppCur) {
		// leaf node
		if (pCur->getLeftChild() == NULL && pCur->getRightChild() == NULL) {
			if (ppCur->getLeftChild() == pCur) {
				// if pCur is left child of ppCur
				ppCur->setLeftChild(NULL);
				delete pCur;
			}
			else {
				// otherwise
				ppCur->setRightChild(NULL);
				delete pCur;
			}
		}
		// two child
		else if (pCur->getLeftChild() && pCur->getRightChild()) {
			Node<T>* MinNode = SearchMinNode(pCur->getRightChild());	// search min node
			T temp = MinNode->getData();	// copy the MinNode's data
			Delete(MinNode->getData());	// delete MinNode from tree
			pCur->setData(temp);	// set to MinNode's data
		}
		// one child
		else {
			if (ppCur->getLeftChild() == pCur) {
				// if pCur is left child of ppCur
				ppCur->setLeftChild((pCur->getLeftChild() != NULL) ? pCur->getLeftChild() : pCur->getRightChild());
				delete pCur;	// select pCur's child and connect to ppCur
			}
			else {
				// otherwise
				ppCur->setRightChild((pCur->getLeftChild() != NULL) ? pCur->getLeftChild() : pCur->getRightChild());
				delete pCur;	// select pCur's child and connect to ppCur
			}
		}
	}
	// if target was root
	else {
		// no child
		if (pCur->getLeftChild() == NULL && pCur->getRightChild() == NULL) {
			root = NULL;
			delete pCur;
		}
		// two child
		else if (pCur->getLeftChild() != NULL && pCur->getRightChild() != NULL) {
			Node<T>* MinNode = SearchMinNode(pCur->getRightChild());	// search min node
			T temp = MinNode->getData();	// copy the MinNode's data
			Delete(MinNode->getData());	// delete MinNode from tree
			pCur->setData(temp);	// set to MinNode's data
		}
		// one child
		else {
			if (pCur->getLeftChild() != NULL) {
				root = pCur->getLeftChild();	// set new root
				delete pCur;	// delet old root
			}
			else {
				root = pCur->getRightChild();	// set new root
				delete pCur;	// delet old root
			}
		}
	}
}

template<class T>
inline Node<T>* BST<T>::SearchMinNode(Node<T>* subroot)
{
	Node<T>* pCur = subroot;
	while (pCur->getLeftChild() != NULL)
		pCur = pCur->getLeftChild();
	return pCur;
}

template<class T>
inline void BST<T>::ThreeWayJoin(BST<T>& small, T mid, BST<T>& big)
{
	root = new Node<T>(mid);	// mid is root
	root->setLeftChild(small.root);		// set left subtree
	root->setRightChild(big.root);		// set right subtree
}

template<class T>
inline void BST<T>::TwoWayJoin(BST<T>& small, BST<T>& big)
{
	// if one of the tree was empty, the other tree will be the result of operation
	if (small.IsEmpty() || big.IsEmpty()) {
		root = (small.IsEmpty()) ? big.GetRoot() : small.GetRoot();
		return;
	}

	// delete min node(it will be mid node) from big tree
	Node<T>* MinNode = SearchMinNode(big.root);
	T mid = MinNode->getData();
	big.Delete(mid);

	// call ThreeWayJoin()
	ThreeWayJoin(small, mid, big);
}

template<class T>
inline void BST<T>::Split(T key, BST<T>& small, Node<T>* mid, BST<T>& big)
{
	// if this was empty tree
	if (root == NULL) {
		small.root = big.root = NULL;
		return;
	}

	T	dummy;
	Node<T>* sHead = new Node<T>(dummy);
	Node<T>* bHead = new Node<T>(dummy);	// create dummy node for head of tree
	Node<T>* s = sHead, b = bHead, currNode = root;

	while (currNode) {
		if (key < currNode->getData()) {
			b->setLeftChild(currNode);
			b = currNode;
			currNode = currNode->getLeftChild();
		}
		else if (key > currNode->getData()) {
			s->setRightChild(currNode);
			s = currNode;
			currNode = currNode->getRightChild();
		}
		else {
			// find the node /w key value
			s->setRightChild(currNode->getLeftChild());
			b->setLeftChild(currNode->getRightChild());
			small.root = s->getRightChild();
			big.root = b->getLeftChild();
			mid = new Node<T>(currNode.getData());	// create new node /w currNode data
			delete sHead;
			delete bHead;
			return;
		}
	}

	// can't find the node /w key value
	s->setRightChild(NULL);
	b->setLeftChild(NULL);
	small.root = s->getRightChild();
	big.root = b->getLeftChild();
	mid = NULL;	// can't create mid node
	delete sHead;
	delete bHead;
}

template<class T>
inline void BST<T>::PreorderTraversal(Node<T>* root)
{
	if (root == NULL)
		return;

	cout << root->getData() << ' ';
	PreorderTraversal(root->getLeftChild());
	PreorderTraversal(root->getRightChild());
}

template<class T>
inline void BST<T>::InorderTraversal(Node<T>* root)
{
	if (root == NULL)
		return;

	InorderTraversal(root->getLeftChild());
	cout << root->getData() << ' ';
	InorderTraversal(root->getRightChild());
}

template<class T>
inline void BST<T>::PostorderTraversal(Node<T>* root)
{
	if (root == NULL)
		return;

	PostorderTraversal(root->getLeftChild());
	PostorderTraversal(root->getRightChild());
	cout << root->getData() << ' ';
}
