#pragma once
#include <iostream>
using namespace std;

template <class T>
class Node {
private:
	T data;
	Node<T>* pNext;

public:
	Node(T data) {
		this->data = data;
		pNext = NULL;
	}

	Node<T>*	getNext() { return pNext; }
	void		setNext(Node<T>* next) { pNext = next; }
	T			getData() { return data; }
};

template <class T>
class SLinkedList {
private:
	Node<T>* head;
	int		 size;
public:
	SLinkedList() { head = NULL; size = 0; }
	~SLinkedList();

	bool IsEmpty() { return head == NULL; }
	void InsertNode(int index, T data);
	void AppendNode(T data);
	int	GetSize() { return size; }
	Node<T>* GetNodeAt(int index);
	int	FindNode(T data);
	void DeleteNode(int index);
	void DisplayList();
};

template<class T>
inline SLinkedList<T>::~SLinkedList()
{
	Node<T>* pPrev = NULL;
	Node<T>* pCur = head;
	while (pCur) {
		pPrev = pCur;
		pCur = pCur->getNext();
		delete pPrev;
	}
}

template <class T>
void SLinkedList<T>::InsertNode(int index, T data) {
	if (index < 0)
		return;

	// find prev node for inserting
	int currIndex = 1;
	Node<T>* pPrev = head;
	while (pPrev && currIndex < index) {
		currIndex++;
		pPrev = pPrev->getNext();
	}
	// out of range
	if (pPrev == NULL && index > 0)
		return;

	// create new node
	Node<T>* NewNode = new Node<T>(data);
	if (index == 0) {
		NewNode->setNext(head);
		head = NewNode;
	}
	else {
		NewNode->setNext(pPrev->getNext());
		pPrev->setNext(NewNode);
	}
	size++;
}

template<class T>
inline void SLinkedList<T>::AppendNode(T data)
{
	// get tail node
	Node<T>* pTail = head;
	while (pTail && pTail->getNext())
		pTail = pTail->getNext();

	Node<T>* NewNode = new Node<T>(data);
	if (pTail == NULL) {
		// if node is empty
		head = NewNode;
	}
	else {
		// otherwise
		pTail->setNext(NewNode);
	}
	size++;
}

template<class T>
inline Node<T>* SLinkedList<T>::GetNodeAt(int index)
{
	if (index < 0)
		return NULL;

	int currIndex = 0;
	Node<T>* pCur = head;
	while (pCur && currIndex < index) {
		pCur = pCur->getNext();
		currIndex++;
	}
		
	if (pCur == NULL)
		return NULL;
	else
		return pCur;
}

template<class T>
inline int SLinkedList<T>::FindNode(T data)
{
	int currIndex = 0;
	Node<T>* pCur = head;
	while (pCur && pCur->getData() != data) {
		pCur = pCur->getNext();
		currIndex++;
	}

	if (pCur)
		return currIndex;
	else
		return -1;
}

template<class T>
inline void SLinkedList<T>::DeleteNode(int index)
{
	if (IsEmpty())
		return;

	Node<T>* pPrev = NULL;
	Node<T>* pCur = head;
	int currIndex = 0;
	while (pCur && currIndex < index) {
		currIndex++;
		pPrev = pCur;
		pCur = pCur->getNext();
	}

	if (pCur) {
		if (pPrev) {
			pPrev->setNext(pCur->getNext());
			delete pCur;
		}
		else {
			head = pCur->getNext();
			delete pCur;
		}
		size--;
	}
}

template<class T>
inline void SLinkedList<T>::DisplayList()
{
	Node<T>* pCur = head;
	while (pCur) {
		cout << pCur->getData() << ' ';
		pCur = pCur->getNext();
	}
	cout << endl;
}
