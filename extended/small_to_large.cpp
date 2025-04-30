#include <bits/stdc++.h>

class DisjointSet {
private:
	std::vector<std::map<int, int>> color;
	std::vector<int> parent, size;
public:
	void init(int, std::vector<int>);
	int find(int);
	bool join(int, int);
	int query(int, int);
};

void DisjointSet::init(int n, std::vector<int> _color) {
	parent.assign(n, 0);
	std::iota(parent.begin(), parent.end(), 0);
	size.assign(n, 1);
	color.resize(n);
	for (int i = 0; i < n; i += 1) {
		color[i][_color[i]] += 1;
	}
}

int DisjointSet::find(int u) {
	return parent[u] = (u == parent[u] ? u : find(parent[u]));
}

bool DisjointSet::join(int a, int b) {
	a = find(a);
	b = find(b);
	if (a == b)
		return false;
	if (size[a] < size[b])
		std::swap(a, b);
	parent[b] = a;
	size[a] += size[b];

	for (auto p : color[b]) color[a][p.first] += p.second;
	color[b].clear();
	return true;
}

int DisjointSet::query(int v, int c) {
	v = find(v);
	return color[v].count(c) ? color[v][c] : 0;
}

int main(void) {
	DisjointSet a;
	a.init(5, std::vector<int>{1, 2, 3, 2, 5});
	a.join(0, 3);
	a.join(2, 3);
	a.join(0, 1);
	std::cout << a.query(2, 2);
	return 0;
}
