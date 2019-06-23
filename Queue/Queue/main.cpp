#include "Queue.h"
#include <string>

void main() {
	Queue<int> iqueue;
	Queue<string> squeue;
	
	for(int i=0; i<5; i++)
		iqueue.EnQueue(i);
	iqueue.DisplayQueue();

	cout << endl << "After Dequeue 3 times..." << endl;
	for(int i=0; i<3; i++)
		iqueue.DeQueue();
	iqueue.DisplayQueue();

	squeue.EnQueue("simpson");
	squeue.EnQueue("bart");
	squeue.EnQueue("lisa");
	squeue.DisplayQueue();

	cout << endl << "After Dequeue twice..." << endl;
	squeue.DeQueue();
	squeue.DeQueue();
	squeue.DisplayQueue();

}