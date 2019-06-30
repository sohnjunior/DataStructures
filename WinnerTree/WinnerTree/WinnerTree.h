#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

template <class T>
class Record {
private:
	T	key;
	int	id;	// run ID
	Record<T>*	pNext;

public:
	Record(T data, int id) { 
		key = data;
		this->id = id;
		pNext = NULL;
	}

	T	GetKey() { return key; }
	int	GetID() { return id; }

	Record<T>*	getNext() { return pNext; }
	void		setNext(Record<T>* next) { pNext = next; }
};

template <class T>
class Run {
private:
	Record<T>* front;
	Record<T>* rear;
	int		size;	// run size
	int		id;		// run ID

public:
	Run(int id) { 
		front = rear = NULL;
		this->id = id;
	}
	~Run() {
		int cursize = size;
		for (int i = 0; i < cursize; i++)
			DeQueue();
	}

	bool	IsEmpty() { return front == NULL; }
	int		GetSize() { return size; }
	Record<T>* GetFrontRef() { return front; }

	void	EnQueue(T data);
	void	DeQueue();
};

template<class T>
inline void Run<T>::EnQueue(T data)
{
	// create new record
	Record<T>* NewNode = new Record<T>(data, id);

	if (IsEmpty()) {
		front = NewNode;
		rear = NewNode;
	}
	else {
		rear->setNext(NewNode);
		rear = NewNode;
	}

	size++;
}

template<class T>
inline void Run<T>::DeQueue()
{
	if (IsEmpty()) {
		cout << "DEQUEUE ERROR : RUN is Empty!" << endl;
		return;
	}

	// remove front node
	Record<T>* target = front;
	front = front->getNext();
	delete target;
	size--;
}


template <class T>
class WinnerTree {
private:
	Record<T>** tree;	// remind tree[0] is not used
	vector<pair<Run<T>*, int>> runs;	// (run, connected leaf node index) pair
	int	run_count;	// how many run's

public:
	WinnerTree() { tree = NULL; run_count = 0; }
	~WinnerTree() { delete tree; }

	void	Init();	// initialize the winner tree

	bool		RunEmpty();
	Record<T>*	GetWinner() { return tree[1]; }	// get current winner (not use tree[0])
	bool		NextWinner();					// find next winner
};

template <class T>
inline void WinnerTree<T>::Init() {
	// determine runs
	cout << "How many runs? : ";
	cin >> run_count;
	cin.ignore();	// remove '\n' from buffer
	runs.resize(run_count);

	// create and initialize runs
	for (int i = 0; i < run_count; i++) {
		runs[i].first = new Run<T>(i);	// create i th run

		string line;
		cout << "Initialize " << i + 1 << "th run ..." << endl;
		getline(cin, line);

		// split /w white space and enqueue
		int key;
		stringstream stream(line);
		while (stream >> key)
			runs[i].first->EnQueue(key);
	}

	// create and initialize the tree
	int level = ceil(log2(run_count));
	int tree_size = pow(2, level + 1);
	tree = new Record<T>*[tree_size];

	// set leaf node(run's start pos) index and push in to tree
	for (int i = 0; i < run_count; i++) {
		runs[i].second = run_count + i;
		tree[run_count + i] = runs[i].first->GetFrontRef();
	}
		
	// init tournament in reverse order (prevent - no sibling situation)
	int walker = runs[run_count - 1].second;	// last run
	while (walker > 1) {
		tree[walker / 2] = (tree[walker]->GetKey() < tree[walker - 1]->GetKey()) ? tree[walker] : tree[walker - 1];
		walker -= 2;
	}
}

template<class T>
inline bool WinnerTree<T>::RunEmpty()
{
	for (int i = 0; i < run_count; i++)
		if (!runs[i].first->IsEmpty())
			return false;
	return true;
}

template<class T>
inline bool WinnerTree<T>::NextWinner() {
	 
	// remove from queue
	int popped_queue = tree[1]->GetID();
	runs[popped_queue].first->DeQueue();

	// check all run's are empty
	if (RunEmpty()) {
		cout << "[ERROR] NO ENTRY AVAILABLE" << endl;
		return false;	// fail
	}

	// insert new element
	int walker = runs[popped_queue].second;
	tree[walker] = runs[popped_queue].first->GetFrontRef();

	// tournament
	int sibling;
	while (walker > 1) {
		// compare with sibling
		if (walker % 2 == 0) 
			sibling = walker + 1;
		else 
			sibling = walker - 1;

		if (tree[walker] == NULL)
			tree[walker / 2] = tree[sibling];
		else if (tree[sibling] == NULL)
			tree[walker / 2] = tree[walker];
		else if (tree[walker]->GetKey() < tree[sibling]->GetKey())
			tree[walker / 2] = tree[walker];
		else if (tree[walker]->GetKey() > tree[sibling]->GetKey())
			tree[walker / 2] = tree[sibling];

		walker /= 2;
	}

	return true;	// success
}
