#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <queue>


template <class T>
class Graph {
private:
	Vertex<T>*	pVertexList;	// head of adjacency vertex list
	int	vertexCount;
	int edgeCount;

public:
	Graph() { 
		pVertexList = NULL;
		vertexCount = edgeCount = 0; 
	}
	~Graph() {}

	bool	IsEmpty() { return vertexCount == 0; }
	int		NumberOfVertices() { return vertexCount; }
	int		NumberOfEdges() { return edgeCount; }

	int		Degree(T vertexKey);					// 정점 v에 인접한 간선의 수 반환
	bool	ExistEdge(T vertexFrom, T vertexTo);	// 그래프에 간선 (u, v)가 존재하면 true

	Vertex<T>*	FindVertex(T vertexKey);	// key값을 가지는 vertex가 존재하는지 확인한다.

	bool	InsertVertex(T vertexKey);		// key값을 가지는 vertex를 생성한다.
	bool	InsertEdge(T vertexFrom, T vertexTo, int weight);		// 무방향 그래프에서 from에서 to에 이르는 간선을 생성한다.
	bool	UniInsertEdge(T vertexFrom, T vertexTo, int weight);	// u -> v 에 해당하는 간선을 생성한다.

	bool	DeleteVertex(T vertexKey);	// vertexKey에 해당하는 정점을 삭제한다.
	bool	DeleteEdge(T vertexFrom, T vertexTo);		// 무방향 그래프에서 (u,v), (v,u)에 해당하는 간선을 삭제한다.
	bool	UniDeleteEdge(T vertexFrom, T vertexTo);	// u -> v 에 해당하는 간선을 삭제한다.

	void	DFS(T startVertex);				// DFS traversal
	void	DFSWorkhorse(T startVertex);	// DFS traversal
	void	BFS(T startVertex);	// BFS traversal
	void	InitializeVisit();	// initialize visit field to non-visited
};

template<class T>
inline int Graph<T>::Degree(T vertexKey) {
	Vertex<T>* target = FindVertex(vertexKey);
	if (target == NULL)
		return -1;	// return -1 if vertex is not exist

	Edge<T>* pCur = target->pAdj;
	int adjCount = 0;
	while (pCur) {
		adjCount++;
		pCur = pCur->pNext;
	}

	return adjCount;
}

template<class T>
inline bool Graph<T>::ExistEdge(T vertexFrom, T vertexTo) {
	Vertex<T>* target = FindVertex(vertexFrom);
	if (target == NULL)
		return false;

	Edge<T>* pCur = target->pAdj;
	while (pCur) {
		if (pCur->pTo->vertexKey == vertexTo)
			return true;

		pCur = pCur->pNext;
	}

	return false;
}

template<class T>
inline Vertex<T>* Graph<T>::FindVertex(T vertexKey) {
	Vertex<T>* pCur = pVertexList;
	while (pCur) {
		if (pCur->vertexKey == vertexKey)
			return pCur;
		pCur = pCur->pNext;
	}
	return NULL;
}

template<class T>
inline bool Graph<T>::InsertVertex(T vertexKey) {
	if (FindVertex(vertexKey))
		return false;

	// create new node
	Vertex<T>* newNode = new Vertex<T>(vertexKey);

	// if there is no vertex
	if (pVertexList == NULL) {
		pVertexList = newNode;
	}
	else {
		// find the position and append the new node
		Vertex<T>* pCur = pVertexList;
		while (pCur->pNext != NULL)
			pCur = pCur->pNext;
		pCur->pNext = newNode;
	}

	vertexCount++;
	return true;
}

template<class T>
inline bool Graph<T>::InsertEdge(T vertexFrom, T vertexTo, int weight) {
	if (!UniInsertEdge(vertexFrom, vertexTo, weight) || !UniInsertEdge(vertexTo, vertexFrom, weight))
		return false;
	return true;
}

