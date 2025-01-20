#include "graphTraversals.hpp"

int main() {

	Graph g(6, true);

	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 3);
	g.addEdge(2, 3);
	g.addEdge(3, 4);
	g.addEdge(4, 5);

	g.BFS(0);
	std::cout << std::endl;

	g.DFS(0);
	std::cout << std::endl;

	if (g.containsCycle())
		std::cout << "Contains cycle" << std::endl;
	else
		std::cout << "Doesn't contain cycle" << std::endl;

	std::cout << "Connected components count: " << g.getConnectedComponentsCount() << std::endl;

	std::vector<size_t> sorted = g.topoSort();
	std::cout << "Topo sort:" << std::endl;

	for (auto el : sorted)
		std::cout << el << " ";

}