#pragma once
#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

template <class T>
class AVLNode {
private:
	T	data;
	int height;	// height
	int	bf;		// balance factor
	AVLNode<T>*	leftChild;
	AVLNode<T>* rightChild;

public:
	AVLNode(T data) {
		leftChild = rightChild = NULL;
		bf = 0;
		height = 1;
		this->data = data;
	}

	T	getData() { return data; }

	template <class T>
	friend class AVL;
};

template <class T>
class AVL {
private:
	AVLNode<T>*	root;

public:
	AVL() { root = NULL; }

	AVLNode<T>*	GetRoot() { return root; }

	void		Insert(T data);
	void		Delete(T data);

	void		UpdateHeightBalance(AVLNode<T>* node);	// update the balance factor of node

	AVLNode<T>* LL_rotation(AVLNode<T>* A, AVLNode<T>* B);	// LL rotation and return new subroot
	AVLNode<T>* LR_rotation(AVLNode<T>* A, AVLNode<T>* B);	// LR rotation and return new subroot
	AVLNode<T>* RR_rotation(AVLNode<T>* A, AVLNode<T>* B);	// RR rotation and return new subroot
	AVLNode<T>* RL_rotation(AVLNode<T>* A, AVLNode<T>* B);	// RL rotation and return new subroot

	void		ReBalance(stack<AVLNode<T>*>& checklist);	// rebalance the tree
	AVLNode<T>* GetMinNode(AVLNode<T>* subroot, stack<AVLNode<T>*>& stack);	// get minimun node

	void		DisplayTree(AVLNode<T>* subroot);	// display the tree /w inorder traversal
};

template<class T>
inline void AVL<T>::Insert(T data) {
	stack<AVLNode<T>*> stackMain;
	AVLNode<T>* NewNode = new AVLNode<T>(data);
	AVLNode<T>* pCur = root;
	AVLNode<T>* pPrev = NULL;
	while (pCur) {
		stackMain.push(pCur);

		if (data < pCur->data) {
			pPrev = pCur;
			pCur = pCur->leftChild;
		}
		else if (data > pCur->data) {
			pPrev = pCur;
			pCur = pCur->rightChild;
		}
		else
			return;	// ignore SAME data!
	}

	// insert new node
	if (pPrev == NULL) {
		root = NewNode;
		return;
	}
	else {
		if (data < pPrev->data)
			pPrev->leftChild = NewNode;
		else
			pPrev->rightChild = NewNode;
	}

	// check tree unbalanced
	ReBalance(stackMain);
}

template<class T>
inline void AVL<T>::Delete(T data) {
	// create stack for balance check
	stack<AVLNode<T>*>	stackMain;
	stack<AVLNode<T>*>	stackSub;

	// find the target node /w data
	AVLNode<T>* pCur = root;
	AVLNode<T>* pPrev = NULL;
	while (pCur) {
		if (data < pCur->data) {
			pPrev = pCur;
			stackMain.push(pPrev);	// push in stack
			pCur = pCur->leftChild;
		}
		else if (data > pCur->data) {
			pPrev = pCur;
			stackMain.push(pPrev);	// push in stack
			pCur = pCur->rightChild;
		}
		else if (data == pCur->data)
			break;
		else {
			cout << "Delete ERROR : cannot find data" << endl;
			return;
		}
	}

	// leaf node
	if (pCur->leftChild == NULL && pCur->rightChild == NULL) {
		if (pPrev) {
			if (pCur == pPrev->leftChild)
				pPrev->leftChild = NULL;
			else
				pPrev->rightChild = NULL;
		}
		else
			root = NULL;	// if target was root node
	}
	// /w two child
	else if (pCur->leftChild != NULL && pCur->rightChild != NULL) {
		AVLNode<T>* newRootPrev = GetMinNode(pCur->rightChild, stackSub);
		AVLNode<T>* newRoot = stackSub.top();
		stackMain.push(newRoot);
		stackSub.pop();	// pop new subroot(for stack purpose)
		
		if (newRootPrev) {
			newRootPrev->leftChild = newRoot->rightChild;
			newRoot->rightChild = pCur->rightChild;
			if(newRootPrev->leftChild != NULL)
				stackSub.push(newRootPrev->leftChild);	// push start point of rebalance operation
		}
		newRoot->leftChild = pCur->leftChild;

		if (pPrev) {
			if (pCur == pPrev->leftChild)
				pPrev->leftChild = newRoot;
			else
				pPrev->rightChild = newRoot;
		}
		else
			root = newRoot;	// if target was root node
	}
	// /w one child
	else {
		if (pPrev) {
			if (pPrev->leftChild == pCur) {
				if (pCur->leftChild != NULL)
					pPrev->leftChild = pCur->leftChild;
				else
					pPrev->leftChild = pCur->rightChild;
			}
			else {
				if (pCur->leftChild != NULL)
					pPrev->rightChild = pCur->leftChild;
				else
					pPrev->rightChild = pCur->rightChild;
			}
		}
		else {
			// if target was root node
			if (pCur->leftChild != NULL)
				root = pCur->leftChild;
			else
				root = pCur->rightChild;
		}
	}

	delete pCur;	// delete the target node
	ReBalance(stackSub);
	ReBalance(stackMain);	// check balance and transform
}

