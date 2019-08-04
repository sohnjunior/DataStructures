#pragma once
#include <iostream>
using namespace std;

template <class T>
class Vertex;

template <class T>
class Edge {
private:
	int			weight;
	Vertex<T>*	pFrom;
	Vertex<T>*	pTo;
	Edge<T>*	pNext;

public:
	Edge(Vertex<T>* from, Vertex<T>* to, int weight) {
		this->weight = weight;
		pFrom = from;
		pTo = to;
		pNext = NULL;
	}

	template<class T>
	friend class Graph;
};