#include <bits/stdc++.h>

class DisjointSet {
private:
	std::vector<int> parent;
	std::vector<int> size;
public:
	void init(int);
	int find(int);
	bool join(int, int);
	bool sameSet(int, int);
};

void DisjointSet::init(int n) {
	parent.assign(n, 0);
	size.assign(n, 1);
	for (int i = 0; i < n; i += 1) {
		parent[i] = i;
	}
}

int DisjointSet::find(int u) {
	return parent[u] = (u == parent[u] ? u : find(parent[u]));
}

bool DisjointSet::sameSet(int u, int v) {
	return find(u) == find(v);
}

// Since that in C++ union is a keyword, so we will use join instead of union
bool DisjointSet::join(int u, int v) {
	u = find(u);
	v = find(v);
	if (u == v)
		return false;
	if (size[u] > size[v])
		std::swap(u, v);
	parent[u] = v;
	size[v] += size[u];
	return true;
}

int main(void) {
	DisjointSet a;
	a.init(5);
	a.join(0, 3);
	a.join(2, 3);
	std::cout << a.sameSet(0, 2);
}