template<class T>
inline void AVL<T>::UpdateHeightBalance(AVLNode<T>* node) {
	int leftHeight = 0;
	int rightHeight = 0;

	if (node->leftChild != NULL)
		leftHeight = node->leftChild->height;
	if (node->rightChild != NULL)
		rightHeight = node->rightChild->height;

	if (leftHeight < rightHeight)
		node->height = rightHeight + 1;
	else
		node->height = leftHeight + 1;

	node->bf = leftHeight - rightHeight;
}

template<class T>
inline AVLNode<T>* AVL<T>::LL_rotation(AVLNode<T>* A, AVLNode<T>* B) {
	// LL rotation
	A->leftChild = B->rightChild;
	B->rightChild = A;

	UpdateHeightBalance(A);
	UpdateHeightBalance(B);

	return B;
}

template<class T>
inline AVLNode<T>* AVL<T>::LR_rotation(AVLNode<T>* A, AVLNode<T>* B) {
	// LR rotation = RR + LL
	AVLNode<T>* C = B->rightChild;
	A->leftChild = RR_rotation(B, C);
	C = LL_rotation(A, A->leftChild);

	return C;
}

template<class T>
inline AVLNode<T>* AVL<T>::RR_rotation(AVLNode<T>* A, AVLNode<T>* B) {
	// RR rotation 
	A->rightChild = B->leftChild;
	B->leftChild = A;

	UpdateHeightBalance(A);
	UpdateHeightBalance(B);

	return B;
}

template<class T>
inline AVLNode<T>* AVL<T>::RL_rotation(AVLNode<T>* A, AVLNode<T>* B) {
	// RL rotation = LL + RR
	AVLNode<T>* C = B->leftChild;
	A->rightChild = LL_rotation(B, C);
	C = RR_rotation(A, A->rightChild);

	return C;
}

template<class T>
inline void AVL<T>::ReBalance(stack<AVLNode<T>*>& checklist) {
	while (!checklist.empty()) {
		AVLNode<T>* checkNode = checklist.top();
		checklist.pop();

		UpdateHeightBalance(checkNode);	// update the balance factor

		// balance status
		if (-1 <= checkNode->bf && checkNode->bf <= 1)
			continue;

		// unbalance status
		AVLNode<T>* newRoot = NULL;
		if (checkNode->bf > 1) {
			AVLNode<T>* B = checkNode->leftChild;
			if (B->bf >= 1)
				newRoot = LL_rotation(checkNode, B);
			else
				newRoot = LR_rotation(checkNode, B);
		}
		else if (checkNode->bf < -1) {
			AVLNode<T>* B = checkNode->rightChild;
			if (B->bf == -1)
				newRoot = RR_rotation(checkNode, B);
			else
				newRoot = RL_rotation(checkNode, B);
		}

		// reset the subroot
		if (!checklist.empty()) {
			AVLNode<T>* parentNode = checklist.top();
			if (parentNode->leftChild == checkNode)
				parentNode->leftChild = newRoot;
			else
				parentNode->rightChild = newRoot;
		}
		else
			root = newRoot;
	}
}

template<class T>
inline AVLNode<T>* AVL<T>::GetMinNode(AVLNode<T>* subroot, stack<AVLNode<T>*>& stack) {
	// stack contains nodes : subroot <-> minimum node(without minimum node)
	AVLNode<T>* prev = NULL;
	AVLNode<T>* target = subroot;
	stack.push(target);
	while (target->leftChild != NULL) {
		prev = target;
		target = target->leftChild;
		stack.push(target);
	}
	
	return prev;
}

template<class T>
inline void AVL<T>::DisplayTree(AVLNode<T>* subroot) {
	if (subroot == NULL)
		return;

	DisplayTree(subroot->leftChild);
	cout << subroot->data << ' ';
	DisplayTree(subroot->rightChild);
}
