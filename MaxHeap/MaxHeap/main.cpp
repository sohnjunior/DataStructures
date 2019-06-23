#include "MaxHeap.h"

void main() {
	MaxHeap<int> MXHeap;

	MXHeap.Push(14);
	MXHeap.Push(12);
	MXHeap.Push(7);
	MXHeap.Push(10);
	MXHeap.Push(8);
	MXHeap.Push(6);

	int popped = MXHeap.Pop();
	cout << popped << " pop!" << endl;
	popped = MXHeap.Pop();
	cout << popped << " pop!" << endl;

	cout << endl;
	MXHeap.Push(5);
	MXHeap.Push(9);
	MXHeap.Push(18);
	MXHeap.Push(19);
	MXHeap.Push(20);
	MXHeap.Push(13);
	MXHeap.Push(11);
	MXHeap.Push(16);

	for (int i = 0; i < 15; i++) {
		popped = MXHeap.Pop();
		cout << popped << " pop!" << endl;
	}
}