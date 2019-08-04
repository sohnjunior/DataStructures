#pragma once
#include "Edge.h"
#include <iostream>
using namespace std;

template <class T>
class Vertex {
private:
	T		vertexKey;	// used for shortest path algorithm
	bool	visited;	// used for graph traversal

	Vertex<T>*	pNext;	// next vertex
	Edge<T>*	pAdj;	// adjacency list

public:
	Vertex(T vertexKey) {
		this->vertexKey = vertexKey;
		visited = false;
		pNext = NULL;
		pAdj = NULL;
	}

	template<class T>
	friend class Graph;
};