template<class T>
inline bool Graph<T>::UniInsertEdge(T vertexFrom, T vertexTo, int weight) {
	Vertex<T>* from = FindVertex(vertexFrom);
	Vertex<T>* to = FindVertex(vertexTo);
	if (from == NULL || to == NULL)
		return false;

	// create new edge
	Edge<T>* newEdge = new Edge<T>(from, to, weight);

	// if vertex has no adj list
	if (from->pAdj == NULL) {
		from->pAdj = newEdge;
	}
	else {
		Edge<T>* pCur = from->pAdj;
		while (pCur->pNext != NULL)
			pCur = pCur->pNext;
		pCur->pNext = newEdge;
	}

	edgeCount++;
	return true;
}

template<class T>
inline bool Graph<T>::DeleteVertex(T vertexKey) {
	// find the vertex
	Vertex<T>* target = FindVertex(vertexKey);
	if (target == NULL)
		return false;

	// delete all edges
	Edge<T>* pPrev = NULL;
	Edge<T>* pCur = target->pAdj;
	while (pCur) {
		pPrev = pCur;
		pCur = pCur->pNext;
		DeleteEdge(vertexKey, pPrev->pTo->vertexKey);
	}

	// delete vertex
	Vertex<T>* prev = pVertexList;
	while (prev) {
		if (prev->pNext == target)
			break;
		prev = prev->pNext;
	}

	if (prev == NULL)
		pVertexList = target->pNext;
	else
		prev->pNext = target->pNext;
	delete target;

	vertexCount--;
	return true;
}

template<class T>
inline bool Graph<T>::DeleteEdge(T vertexFrom, T vertexTo) {
	if (!UniDeleteEdge(vertexFrom, vertexTo) || !UniDeleteEdge(vertexTo, vertexFrom))
		return false;
	return true;
}

template<class T>
inline bool Graph<T>::UniDeleteEdge(T vertexFrom, T vertexTo) {
	// find the vertex
	Vertex<T>* from = FindVertex(vertexFrom);
	if (from == NULL)
		return false;

	// find the edge node
	Edge<T>* fromPrev = NULL;
	Edge<T>* fromAdj = from->pAdj;
	while (fromAdj) {
		if (fromAdj->pTo->vertexKey == vertexTo)
			break;
		fromPrev = fromAdj;
		fromAdj = fromAdj->pNext;
	}
	if (fromAdj == NULL)
		return false;
	
	// redirect the node pointer
	if (fromPrev == NULL)
		from->pAdj = fromAdj->pNext;
	else
		fromPrev->pNext = fromAdj->pNext;
	delete fromAdj;

	edgeCount--;
	return true;
}

template<class T>
inline void Graph<T>::DFS(T startVertex) {
	InitializeVisit();
	DFSWorkhorse(startVertex);
}

template<class T>
inline void Graph<T>::DFSWorkhorse(T startVertex) {
	Vertex<T>* pCur = FindVertex(startVertex);
	if (pCur == NULL)
		return;

	cout << pCur->vertexKey << ' ';	// visit action
	pCur->visited = true;
	Edge<T>* adjList = pCur->pAdj;
	while (adjList) {
		if (!adjList->pTo->visited)
			DFSWorkhorse(adjList->pTo->vertexKey);
		adjList = adjList->pNext;
	}
}

template<class T>
inline void Graph<T>::BFS(T startVertex) {
	Vertex<T>* pCur = FindVertex(startVertex);
	if (pCur == NULL)
		return;

	InitializeVisit();	// initialize the status
	queue<Vertex<T>*> queue;

	cout << pCur->vertexKey << ' ';	// visit action
	pCur->visited = true;
	queue.push(pCur);

	while (!queue.empty()) {
		Vertex<T>* popped = queue.front();	queue.pop();
		
		Edge<T>* adjList = popped->pAdj;
		while (adjList) {
			pCur = adjList->pTo;
			if (!pCur->visited) {
				cout << pCur->vertexKey << ' ';	// visit action
				pCur->visited = true;
				queue.push(pCur);
			}

			adjList = adjList->pNext;
		}
	}
}

template<class T>
inline void Graph<T>::InitializeVisit() {
	Vertex<T>* pCur = pVertexList;
	while (pCur) {
		pCur->visited = false;
		pCur = pCur->pNext;
	}
}
