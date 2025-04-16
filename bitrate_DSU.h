#include <bits/stdc++.h>

class DisjointSet {
private:
	std::vector<std::pair<int, int>> parent;
	std::vector<int> rank;
	std::vector<int> bipartite;
public:
	void init(int);
	std::pair<int, int> find(int);
	bool join(int, int);
	bool is_bipartite(int);
};

void DisjointSet::init(int n) {
	parent.resize(n);
	rank.resize(n);
	bipartite.resize(n);
	for (int v = 0; v < n; v += 1) {
		parent[v] = std::make_pair(v, 0);
		rank[v] = 0;
		bipartite[v] = true;
	}
}

std::pair<int, int> DisjointSet::find(int v) {
	if (v != parent[v].first) {
		int parity = parent[v].second;
		parent[v] = find(parent[v].first);
		parent[v].second ^= parity;
	}
	return parent[v];
}

bool DisjointSet::join(int a, int b) {
	std::pair<int, int> pa = find(a);
	a = pa.first;
	int x = pa.second;
	
	std::pair<int, int> pb = find(b);
	b = pb.first;
	int y = pb.second;
	
	if (a == b) {
		if (x == y)
		bipartite[a] = false;
		return false;
	} else {
		if (rank[a] < rank[b])
		std::swap(a, b);
		parent[b] = std::make_pair(a, x ^ y ^ 1);
		bipartite[a] &= bipartite[b];
		if (rank[a] == rank[b])
		rank[a] += 1;
		return true;
	}
}

bool DisjointSet::is_bipartite(int v) {
	return bipartite[find(v).first];
}