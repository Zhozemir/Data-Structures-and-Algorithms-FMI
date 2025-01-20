#include <iostream>
#include <vector>
#include <queue>
#include <stack>

class Graph {

	std::vector<std::vector<int>> adj;

	bool oriented;

	bool containsCycleRec(size_t start, std::vector<bool>& visited, std::vector<bool>& stack) const;
	void topoSortRec(size_t start, std::vector<bool>& visited, std::vector<size_t>& st) const;

public:

	Graph(size_t vertexCount, bool isOriented);
	void addEdge(size_t start, size_t end);

	void BFS(size_t start) const;
	void DFS(size_t start) const;

	bool containsCycle() const;

	void connectedComponentsBFS(size_t start, std::vector<bool>& visited) const;
	size_t getConnectedComponentsCount() const;

	std::vector<size_t> topoSort() const;

};

Graph::Graph(size_t vertexCount, bool isOriented) : adj(vertexCount), oriented(isOriented) {}

void Graph::addEdge(size_t start, size_t end) {

	adj[start].push_back((int)end);

	if (!oriented)
		adj[end].push_back((int)start);

}

void Graph::BFS(size_t start) const {

	std::vector<bool> visited(adj.size(), false);

	std::queue<int> q;
	q.push(start);

	visited[start] = true;

	while (!q.empty()) {

		int currentVertex = q.front();
		q.pop();

		std::cout << currentVertex << " ";

		for (auto neighbor : adj[currentVertex]) {

			if (visited[neighbor])
				continue;

			visited[neighbor] = true;
			q.push(neighbor);


		}

	}

}

void Graph::DFS(size_t start) const {

	std::vector<bool> visited(adj.size(), false);

	std::stack<size_t> s;

	s.push(start);

	while (!s.empty()) {

		size_t current = s.top();
		s.pop();

		if (visited[current])
			continue;

		visited[current] = true;
		std::cout << current << " ";

		for (auto neighbor : adj[current])
			s.push(neighbor);

	}

}

bool Graph::containsCycleRec(size_t start, std::vector<bool>& visited, std::vector<bool>& stack) const {

	if (!visited[start]) {

		visited[start] = true;
		stack[start] = true;

		for (auto neighbor : adj[start]) {

			if (!visited[neighbor] && containsCycleRec(neighbor, visited, stack))
				return true;
			else if (stack[neighbor])
				return true;

		}

	}

	stack[start] = false;
	return false;

}

bool Graph::containsCycle() const {

	std::vector<bool> visited(adj.size(), false);
	std::vector<bool> inStack(adj.size(), false);

	for (int i = 0; i < adj.size(); i++) {

		if (containsCycleRec(i, visited, inStack))
			return true;

	}

	return false;

}

void Graph::connectedComponentsBFS(size_t start, std::vector<bool>& visited) const {

	std::queue<size_t> q;
	q.push(start);
	visited[start] = true;

	while (!q.empty()) {

		size_t currentVertex = q.front();
		q.pop();

		for (auto neighbor : adj[currentVertex]) {

			if (visited[neighbor])
				continue;

			visited[neighbor] = true;
			q.push(neighbor);

		}

	}

}

size_t Graph::getConnectedComponentsCount() const {

	size_t connectedComponentsCount = 0;

	std::vector<bool> visited(adj.size(), false);

	for (int i = 0; i < adj.size(); i++) {

		if (!visited[i]) {

			connectedComponentsCount++;
			connectedComponentsBFS(i, visited);

		}

	}

	return connectedComponentsCount;

}

void Graph::topoSortRec(size_t start, std::vector<bool>& visited, std::vector<size_t>& st) const {

	visited[start] = true;

	for (int i = 0; i < adj[start].size(); i++) {

		size_t neighbor = adj[start][i];

		if (!visited[neighbor])
			topoSortRec(neighbor, visited, st);

	}

	st.push_back(start);

}

std::vector<size_t> Graph::topoSort() const {

	std::vector<bool> visited(adj.size(), false);
	std::vector<size_t> result;

	for (int i = 0; i < adj.size(); i++) {

		if (!visited[i])
			topoSortRec(i, visited, result);

	}

	std::reverse(result.begin(), result.end());

	return result;

}