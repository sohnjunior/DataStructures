#pragma once
#include <iostream>
using namespace std;

// Assuem that type T is already defined with operator '>' or '<' or '=='
// to compare priority of nodes

template <class T>
class MaxHeap {
private :
	T* heap;
	int heapSize;
	int capacity;

public:
	MaxHeap(int capacity = 10) {
		if (capacity < 1) {
			cout << "Capacity must be >= 1" << endl;
			return;
		}
		this->capacity = capacity;
		heapSize = 0;
		heap = new T[capacity + 1];	// ignore heap[0] for convenience
	}

	bool IsEmpty() { return heapSize == 0; }
	void Push(const T& data);
	T Pop();

	void ChangeSize1D(int oldsize, int newsize);
};

template<class T>
inline void MaxHeap<T>::Push(const T & data)
{
	// if queue is full, resize
	if (heapSize == capacity) {
		ChangeSize1D(capacity, capacity * 2);
		capacity *= 2;
	}

	int currNode = ++heapSize;	// insert at last pos of heap
	while (currNode != 1 && heap[currNode / 2] < data) {
		heap[currNode] = heap[currNode / 2];
		currNode /= 2;	// bubbling up
	}

	heap[currNode] = data;	// insert data
}

template<class T>
inline T MaxHeap<T>::Pop()
{
	if (IsEmpty()) {
		cout << "[POP ERROR] queue is already full" << endl;
		return -1;
	}

	T popped = heap[1];	// popped node

	T lastE = heap[heapSize--];
	int currNode = 1;
	int child = 2;

	while (child <= heapSize) {
		if (child < heapSize && heap[child] < heap[child + 1])
			child = child + 1;	// find the largest child
		
		// find the position
		if (lastE >= heap[child])
			break;	
		// otherwise
		else {
			heap[currNode] = heap[child];
			currNode = child;
			child *= 2;	// trickle down
		}
	}

	heap[currNode] = lastE;
	return popped;
}

template<class T>
inline void MaxHeap<T>::ChangeSize1D(int oldsize, int newsize)
{
	T* oldheap = heap;
	T* newheap = new T[newsize];
	
	// copy the data to new heap
	for (int i = 0; i <= oldsize; i++)
		newheap[i] = oldheap[i];

	heap = newheap;
	delete oldheap;
}
