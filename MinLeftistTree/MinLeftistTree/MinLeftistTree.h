#pragma once
#include <iostream>
using namespace std;

template <class T>
class LeftistNode {
private:
	T	data;
	LeftistNode<T>* leftChild;
	LeftistNode<T>* rightChild;
	int	shortest;

public:
	LeftistNode(T newdata) {
		leftChild = rightChild = NULL;
		data = newdata;
		shortest = 0;
	}
	~LeftistNode() {}

	template<class T>
	friend class MinLeftistTree;
};

template <class T>
class MinLeftistTree {
private:
	LeftistNode<T>* root;

	LeftistNode<T>*	Meld(LeftistNode<T>* a, LeftistNode<T>* b);

public:
	MinLeftistTree() { root = NULL; }
	~MinLeftistTree() {}

	void	Meld(MinLeftistTree<T>* b);

	bool	IsEmpty() { return root == NULL; }
	const T	Top() { return root->data; }
	void	Push(T	newdata);
	void	Pop();
};

template<class T>
inline LeftistNode<T>* MinLeftistTree<T>::Meld(LeftistNode<T>* a, LeftistNode<T>* b) {
	if (a->data > b->data) {
		LeftistNode<T>* temp = a;
		a = b;
		b = temp;
	}	// swap if a is bigger than b

	// 
	if (a->rightChild == NULL)
		a->rightChild = b;
	else
		a->rightChild = Meld(a->rightChild, b);

	// 
	if (a->leftChild == NULL || a->leftChild->shortest < a->rightChild->shortest) {
		LeftistNode<T>* temp = a->leftChild;
		a->leftChild = a->rightChild;
		a->rightChild = temp;
	}

	if (a->rightChild != NULL)
		a->shortest = a->rightChild->shortest + 1;
	else
		a->shortest = 1;
	
	return a;	// return root node of melded
}

template<class T>
inline void MinLeftistTree<T>::Meld(MinLeftistTree<T>* b) {
	if (IsEmpty())
		root = b->root;
	else if(!b->IsEmpty())
		root = Meld(root, b->root);
	b->root = NULL;
}

template<class T>
inline void MinLeftistTree<T>::Push(T newdata) {
	// create new tree /w one node
	MinLeftistTree<T> temp;
	temp.root = new LeftistNode<T>(newdata);

	// meld two tree
	Meld(&temp);
}

template<class T>
inline void MinLeftistTree<T>::Pop() {
	// meld root's left and right child
	LeftistNode<T>* newroot = Meld(root->leftChild, root->rightChild);

	// replace root node
	delete root;
	root = newroot;
}