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

	Node<T>* getNext() { return pNext; }
	void	 setNext(Node<T>* next) { pNext = next; }
	T		getData() { return data; }
	void	setData(T data) { this->data = data; }
};

template <class T>
class Queue {
private:
	Node<T>* front;
	Node<T>* rear;
	int		 size;
public:
	Queue() {
		front = rear = NULL;
		size = 0;
	}
	~Queue();

	bool IsEmpty() { return front == NULL; }
	T Front() { return *front; }
	T Rear() { return *rear; }
	void EnQueue(T data);
	void DeQueue();
	int	GetSize() { return size; }
	void	DisplayQueue();
};

template<class T>
inline Queue<T>::~Queue()
{
	for (int i = 0; i < size; i++)
		DeQueue();
}

template <class T>
void Queue<T>::EnQueue(T data) {
	// create new node
	Node<T>* NewNode = new Node<T>(data);

	// queue is empty
	if (IsEmpty()) {
		front = NewNode;
		rear = NewNode;
	}
	// otherwise
	else {
		rear->setNext(NewNode);
		rear = NewNode;
	}
	size++;
}

template <class T>
void Queue<T>::DeQueue() {
	if (IsEmpty()) {
		cout << "[POP FAILED] Queue is already empty!" << endl;
		return;
	}

	Node<T>* old = front;
	front = front->getNext();
	delete old;
	size--;
}

template<class T>
inline void Queue<T>::DisplayQueue()
{
	cout << endl << "========== Queue Status ==========" << endl;
	cout << "Queue size = " << GetSize() << endl;
	Node<T>* pCur = front;
	while (pCur) {
		cout << pCur->getData() << ' ';
		pCur = pCur->getNext();
	}
	cout << endl << "==================================" << endl;
}
