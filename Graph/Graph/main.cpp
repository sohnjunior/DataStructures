#include "Graph.h"

int main() {
	Graph<int> graph;

	puts("========== Create Graph ==========");
	// create vertex
	for (int i = 0; i < 8; i++)
		graph.InsertVertex(i);
	// create edges
	graph.InsertEdge(0, 1, 0);
	graph.InsertEdge(0, 2, 0);
	graph.InsertEdge(1, 3, 0);
	graph.InsertEdge(1, 4, 0);
	graph.InsertEdge(2, 5, 0);
	graph.InsertEdge(2, 6, 0);
	graph.InsertEdge(7, 3, 0);
	graph.InsertEdge(7, 4, 0);
	graph.InsertEdge(7, 5, 0);
	graph.InsertEdge(7, 6, 0);

	puts("\n========== DFS ==========");
	cout << "start with vertex 0 : ";
	graph.DFS(0);
	cout << endl;
	cout << "start with vertex 1 : ";
	graph.DFS(1);

	puts("\n========== BFS ==========");
	cout << "start with vertex 0 : ";
	graph.BFS(0);
	cout << endl;
	cout << "start with vertex 1 : ";
	graph.BFS(1);

	
	puts("\n========== Delete Vertex 4 ==========");
	graph.DeleteVertex(4);
	graph.DFS(0);
	cout << endl;

	puts("\n========== Delete Vertex 2 ==========");
	graph.DeleteVertex(2);
	graph.DFS(0);
	cout << endl;

	puts("\n========== Delete Edge ==========");
	graph.DeleteEdge(3, 7);
	graph.DFS(0);
	cout << endl;
	graph.DFS(7);
	cout << endl;

	return 0;
}