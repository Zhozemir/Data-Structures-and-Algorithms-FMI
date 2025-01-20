#include <iostream>
#include <vector>
#include <queue>

class Graph {

private:

	bool isOriented;
	size_t vtxCount;
	std::vector<std::vector<std::pair<int, int>>> adj;

public:

	Graph(size_t V, bool isOriented);

	void addEdge(size_t start, size_t end, int weight);

	size_t dijkstra(size_t start, size_t end, std::vector<size_t>& path) const;

};

Graph::Graph(size_t V, bool isOriented) : adj(V), vtxCount(V), isOriented(isOriented) {}

void Graph::addEdge(size_t start, size_t end, int weight) {
	
	adj[start].push_back(std::make_pair(end, weight));

	if (!isOriented)
		adj[end].push_back(std::make_pair(start, weight));

}

size_t Graph::dijkstra(size_t start, size_t end, std::vector<size_t>& path) const {

	std::vector<size_t> distances(vtxCount, INT_MAX);
	std::vector<size_t> prevs(vtxCount);

	struct vertexAndDistancePair {

		size_t vertex;
		size_t distFromStart;

		bool operator<(const vertexAndDistancePair& other) const {
		
			return distFromStart > other.distFromStart;
		
		}

	};

	std::priority_queue<vertexAndDistancePair> pq;

	distances[start] = 0;

	pq.push({ start, 0 });

	while (!pq.empty()) {
	
		vertexAndDistancePair current = pq.top();
		pq.pop();
	
		if (current.vertex == end) {
		
			while (end != start) {
			
				path.push_back(end);
				end = prevs[end];
			
			}

			path.push_back(start);

			std::reverse(path.begin(), path.end());
		
			return distances[current.vertex];
		
		
		}

		for (int i = 0; i < adj[current.vertex].size(); i++) {
		
			size_t currentNeighbor = adj[current.vertex][i].first;

			size_t newDist = current.distFromStart + adj[current.vertex][i].second;

			if (distances[currentNeighbor] > newDist) {
			
				distances[currentNeighbor] = newDist;

				pq.push({ currentNeighbor, newDist });

				prevs[currentNeighbor] = current.vertex;
			
			}
		
		
		}
	
	}

	return INT_MAX;

}

